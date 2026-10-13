# Reference material

`make headers`, `make check-headers` and the docstring tools read Microsoft's SDK and help files from `reference/`,
which isn't in the repository. This is where they come from and how they're laid out.

## Handheld PC 2000 SDK

Microsoft Windows Platform SDK for Handheld PC 2000, archived at Internet Archive:

- Item: https://archive.org/details/hpc2ksdkusa
- Installer: `HPC2K-SDK_USA.exe`
- Archive.org SHA-1: `e0e406877b01fa1df5855458e967cd5fafe6b63e`
- Included readme: `hpc2000sdkreadme.htm`

Its embedded ZIP holds the headers and libraries; no `.hlp` or `.chm` files.

## Help files (eMbedded Visual Tools 3.0, archive.org item embedvt-3)

- `reference/help/evt3/*.CHM`: from `EMBEDVT3_CD1.iso/WCE/HTMLHELP/TOOLS/`. `WCESDKR.CHM` is the Windows CE 3.0
  SDK reference (3761 pages), `WCECRT.CHM` the C runtime reference; the rest are guides. Each is
  extracted with `7zz x` into the lowercase folder of the same name.
- `reference/help/JUPSDKR.CHM`, `reference/help/JUPWCE.CHM`: from `EMBEDVT3_CD2.iso/HPC30SDK/HELP/`. H/PC Pro delta pages
  (requirements rows only), applied over WCESDKR in the original viewer.

## Handheld PC 2000 SDK headers and libraries

- `reference/hpc2000-sdk/`: `wce300/hpc2000/include` and `wce300/hpc2000/lib/arm`, unzipped from `HPC2K-SDK_USA.exe`
  without running it. These are the CE 3.0 headers. Not `HPC30SDK` on the eMbedded Visual Tools
  CD, which is the Handheld PC Pro (CE 2.11) SDK.
- `reference/sdk/include/ce300`: a link to `reference/hpc2000-sdk/.../include`, the layout `tools/mksdk.py`, `tools/mkconstants.py`
  and `tests/check-headers.py` expect. The Makefile uses this folder as `JORNADA_REFERENCE` by default.

## Docstring work

`docs/DOCSTRINGS.md` says how to write the `docs/api` entries. `reference/index.json` and `reference/batches/` are
made by `tools/docref.py`.
