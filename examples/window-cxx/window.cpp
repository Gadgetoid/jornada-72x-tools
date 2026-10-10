#include <jornada/cxx/format.h>
#include <jornada/cxx/optional.h>
#include <jornada/cxx/window.h>

namespace {

class tap_window : public jornada::window<tap_window> {
public:
    static constexpr const wchar_t *class_name = L"JornadaExampleWindowCxx";

    void on_paint(jornada::paint_dc &dc) {
        auto text = jornada::format<64>(L"Taps: %d\nTap anywhere, Esc to quit", tap_count);
        dc.draw_text(text, client_rect(), DT_CENTER | DT_WORDBREAK);
        if (last_tap) {
            dc.ellipse({last_tap->x - mark_size, last_tap->y - mark_size, last_tap->x + mark_size, last_tap->y + mark_size});
        }
    }

    void on_tap(jornada::point where) {
        tap_count++;
        last_tap = where;
        invalidate();
    }

    void on_key(UINT key) {
        if (key == VK_ESCAPE) {
            destroy();
        }
    }

    void on_destroy() {
        PostQuitMessage(0);
    }

private:
    static constexpr int mark_size = 6;

    int tap_count = 0;
    jornada::optional<jornada::point> last_tap;
};

}

int WINAPI WinMain(HINSTANCE instance, HINSTANCE previous, LPWSTR command_line, int show) {
    tap_window window;
    if (!tap_window::register_class(instance) || !window.create(instance, L"Window", WS_VISIBLE | WS_CAPTION | WS_SYSMENU, jornada::work_area_rect())) {
        return 1;
    }
    window.focus();
    return jornada::run_message_loop();
}
