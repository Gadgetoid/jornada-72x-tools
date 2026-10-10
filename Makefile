TOOLCHAIN = $(CURDIR)/cmake/jornada-ce.cmake
JORNADA_LLVM_ROOT ?= $(CURDIR)/llvm
export JORNADA_LLVM_ROOT
CLANG = $(JORNADA_LLVM_ROOT)/bin/clang
ROM ?= $(JORNADA_ROM)
JORNADA_REFERENCE ?= $(CURDIR)/reference/sdk
export JORNADA_REFERENCE
EXPORT_DLLS = addrstor asform ceshell commctrl commdlg coredll cxport htmlview imgdecmp inkx mlang mqoa msgstore msmqrt mshtml ndis ole32 oleaut32 richink secur32 shdocvw tnefutil toolhelp urlmon webview wininet winscard winsock

.PHONY: examples exports headers docstrings check-abi check-headers check-cxx-headers check-stdlib clean

examples:
	cmake -S examples -B build/ce3 -DCMAKE_TOOLCHAIN_FILE=$(TOOLCHAIN)
	cmake --build build/ce3

exports:
	python3 tools/cerom.py $(ROM) --exports exports/ce3 $(foreach dll,$(EXPORT_DLLS),--dll $(dll).dll)

headers:
	python3 tools/mksdk.py --clang $(CLANG)
	python3 tools/mkheaders.py --clang $(CLANG)
	python3 tools/mkconstants.py --clang $(CLANG)
	python3 tools/mkdocs.py

docstrings:
	python3 tools/mkdocs.py

check-abi:
	python3 tests/check-abi.py --clang $(CLANG)

check-stdlib:
	cmake -S tests/stdlib -B build/check-stdlib -DCMAKE_TOOLCHAIN_FILE=$(TOOLCHAIN)
	cmake --build build/check-stdlib

check-headers:
	python3 tests/check-headers.py --clang $(CLANG)

check-cxx-headers:
	python3 tests/check-cxx-headers.py --clang $(CLANG)

clean:
	rm -rf build
