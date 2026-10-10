# Resource Script (RC) for VS Code

Syntax highlighting for Windows resource scripts (`.rc`, `.rc2`), as `rc.exe` and `llvm-rc` accept them, including the Windows CE subset.

It highlights:

- the C preprocessor: `#include`, `#define`, `#if`/`#ifdef`/`#ifndef`/`#elif`/`#else`/`#endif`, `#undef`, `#pragma`, `#error`
- `//` and `/* */` comments
- strings, with escapes, `""` quotes, `\` line continuations and `L"..."` wide strings
- decimal and hex numbers, with `L` and `U` suffixes
- resource types, statements, controls, and memory, menu, accelerator and `VERSIONINFO` options, in any case
- common constants: `WS_*`, `DS_*`, `ES_*`, `BS_*`, `SS_*`, `LBS_*`, `CBS_*`, `SBS_*`, `VK_*`, `LANG_*`, `VS_*` and `IDOK`-style IDs

Strings end at the end of a line unless it ends with `\`, so an unclosed string doesn't run on into the rest of the file.

## Install

Either symlink this folder into VS Code's extensions folder and restart VS Code:

```sh
ln -s "$PWD" ~/.vscode/extensions/jornada-72x-tools.rc-language
```

or package it and install the `.vsix`:

```sh
npx @vscode/vsce package
code --install-extension rc-language-0.1.0.vsix
```

## Test

```sh
npm install
npm test
```

`test/constructs.test.rc` is a [vscode-tmgrammar-test](https://github.com/PanAeon/vscode-tmgrammar-test) fixture asserting the scopes of each construct. `test/check-files.js` tokenizes every `.rc` file in this repository, or the files and folders given as arguments, and fails if a string, comment or directive is left open at the end of a line or file, or a `BEGIN`/`END` line isn't scoped as a block.

## Licence

MIT. The preprocessor rules and scope names follow VS Code's C grammar (`extensions/cpp/syntaxes/c.tmLanguage.json`, from [jeff-hykin/better-c-syntax](https://github.com/jeff-hykin/better-c-syntax)), which is MIT licensed.
