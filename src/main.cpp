#define WIN32_LEAN_AND_MEAN

#include <iostream>
#include <windows.h>
#include <vector>

const int WIDTH = 800;
const int HEIGHT = 600;
const int BYTES = 4;


std::vector<unsigned char> framebuffer;


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {

    switch (msg) {

        case WM_PAINT: {

            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            RECT rect{};
            GetClientRect(hwnd, &rect);


            HBRUSH blackBrush = CreateSolidBrush(RGB(0, 0, 0));
            FillRect(hdc, &ps.rcPaint, blackBrush);

            DeleteObject(blackBrush);
            EndPaint(hwnd, &ps);
            break;
        }

        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProcW(hwnd, msg, wParam, lParam);
    }

    return 0;
}

int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdline,
    int nCmdShow
)
{
    constexpr wchar_t className[] = L"myWindowClass";

    HBRUSH backgroundBrush = CreateSolidBrush(RGB(0, 0, 0));

    framebuffer.resize(WIDTH * HEIGHT * BYTES);

    

    WNDCLASSEXW wc{};

    wc.cbSize = sizeof(WNDCLASSEXW);
    wc.style = 0;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIconW(nullptr, MAKEINTRESOURCEW(32512));
    wc.hCursor = LoadCursorW(nullptr, MAKEINTRESOURCEW(32512));
    wc.hbrBackground = backgroundBrush;
    wc.lpszMenuName = nullptr;
    wc.lpszClassName = className;
    wc.hIconSm = LoadIconW(nullptr, MAKEINTRESOURCEW(32512));

    if (!RegisterClassExW(&wc)) {

        MessageBoxW(
            nullptr,
            L"Windows Registration Failed!",
            L"Error!",
            MB_ICONINFORMATION | MB_OK
        );

        DeleteObject(backgroundBrush);
        return 0;
    }

    HWND hwnd = CreateWindowExW(
        0,
        className,
        L"Nostos",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        WIDTH,
        HEIGHT,
        nullptr,
        nullptr,
        hInstance,
        nullptr
    );

    if (hwnd == nullptr) {

        MessageBoxW(
            nullptr,
            L"Create Window failed!",
            L"Error!",
            MB_ICONEXCLAMATION | MB_OK
        );

        UnregisterClassW(className, hInstance);
        DeleteObject(backgroundBrush);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg{};

    while (GetMessageW(&msg, nullptr, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    UnregisterClassW(className, hInstance);
    DeleteObject(backgroundBrush);

    return static_cast<int>(msg.wParam);
}