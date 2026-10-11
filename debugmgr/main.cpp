#include <windows.h>
#include <winsock.h>

#include <jornada/cxx/format.h>
#include <jornada/cxx/window.h>

#include "device_ce.h"
#include "server.h"

namespace {

constexpr UINT status_changed = WM_APP;
constexpr UINT_PTR address_timer = 1;
constexpr UINT address_refresh_milliseconds = 3000;
constexpr int window_width = 420;
constexpr int window_height = 150;
constexpr int margin = 8;

struct status_snapshot {
    bool listening = false;
    bool failed = false;
    bool connected = false;
    uint32_t client = 0;
    unsigned requests = 0;
    uint16_t last_command = 0;
    uint32_t last_status = 0;
};

struct shared_status {
    CRITICAL_SECTION lock;
    status_snapshot state;
};

jornada::wstring<48> dotted(uint32_t address) {
    return jornada::format<48>(L"%u.%u.%u.%u", address >> 24, (address >> 16) & 0xFF, (address >> 8) & 0xFF, address & 0xFF);
}

jornada::wstring<96> local_addresses() {
    jornada::wstring<96> result;
    char name[64];
    if (gethostname(name, sizeof(name)) != 0) {
        return result;
    }
    hostent *host = gethostbyname(name);
    if (!host) {
        return result;
    }
    for (int index = 0; host->h_addr_list[index]; index++) {
        const uint8_t *bytes = reinterpret_cast<const uint8_t *>(host->h_addr_list[index]);
        uint32_t address = static_cast<uint32_t>(bytes[0]) << 24 | bytes[1] << 16 | bytes[2] << 8 | bytes[3];
        if (!result.empty()) {
            result.append(L", ");
        }
        result.append(dotted(address));
    }
    return result;
}

class status_window : public jornada::window<status_window> {
public:
    static constexpr const wchar_t *class_name = L"JornadaDebugManager";

    status_window(shared_status &status, uint16_t port) : status(status), port(port) {}

    bool on_create() {
        addresses = local_addresses();
        SetTimer(handle(), address_timer, address_refresh_milliseconds, nullptr);
        return true;
    }

    void on_paint(jornada::paint_dc &dc) {
        EnterCriticalSection(&status.lock);
        status_snapshot now = status.state;
        LeaveCriticalSection(&status.lock);

        jornada::wstring<160> listening;
        if (now.failed) {
            listening = jornada::format<160>(L"Can't listen on port %u", static_cast<unsigned>(port));
        } else if (addresses.empty()) {
            listening = jornada::format<160>(L"Listening on port %u, no network address yet", static_cast<unsigned>(port));
        } else {
            listening = jornada::format<160>(L"Connect to %s port %u", addresses, static_cast<unsigned>(port));
        }
        jornada::wstring<64> connection = now.connected ? jornada::format<64>(L"Connected to %s", dotted(now.client))
                                                        : jornada::wstring<64>(L"Waiting for a connection");
        jornada::wstring<96> activity = now.requests == 0 ? jornada::wstring<96>(L"No requests yet")
                                                          : jornada::format<96>(L"%u requests, last %S: %s", now.requests,
                                                                                debugmgr::command_name(now.last_command),
                                                                                now.last_status ? L"failed" : L"done");

        RECT area = client_rect();
        area.left += margin;
        area.top += margin;
        area.right -= margin;
        int line = dc.text_height();
        for (const wchar_t *text : {listening.c_str(), connection.c_str(), activity.c_str()}) {
            dc.draw_text(text, area, DT_LEFT | DT_SINGLELINE);
            area.top += line + 2;
        }
        area.top += line / 2;
        dc.draw_text(L"Anything that can reach this port can copy files to this device and run programs. Close this window to stop.", area,
                     DT_LEFT | DT_WORDBREAK);
    }

    bool on_message(UINT message, WPARAM wparam, LPARAM lparam, LRESULT &result) {
        if (message == status_changed) {
            invalidate();
            result = 0;
            return true;
        }
        if (message == WM_TIMER && wparam == address_timer) {
            jornada::wstring<96> refreshed = local_addresses();
            if (refreshed.view() != addresses.view()) {
                addresses = refreshed;
                invalidate();
            }
            result = 0;
            return true;
        }
        return false;
    }

    void on_destroy() {
        KillTimer(handle(), address_timer);
        PostQuitMessage(0);
    }

private:
    shared_status &status;
    uint16_t port;
    jornada::wstring<96> addresses;
};

struct server_context {
    shared_status *status;
    HWND window;
    uint16_t port;
};

void record(void *context, const debugmgr::report &happened) {
    server_context &server = *static_cast<server_context *>(context);
    EnterCriticalSection(&server.status->lock);
    switch (happened.kind) {
    case debugmgr::event::listening:
        server.status->state.listening = true;
        break;
    case debugmgr::event::listen_failed:
        server.status->state.failed = true;
        break;
    case debugmgr::event::connected:
        server.status->state.connected = true;
        server.status->state.client = happened.address;
        break;
    case debugmgr::event::disconnected:
        server.status->state.connected = false;
        break;
    case debugmgr::event::request:
        server.status->state.requests++;
        server.status->state.last_command = happened.command;
        server.status->state.last_status = happened.status;
        break;
    }
    LeaveCriticalSection(&server.status->lock);
    PostMessageW(server.window, status_changed, 0, 0);
}

DWORD WINAPI run_server(void *parameter) {
    server_context &server = *static_cast<server_context *>(parameter);
    debugmgr::ce_device device;
    if (debugmgr::serve(server.port, device, _WIN32_WCE, record, &server)) {
        PostMessageW(server.window, WM_CLOSE, 0, 0);
    }
    return 0;
}

}

int WINAPI WinMain(HINSTANCE instance, HINSTANCE previous, LPWSTR command_line, int show) {
    long requested_port = _wtol(command_line);
    uint16_t port = requested_port > 0 && requested_port < 65536 ? static_cast<uint16_t>(requested_port) : debugmgr::default_port;

    WSADATA winsock;
    if (WSAStartup(MAKEWORD(1, 1), &winsock) != 0) {
        MessageBoxW(nullptr, L"Winsock isn't available.", L"debugmgr", MB_OK | MB_ICONERROR);
        return 1;
    }

    shared_status status;
    InitializeCriticalSection(&status.lock);
    status_window window(status, port);
    RECT area = jornada::work_area_rect();
    int left = area.left + (area.right - area.left - window_width) / 2;
    int top = area.top + (area.bottom - area.top - window_height) / 2;
    if (!status_window::register_class(instance) ||
        !window.create(instance, L"debugmgr", WS_VISIBLE | WS_CAPTION | WS_SYSMENU, RECT{left, top, left + window_width, top + window_height})) {
        return 1;
    }

    server_context server{&status, window.handle(), port};
    HANDLE thread = CreateThread(nullptr, 0, run_server, &server, 0, nullptr);
    if (!thread) {
        return 1;
    }
    CloseHandle(thread);
    int result = jornada::run_message_loop();
    WSACleanup();
    return result;
}
