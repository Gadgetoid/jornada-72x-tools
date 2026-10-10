#include <windows.h>

int WINAPI WinMain(HINSTANCE instance, HINSTANCE previous, LPWSTR command_line, int show) {
    MessageBoxW(0, L"Hello from jornada-72x-tools!", L"Hello", MB_OK | MB_ICONINFORMATION);
    return 0;
}
