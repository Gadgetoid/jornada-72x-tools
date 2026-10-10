include_guard(GLOBAL)

get_filename_component(JORNADA_TOOLCHAIN_ROOT "${CMAKE_CURRENT_LIST_DIR}/.." ABSOLUTE)
find_package(Python3 REQUIRED COMPONENTS Interpreter)
enable_language(ASM)
enable_language(CXX)

set(JORNADA_WIN32_WCE ${JORNADA_CE_VERSION}00)
set(JORNADA_EXPORTS_NAME "ce${JORNADA_CE_VERSION}")
set(JORNADA_EXPORTS_DIR "${JORNADA_TOOLCHAIN_ROOT}/exports/${JORNADA_EXPORTS_NAME}")
if(NOT IS_DIRECTORY "${JORNADA_EXPORTS_DIR}")
    message(FATAL_ERROR "No export lists for JORNADA_CE_VERSION=${JORNADA_CE_VERSION}")
endif()

if(NOT DEFINED JORNADA_OS_SYMBOLS)
    set(JORNADA_OS_SYMBOLS "$ENV{JORNADA_OS_SYMBOLS}")
endif()
if(JORNADA_OS_SYMBOLS)
    get_filename_component(JORNADA_OS_SYMBOLS "${JORNADA_OS_SYMBOLS}" ABSOLUTE)
    if(NOT EXISTS "${JORNADA_OS_SYMBOLS}/nk.elf" OR NOT EXISTS "${JORNADA_OS_SYMBOLS}/rom.elf")
        message(WARNING "JORNADA_OS_SYMBOLS is ${JORNADA_OS_SYMBOLS}, which lacks nk.elf or rom.elf")
    endif()
endif()

add_library(jornada_headers INTERFACE)
target_include_directories(jornada_headers SYSTEM INTERFACE "${JORNADA_TOOLCHAIN_ROOT}/include" "${JORNADA_TOOLCHAIN_ROOT}/include/w32api")
add_library(jornada::headers ALIAS jornada_headers)

file(GLOB JORNADA_RUNTIME_SOURCES "${JORNADA_TOOLCHAIN_ROOT}/runtime/*.c" "${JORNADA_TOOLCHAIN_ROOT}/runtime/compiler-rt/*.c")
add_library(jornada_runtime STATIC EXCLUDE_FROM_ALL ${JORNADA_RUNTIME_SOURCES})
target_compile_options(jornada_runtime PRIVATE -fno-builtin -w)
add_library(jornada::runtime ALIAS jornada_runtime)

file(GLOB JORNADA_CXX_RUNTIME_SOURCES "${JORNADA_TOOLCHAIN_ROOT}/runtime/cxx/*.cpp")
add_library(jornada_cxx_runtime STATIC EXCLUDE_FROM_ALL ${JORNADA_CXX_RUNTIME_SOURCES})
target_link_libraries(jornada_cxx_runtime PRIVATE jornada_headers)
add_library(jornada::cxx_runtime ALIAS jornada_cxx_runtime)

file(GLOB JORNADA_EXPORT_LISTS "${JORNADA_EXPORTS_DIR}/*.txt")
file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/jornada/${JORNADA_EXPORTS_NAME}")
foreach(exports IN LISTS JORNADA_EXPORT_LISTS)
    get_filename_component(dll "${exports}" NAME_WE)
    string(TOUPPER "${dll}" dll_upper)
    set(stubs "${CMAKE_BINARY_DIR}/jornada/${JORNADA_EXPORTS_NAME}/${dll}.S")
    add_custom_command(
        OUTPUT "${stubs}"
        COMMAND "${Python3_EXECUTABLE}" "${JORNADA_TOOLCHAIN_ROOT}/tools/mkimplib.py" "${exports}" "${dll_upper}.dll" "${stubs}"
        DEPENDS "${exports}" "${JORNADA_TOOLCHAIN_ROOT}/tools/mkimplib.py"
        VERBATIM)
    add_library(jornada_${dll} STATIC EXCLUDE_FROM_ALL "${stubs}")
    add_library(jornada::${dll} ALIAS jornada_${dll})
endforeach()

function(_jornada_link target script cxx_entry)
    set_target_properties(${target} PROPERTIES SUFFIX ".elf" LINK_DEPENDS "${script}")
    target_link_options(${target} PRIVATE -T "${script}" "$<$<LINK_LANGUAGE:CXX>:--entry=${cxx_entry}>")
    target_link_libraries(${target} PRIVATE jornada::headers jornada::runtime jornada::coredll "$<$<LINK_LANGUAGE:CXX>:jornada::cxx_runtime>")
endfunction()

function(_jornada_pe target output)
    set_property(TARGET ${target} APPEND PROPERTY LINK_DEPENDS "${JORNADA_TOOLCHAIN_ROOT}/tools/mkpe.py")
    add_custom_command(TARGET ${target} POST_BUILD
        COMMAND "${Python3_EXECUTABLE}" "${JORNADA_TOOLCHAIN_ROOT}/tools/mkpe.py" "$<TARGET_FILE:${target}>" "$<TARGET_FILE_DIR:${target}>/${output}" "--ce-version=${JORNADA_CE_VERSION}" ${ARGN}
        VERBATIM)
endfunction()

function(_jornada_resources target out_options)
    set(options "")
    set(dependencies "")
    set(scripts "")
    foreach(resource IN LISTS ARGN)
        get_filename_component(resource "${resource}" ABSOLUTE)
        if(resource MATCHES "\\.rc$")
            list(APPEND scripts "${resource}")
        else()
            list(APPEND dependencies "${resource}")
        endif()
    endforeach()
    if(scripts)
        find_program(JORNADA_RC llvm-rc HINTS "${JORNADA_LLVM_ROOT}/bin" REQUIRED)
    endif()
    set(JORNADA_RC_ARCH_DEFINES "")
    foreach(define IN LISTS JORNADA_ARCH_DEFINES)
        list(APPEND JORNADA_RC_ARCH_DEFINES -D "${define}")
    endforeach()
    foreach(script IN LISTS scripts)
        get_filename_component(name "${script}" NAME_WE)
        get_filename_component(directory "${script}" DIRECTORY)
        set(compiled "${CMAKE_CURRENT_BINARY_DIR}/${target}_${name}.res")
        add_custom_command(
            OUTPUT "${compiled}"
            COMMAND "${JORNADA_RC}" -D "_WIN32_WCE=${JORNADA_WIN32_WCE}" ${JORNADA_RC_ARCH_DEFINES} -I "${JORNADA_TOOLCHAIN_ROOT}/include" -I "${JORNADA_TOOLCHAIN_ROOT}/include/w32api" -I "${directory}" -FO "${compiled}" -- "${script}"
            DEPENDS "${script}" ${dependencies}
            VERBATIM)
        target_sources(${target} PRIVATE "${compiled}")
        set_property(TARGET ${target} APPEND PROPERTY LINK_DEPENDS "${compiled}")
        list(APPEND options "--resources=${compiled}")
    endforeach()
    set(${out_options} ${options} PARENT_SCOPE)
endfunction()

function(_jornada_gdb_scripts)
    get_property(executables GLOBAL PROPERTY JORNADA_EXECUTABLES)
    get_property(libraries GLOBAL PROPERTY JORNADA_LIBRARIES)
    set(library_folders "")
    set(library_uploads "")
    foreach(library IN LISTS libraries)
        get_target_property(output ${library} JORNADA_OUTPUT)
        string(APPEND library_folders ":$<TARGET_FILE_DIR:${library}>")
        string(APPEND library_uploads "  remote put \"$<TARGET_FILE_DIR:${library}>/${output}\" /Windows/${output}\n")
    endforeach()
    set(os_symbols_setup "")
    set(os_symbols_folder "")
    set(os_symbols_load "")
    if(JORNADA_OS_SYMBOLS)
        set(os_symbols_setup "add-symbol-file \"${JORNADA_OS_SYMBOLS}/nk.elf\"
python
import os
def jornada_os_symbols(event):
    folder = os.path.realpath(\"${JORNADA_OS_SYMBOLS}\")
    loaded = [os.path.realpath(objfile.filename) for objfile in gdb.objfiles() if objfile.filename]
    if os.path.join(folder, \"rom.elf\") in loaded:
        return
    files = {name.lower(): name for name in os.listdir(folder)}
    for line in gdb.execute(\"info sharedlibrary\", to_string=True).splitlines():
        fields = line.split()
        if len(fields) < 2 or fields[-2] != \"No\":
            continue
        name = files.get(os.path.basename(fields[-1]).lower())
        if name and os.path.join(folder, name) not in loaded:
            gdb.execute(\"add-symbol-file \\\"%s\\\"\" % os.path.join(folder, name))
            loaded.append(os.path.join(folder, name))
    if [path for path in loaded if os.path.dirname(path) == folder and os.path.basename(path) != \"nk.elf\"]:
        return
    gdb.execute(\"remove-symbol-file \\\"%s\\\"\" % os.path.join(folder, \"nk.elf\"))
    gdb.execute(\"add-symbol-file \\\"%s\\\"\" % os.path.join(folder, \"rom.elf\"))
gdb.events.stop.connect(jornada_os_symbols)
end
")
        set(os_symbols_folder ":${JORNADA_OS_SYMBOLS}")
        set(os_symbols_load "  sharedlibrary\n")
    endif()
    set(architecture "set architecture armv4\n")
    foreach(target IN LISTS executables)
        get_target_property(output ${target} JORNADA_OUTPUT)
        file(GENERATE OUTPUT "$<TARGET_FILE:${target}>.gdb" CONTENT
"${architecture}set confirm off
set exec-file-mismatch off
maint set target-non-stop on
file \"$<TARGET_FILE:${target}>\"
${os_symbols_setup}set breakpoint pending on
set solib-search-path $<TARGET_FILE_DIR:${target}>${library_folders}${os_symbols_folder}
set remote exec-file /Windows/${output}
define jornada-load
  remote put \"$<TARGET_FILE_DIR:${target}>/${output}\" /Windows/${output}
${library_uploads}${os_symbols_load}end
")
    endforeach()
endfunction()

function(_jornada_add_gdb_script target output kind)
    set_target_properties(${target} PROPERTIES JORNADA_OUTPUT "${output}")
    set_property(GLOBAL APPEND PROPERTY ${kind} ${target})
    get_property(deferred GLOBAL PROPERTY JORNADA_GDB_SCRIPTS_DEFERRED)
    if(NOT deferred)
        set_property(GLOBAL PROPERTY JORNADA_GDB_SCRIPTS_DEFERRED TRUE)
        cmake_language(DEFER DIRECTORY "${CMAKE_SOURCE_DIR}" CALL _jornada_gdb_scripts)
    endif()
endfunction()

function(_jornada_require_exports target)
    foreach(export IN LISTS ARGN)
        string(REGEX REPLACE "^[^=]*=" "" symbol "${export}")
        target_link_options(${target} PRIVATE "--undefined=${symbol}")
    endforeach()
endfunction()

function(jornada_add_executable target)
    cmake_parse_arguments(PARSE_ARGV 1 JORNADA "EXCLUDE_FROM_ALL" "OUTPUT;ICON" "RESOURCES")
    if(NOT JORNADA_OUTPUT)
        set(JORNADA_OUTPUT "${target}.exe")
    endif()
    set(exclude "")
    if(JORNADA_EXCLUDE_FROM_ALL)
        set(exclude EXCLUDE_FROM_ALL)
    endif()
    add_executable(${target} ${exclude} ${JORNADA_UNPARSED_ARGUMENTS})
    _jornada_link(${target} "${JORNADA_TOOLCHAIN_ROOT}/ld/exe.ld" __jornada_exe_start)
    set(options "")
    if(JORNADA_ICON)
        get_filename_component(icon "${JORNADA_ICON}" ABSOLUTE)
        set(options "--icon=${icon}")
    endif()
    _jornada_resources(${target} resource_options ${JORNADA_RESOURCES})
    _jornada_pe(${target} "${JORNADA_OUTPUT}" ${options} ${resource_options})
    _jornada_add_gdb_script(${target} "${JORNADA_OUTPUT}" JORNADA_EXECUTABLES)
endfunction()

function(jornada_add_library target)
    cmake_parse_arguments(PARSE_ARGV 1 JORNADA "EXCLUDE_FROM_ALL" "OUTPUT;EXPORTS_FILE" "EXPORTS;RESOURCES")
    if(NOT JORNADA_OUTPUT)
        set(JORNADA_OUTPUT "${target}.dll")
    endif()
    if(NOT JORNADA_EXPORTS AND NOT JORNADA_EXPORTS_FILE)
        message(FATAL_ERROR "jornada_add_library(${target}) needs EXPORTS or EXPORTS_FILE")
    endif()
    set(exclude "")
    if(JORNADA_EXCLUDE_FROM_ALL)
        set(exclude EXCLUDE_FROM_ALL)
    endif()
    add_executable(${target} ${exclude} ${JORNADA_UNPARSED_ARGUMENTS})
    _jornada_link(${target} "${JORNADA_TOOLCHAIN_ROOT}/ld/dll.ld" __jornada_dll_start)
    set(options "")
    _jornada_require_exports(${target} ${JORNADA_EXPORTS})
    if(JORNADA_EXPORTS)
        string(JOIN "," exports ${JORNADA_EXPORTS})
        list(APPEND options "--exports=${exports}")
    endif()
    if(JORNADA_EXPORTS_FILE)
        get_filename_component(exports_file "${JORNADA_EXPORTS_FILE}" ABSOLUTE)
        file(STRINGS "${exports_file}" file_exports)
        _jornada_require_exports(${target} ${file_exports})
        list(APPEND options "--exports-file=${exports_file}")
        set_property(TARGET ${target} APPEND PROPERTY LINK_DEPENDS "${exports_file}")
    endif()
    _jornada_resources(${target} resource_options ${JORNADA_RESOURCES})
    _jornada_pe(${target} "${JORNADA_OUTPUT}" ${options} ${resource_options})
    if(NOT JORNADA_EXCLUDE_FROM_ALL)
        _jornada_add_gdb_script(${target} "${JORNADA_OUTPUT}" JORNADA_LIBRARIES)
    endif()
endfunction()
