# jornada/cxx

A header-only C++20 layer over the Windows CE API, in namespace `jornada`. It needs the toolchain's C++ support (see the main README), and nothing else: no exceptions, RTTI or standard library. It works alongside the standard library where that's available.

- It should cost nothing over the C it replaces: everything is inline, and the window base dispatches messages with no virtual calls.
- Errors are values. Functions that can fail return `jornada::result<T>`, which holds a `T` or a `jornada::error` (a `GetLastError` code or an HRESULT).
- It only wraps what Windows CE 3.0 on the Handheld PC 2000 has: every function it calls is exported by the Jornada 720's ROM.

## Headers

| Header | |
| --- | --- |
| `result.h` | `error`, `result<T>`, `result<void>`, `check(BOOL)`, `check_hresult(HRESULT)` |
| `handle.h` | `unique_resource<T, Traits>`, `unique_handle` (`CloseHandle`), `create_file`, `create_event` |
| `memory.h` | `local_ptr<T>` (`LocalFree`), `local_alloc<T>(count)` |
| `gdi.h` | `unique_pen`, `unique_brush`, `unique_font`, `unique_bitmap`, `unique_region` (`DeleteObject`) and their `create_` functions, `select_guard`, `device_context`, `paint_dc` (`BeginPaint`/`EndPaint`), `window_dc` (`GetDC`/`ReleaseDC`), `point` |
| `string_view.h` | `wstring_view`, `string_view` |
| `fixed_string.h` | `wstring<N>`, `string<N>`: up to N - 1 characters inline, always null-terminated |
| `utf8.h` | `utf8_to_utf16`, `utf16_to_utf8`, `to_wstring<N>`, `to_utf8<N>` |
| `format.h` | `format<N>` and `format_to`, over coredll's `_snwprintf` |
| `optional.h` | `optional<T>` |
| `window.h` | `window<Derived>`, `run_message_loop`, `screen_rect`, `work_area_rect` (the screen less the taskbar) |
| `core.h` | `move`, `forward`, `exchange`, `swap` and a few type traits |

## Formatting

`jornada::format<N>(L"...", arguments...)` calls coredll's `_snwprintf` and returns a `wstring<N>`. The format is checked against the arguments at compile time:

```cpp
auto text = jornada::format<64>(L"%s: %d of %u, %.1f%%", name, done, total, percent);
jornada::format<64>(L"%d", L"text");     // error: format_argument_does_not_match_its_conversion
jornada::format<64>(L"%d", bytes);       // error: format_64_bit_integer_needs_the_I64_prefix (bytes is a long long)
jornada::format<8>(L"Total: %d", total); // error: format_output_may_not_fit_in_the_capacity
```

Conversions are `%[flags][width][.precision][h|l|L|I64]type`, with flags from `-`, `+`, space, `#` and `0`:

- `d`, `i`, `u`, `o`, `x`, `X`: integers or enums up to 32 bits, or 64 bits with `I64` (`%I64d`)
- `c`, `C`: a character
- `s`: a wide string, `const wchar_t *` or `wstring<N>`; `S` or `hs`: a narrow string, `const char *` or `string<N>`
- `e`, `E`, `f`, `g`, `G`: a `float` or `double`
- `p`: a pointer

`*` widths and precisions, and `%n`, are compile errors. A format whose longest output wouldn't fit in N - 1 characters is a compile error, except `%f` and strings without a precision, whose length depends on the value. Those are cut off at N - 1 characters, and `format_to` returns false when that happens.

## Windows

`window<Derived>` registers a class and creates a window whose messages go to `Derived`'s handlers. Declare the ones you want, public:

```cpp
#include <jornada/cxx/window.h>

namespace {

class main_window : public jornada::window<main_window> {
public:
    static constexpr const wchar_t *class_name = L"MainWindow";

    void on_paint(jornada::paint_dc &dc) {
        dc.draw_text(L"Hello", client_rect(), DT_CENTER);
    }

    void on_destroy() {
        PostQuitMessage(0);
    }
};

}

int WINAPI WinMain(HINSTANCE instance, HINSTANCE previous, LPWSTR command_line, int show) {
    main_window window;
    if (!main_window::register_class(instance) || !window.create(instance, L"Hello", WS_VISIBLE | WS_CAPTION | WS_SYSMENU, jornada::work_area_rect())) {
        return 1;
    }
    return jornada::run_message_loop();
}
```

Handlers are `on_create`, `on_paint(paint_dc &)`, `on_tap(point)`, `on_key(UINT)`, `on_command(WORD id, WORD code, HWND control)`, `on_destroy` and `on_message(UINT, WPARAM, LPARAM, LRESULT &)` for anything else; `window.h` says what each gets and returns. A handler that isn't public isn't found, and its message goes to `DefWindowProcW`.

Put a window class used in one file in an unnamed namespace, as above. Its functions are then local to the file, so the compiler inlines them into the window procedure instead of keeping them as separate functions.

The object stores itself in the window's extra bytes, so it must outlive the window. Its destructor destroys a window that's still open.
