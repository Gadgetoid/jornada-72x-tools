# jornada-72x-tools

A CMake toolchain for Windows CE 3.0 (Handheld PC 2000) ARM programs and DLLs, aimed at the HP Jornada 720 (StrongARM SA-1110). It uses clang and lld, then `tools/mkpe.py` turns the linked ELF into a CE PE.

## LLVM

Microsoft's CE ARM calling convention needs the `armv4-unknown-none-wince` target, which no LLVM release has. Download it from [velo-llvm-builds](https://github.com/Gadgetoid/velo-llvm-builds/releases) (v3 or later; v2 works without the C++ standard library), then set `JORNADA_LLVM_ROOT` to the unpacked folder or link it as `llvm` here.

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
- C++20 without exceptions or RTTI, with a header-only layer in `include/jornada/cxx` (see its README), and the C++ standard library (below).

## C++ standard library

With an LLVM that includes libc++ (velo-llvm-builds v3 or later), C++ code gets the standard library: strings and `string_view`, the containers, `<algorithm>`, `optional`, `variant`, `any`, `expected`, smart pointers, `std::function`, ranges, `<random>` and `std::format`. See `examples/stl-text` and `examples/stl-collections`.

- It's configured without threads, locales, iostreams, filesystem or exceptions. An error that would throw writes a message to the debug output and stops the program.
- The parts libc++ keeps in its library are built from its sources (`jornada::cxx_stdlib`, linked automatically). Floating point `to_chars`, used by `std::format`, is over coredll's `_snprintf`: exact with a precision, 17 significant digits (9 for `float`) without one.
- The runtime adds the C99 functions libc++ needs that coredll lacks: `snprintf`, `strtoll`, `float` and `long double` maths, `errno`, `wmemcpy` and others. `swprintf` keeps Microsoft's form; define `JORNADA_C99_SWPRINTF` for C99's.

## debugmgr

`debugmgr.exe` (`make debugmgr`, into `build/debugmgr`) runs on the device and lets `tools/jornada-debug` copy files, list folders and start and stop programs over TCP: through ActiveSync, a CF network card or anything else that gives the device an address. Copy it over once, start it, and it shows the address and port (2100) to connect to.

```sh
export JORNADA_DEVICE=192.168.55.101
tools/jornada-debug ping
tools/jornada-debug put build/ce3/hello/hello.exe /Windows/hello.exe
tools/jornada-debug run /Windows/hello.exe     # prints the process ID
tools/jornada-debug kill 0x1234
```

In an emulator, debugmgr can use the emulator's host mailbox instead of TCP: start it with `mailbox` on its command line, or set the registry value `HKLM\Software\debugmgr\Transport` to `mailbox`, and point `jornada-debug --socket` (or `JORNADA_AGENT`) at the emulator's agent socket. On a real device the mailbox call would end debugmgr, so it's only used when selected.

It also has `get`, `ls`, `rm`, `mkdir`, `rmdir`, `mv`, `quit` and `handover`. `kill` ends any process, not just ones debugmgr started. Anything that can reach the port can copy files to the device and run programs, so only leave it running on a network you trust. The protocol is in `debugmgr/PROTOCOL.md`.

## Connecting a device over USB

A Jornada 720's dock has a USB sync port, which Linux's `ipaq` driver turns into a serial port. macOS has no driver for it. `bridge/` sets up a Linux machine, such as a Raspberry Pi, to answer PC Link when the device is plugged in, giving it an address with PPP:

```sh
sudo apt install ppp
sudo bridge/install.sh
```

A udev rule starts `jornada-link@ttyUSB0` when the dock connects and stops it when it's unplugged. It answers the device's `CLIENT` greeting and runs `pppd`, with the host at 192.168.131.102 and the device at 192.168.131.201. `jornada-desktop` answers PC Link's desktop connection, without which it gives up with "Communications Error". Set `JORNADA_HOST_ADDRESS` and `JORNADA_DEVICE_ADDRESS` in `/etc/default/jornada-bridge` to change the addresses.

Start PC Link on the device with the USB connection.

On macOS, a serial cable works instead, through `/usr/sbin/pppd`, which needs root. PC Link only starts once DTR is raised, which `pppd` does:

```sh
python3 bridge/jornada-desktop --address 192.168.131.102 &
sudo pppd /dev/cu.usbserial-10 57600 nodetach noauth local nocrtscts nodefaultroute lcp-echo-interval 0 \
    connect "$(which python3) $PWD/bridge/jornada-handshake" 192.168.131.102:192.168.131.201
```

Then start PC Link on the device within 20 seconds.
 Nothing is routed between the link and other networks; from another computer, tunnel through the bridge's host:

```sh
ssh -N -L 2100:192.168.131.201:2100 pi
tools/jornada-debug --device 127.0.0.1:2100 ping
```

## GDB and VS Code

Each executable gets a GDB script beside its `.elf`, `<name>.elf.gdb`. It loads the symbols, sets the program to run as `\Windows\<name>.exe`, and defines `jornada-load`, which uploads the `.exe` and the project's DLLs to `\Windows` through debugmgr.

[jornada-72x-emu](https://github.com/Gadgetoid/jornada-72x-emu)'s GDB stub serves these. `tools/jornada-emulator` starts it (`JORNADA_EMU` names its folder) on the PPP gateway with GDB on port 2720 and the agent socket at `build/debugmgr/agent.sock`. PC Link connects by itself and the emulator installs debugmgr, printing `debugmgr: ready`, then:

```sh
gdb -x build/ce3/hello/hello.elf.gdb -ex "target extended-remote :2720" -ex jornada-load -ex "break WinMain" -ex run
```

For VS Code, copy `vscode/launch.json`, `vscode/tasks.json` and `vscode/settings.json` into a project's `.vscode` and set `JORNADA_TOOLCHAIN` to this folder. The settings have IntelliSense take include paths from CMake Tools. Debugging needs the C/C++ and CMake Tools extensions, a `Debug` build, and `gdb` with ARM support (Homebrew's `gdb` on macOS, `gdb-multiarch` on Linux). The emulator has no hardware watchpoints, so GDB uses software ones.

## Make

- `make check`: run every check that doesn't need the SDK, and build the examples and debugmgr
- `make examples`: build `examples/` into `build/ce3`
- `make check-abi`: check the compiler follows Microsoft's Windows CE ARM calling standard
- `make check-cxx-headers`: check the headers compile as C++
- `make check-stdlib`: build and link a program using most of the standard library
- `make debugmgr`: build `debugmgr.exe`
- `make check-debugmgr`: test debugmgr's protocol and `jornada-debug`, with debugmgr built for this computer serving a folder
- `make headers`, `make check-headers`: regenerate and check the headers against the SDK (needs `reference/sdk`, not included)
- `make exports ROM=jornada720.bin`: rewrite the export lists from a ROM image

## Status

Builds and checks pass. debugmgr and GDB debugging work in jornada-72x-emu. Programs run on a Jornada 720 through debugmgr over the USB bridge.

## Licence

MIT, see `LICENSE`. `include/w32api` is CeGCC's public-domain w32api, `runtime/compiler-rt` is LLVM's (Apache 2.0 with LLVM exceptions).
