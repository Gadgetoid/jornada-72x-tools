# jornada-72x-tools

A CMake toolchain for Windows CE 3.0 (Handheld PC 2000) ARM programs and DLLs, aimed at the HP Jornada 720 (StrongARM SA-1110). It uses clang and lld, then `tools/mkpe.py` turns the linked ELF into a CE PE.

## LLVM

Microsoft's CE ARM calling convention needs the `armv4-unknown-none-wince` target, which no LLVM release has. Download it from [velo-llvm-builds](https://github.com/Gadgetoid/velo-llvm-builds/releases) (v2 or later), then set `JORNADA_LLVM_ROOT` to the unpacked folder or link it as `llvm` here.

## Usage

```cmake
cmake_minimum_required(VERSION 3.20)
project(myapp C)
include(JornadaCE)

jornada_add_executable(myapp main.c ICON myapp.ico RESOURCES myapp.rc)
jornada_add_library(mylib mylib.c EXPORTS Add Greeting=greeting_impl)
target_link_libraries(myapp PRIVATE jornada::commctrl)
```

```sh
cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=/path/to/jornada-72x-tools/cmake/jornada-ce.cmake
cmake --build build
```

- Import libraries (`jornada::<dll>`) come from the Jornada 720 ROM's export tables (`exports/ce3`). `coredll` is always linked.
- `windows.h` gives the Win32 API, plus the C runtime that coredll exports (stdio, math, `malloc`, `printf`, `setjmp`). Everything is checked against the Handheld PC 2000 SDK headers.
- C++20 without exceptions or RTTI, with a header-only layer in `include/jornada/cxx` (see its README).
- `vscode/settings.json` sets up IntelliSense through CMake Tools.

## Make

- `make examples`: build `examples/` into `build/ce3`
- `make check-abi`: check the compiler follows Microsoft's Windows CE ARM calling standard
- `make check-cxx-headers`: check the headers compile as C++
- `make headers`, `make check-headers`: regenerate and check the headers against the SDK (needs `reference/sdk`, not included)
- `make exports ROM=jornada720.bin`: rewrite the export lists from a ROM image

## Status

Builds and checks pass. Nothing has run on a device or emulator yet.

## Licence

MIT, see `LICENSE`. `include/w32api` is CeGCC's public-domain w32api, `runtime/compiler-rt` is LLVM's (Apache 2.0 with LLVM exceptions).
