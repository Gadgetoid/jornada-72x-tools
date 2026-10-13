# Writing docstrings

The headers get their editor hover text and parameter names from `docs/api/*.txt`. `tools/mkdocs.py`
copies each entry above the function's declaration. They're written from the Windows CE 3.0 SDK reference (`reference/help/evt3/wcesdkr`), the C run-time
reference (`reference/help/evt3/wcecrt`) and the Handheld PC 2000 SDK headers (`reference/sdk/include/ce300`).
`docs/REFERENCE.md` says where those come from.

## The batches

`reference/batches/INDEX.md` lists the batches, one or more per `docs/api` file. Each batch file has, for every
function in it:

- its status:
  - `new`: no entry yet, has a reference page
  - `new-without-reference`: no entry, no reference page
  - `review`: has an entry, written from the Windows CE 1.0 and 2.0 references
  - `review-stale`: has an entry that mentions CE 1.0, 2.0 or the Velo
- the declaration from our headers, with the parameter names the entry must use
- the current entry, if any
- the reference page as text (summary, syntax, parameters, return values, remarks, requirements)

Regenerate them with `python3 tools/docref.py batches` after the headers change.

## Doing a batch

1. Read the batch file.
2. Write the entries into `docs/api/<file>.<batch>.txt`, where `<file>` is the batch's target and
   `<batch>` is its number. For batch `053-winbase`, that's `docs/api/winbase.053.txt`. This keeps
   batches that share a target from editing the same file.
   - `new` and `new-without-reference`: write an entry.
   - `review` and `review-stale`: write a replacement only where the CE 3.0 page says something
     different or adds something the reader needs. Leave out entries that need no change: `merge`
     replaces entries by name and keeps the rest.
3. When the batches are done, fold the files in, write the docstrings into the headers and check:

   ```sh
   python3 tools/docref.py merge
   make docstrings          # must report 0 problems
   make check-cxx-headers
   python3 tools/docref.py status
   ```

Don't edit `include/` by hand: `make docstrings` and `make headers` overwrite it.

## Entry format

```
## FunctionName(firstParameter, secondParameter)
One line saying what it does.

Optional paragraphs: when to use it, what to watch for, what CE 3.0 does
differently from desktop Windows.

@param firstParameter What it is, and the values it takes.
@param secondParameter What it is. Continuation lines are indented to
       line up after the tag.
@return What it returns, and how failure shows (for example "TRUE on
        success, FALSE on failure (see GetLastError)").
```

- Name the parameters exactly as in the batch's declaration, in order, one `@param` each. Leave out
  `...`. `make docstrings` reports a mismatch.
- Leave out `@return` for `void` functions.
- Wrap at about 76 columns. Entries in a file are sorted by name, ignoring case. `merge` handles that
  for you.
- For a function the headers reach under another name (the batch says "Exported by the ROM as"),
  document the name the batch uses.

## Style

- Write in your own words: technical, informal, direct and brief. Keep exact facts exact: flag names,
  value ranges, buffer sizes, error codes and the functions to call instead.
- Don't state what the declaration already says, or anything a Windows programmer would find obvious.
- Plain ASCII: no em dashes, curly quotes or other characters you can't type. No double spaces after
  a period.
- Don't write `*/` (as in `GWL_*/DWL_*`): it ends the comment in the header. `make docstrings` turns
  it into `* /`, but `GWL_* or DWL_*` reads better.
- Describe Windows CE 3.0 as the Handheld PC 2000 has it. Drop anything about CE 1.0, 1.01 or 2.0,
  the Philips Velo, velo-emu, `jornada::runtime` or a static C library. Every function in a batch is
  exported by the Jornada 720's ROM, so don't add version notes ("3.0 and later").
- If the page says the function is unsupported, a stub, or depends on the OEM, say so briefly.
- `new-without-reference`: write an entry only when the declaration and the SDK header in
  `reference/sdk/include/ce300` make the purpose clear. Never guess at behaviour. Otherwise leave it out.
- Skip the page's examples, "Requirements" boilerplate and "See Also" lists. Name another function
  only when the reader needs it (the function that frees a result, the one to call first).

## Facts from the Handheld PC 2000 SDK release notes

From `reference/hpc2000sdkreadme.htm`. Put each in the relevant entry:

- `CeSetDatabaseInfo` (and MFC's `CCeDBDatabase::SetInfo`): the database must be closed first on
  Handheld PC 2000. Handheld PC Pro didn't require it.
- Up-down controls: `UDM_SETRANGE` doesn't set the position, so send `UDM_SETPOS` after it. Set the
  range before reading a position, or the sign of `NM_UPDOWN.iDelta` can be inverted. The position can
  be out of range if you manage it yourself, so clamp it.
- TAPI: programs can hang in `GetMessage` waiting for a message that never arrives, because TAPI
  messages go straight to the callback. Use `Sleep(50)` then `PeekMessage` instead.
- `MENU_HEIGHT` is missing from the SDK headers. Its value is 26.

## Rebuilding the inputs

- `python3 tools/docref.py index`: parse `reference/help/evt3/*/htm` into `reference/index.json`. Run it again if the help
  files change.
- `python3 tools/docref.py status`: count functions with entries and reference pages.
- `make headers`: regenerate the headers from `reference/sdk/include/ce300` and the export lists, then the
  docstrings. It needs `JORNADA_LLVM_ROOT`.
