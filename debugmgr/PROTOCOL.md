# debugmgr protocol

debugmgr listens on TCP port 2100 (or the port given on its command line) and serves one connection at a time. Each message is
framed as a u32 little-endian length followed by the message. A request longer than the maximum message size closes the
connection.

All integers are little-endian. Strings are a u16 count of UTF-16 code units followed by that many UTF-16LE code units, with no
terminator. Paths are CE paths, `\` separated and absolute. Fields aren't aligned.

## Messages

Request: u16 command, u16 sequence, payload.

Reply: u16 command | 0x8000, u16 sequence (copied from the request), u32 status, payload. The payload is empty unless status is 0.

Clients use sequences 0x0001 to 0x7FFF. 0x8000 to 0xFFFF are kept for a debugger sharing the connection.

## Status

| Status | Meaning |
| --- | --- |
| 0 | done |
| 0x20000001 | unknown command |
| 0x20000002 | malformed request |
| 0x20000003 | no such process: KILL only knows programs started by RUN |
| 0x20000005 | KILL: still running after 5 seconds |
| other | the Windows error from `GetLastError`, e.g. 2 file not found, 3 path not found, 5 access denied, 80 or 183 exists, 112 disk full, 145 folder not empty |

## Commands

| # | Command | Request payload | Reply payload |
| --- | --- | --- | --- |
| 1 | PING | none | u32 protocol version (1), u32 maximum message size, u32 `_WIN32_WCE` (300) |
| 2 | WRITE | u32 offset, u32 flags, string path, data to the end of the message | none |
| 3 | READ | u32 offset, u32 length, string path | u32 file size, then up to length bytes from offset |
| 4 | RUN | string program, string arguments (empty for none) | u32 process ID |
| 5 | KILL | u32 process ID | none |
| 6 | LIST | string pattern, e.g. `\Windows\*` | u32 count, then per entry: u32 attributes, u32 size, string name |
| 7 | DELETE | string path | none |
| 8 | MKDIR | string path | none |
| 9 | RMDIR | string path | none |
| 10 | MOVE | string from, string to | none |
| 11 | QUIT | none | none, then debugmgr exits |
| 12 | HANDOVER | as RUN | as RUN, then debugmgr exits |

WRITE flag 0x1 creates the file, or truncates it if it exists. Without it the file must exist. Data is written at offset.

READ returns fewer bytes than asked at the end of the file, or when the reply would exceed the maximum message size.

The process ID is CE's `dwProcessId` from `CreateProcessW`. debugmgr remembers the last 16 programs it started for KILL, forgetting
the oldest after that. KILL waits up to 5 seconds for the program to end.

LIST stops early if the reply would exceed the maximum message size.

This is the protocol velo-toolchain's debugmgr uses through velo-emu's mailbox, with TCP framing in its place.
