jornada_add_library(cxx-counter cxx-counter.cpp EXPORTS ConstructedCount)
jornada_add_executable(cxx-basics cxx-basics.cpp)
add_dependencies(cxx-basics cxx-counter)
