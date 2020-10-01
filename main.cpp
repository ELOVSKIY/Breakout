#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <windowsx.h>
#include <new>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>
using namespace std;

struct StateInfo {
    int clientWidth, clientHeight;
    int colCount, rowCount;
    vector<vector<string>> content;
};


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
    const wchar_t CLASS_NAME[] = L"Sample Window Class";

    WNDCLASS wc = { };

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    StateInfo* pState = new (std::nothrow) StateInfo;

    if (pState == NULL)
    {
        return 0;
    }

    HWND hwnd = CreateWindowEx(
            0,
            CLASS_NAME,
            L"Breakout",
            WS_OVERLAPPEDWINDOW,

            CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

            NULL,
            NULL,
            hInstance,
            pState
    );

    if (hwnd == NULL)
    {
        return 1;
    }

    ShowWindow(hwnd, nCmdShow);


    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

inline StateInfo* GetAppState(
        HWND hwnd)
{
    LONG_PTR ptr = GetWindowLongPtr(hwnd, GWLP_USERDATA);
    StateInfo* pState = reinterpret_cast<StateInfo*>(ptr);
    return pState;
}

LRESULT CALLBACK WindowProc(
        HWND hwnd,
        UINT uMsg,
        WPARAM wParam,
        LPARAM lParam)
{
    StateInfo* pState;
    if (uMsg == WM_CREATE)
    {
        CREATESTRUCT* pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
        pState = reinterpret_cast<StateInfo*>(pCreate->lpCreateParams);
        SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pState);

        RECT winRect;

        if (GetClientRect(hwnd, &winRect)) {
            pState->clientWidth = winRect.right - winRect.left;
            pState->clientHeight = winRect.bottom - winRect.top;
        }

    }
    else
    {
        pState = GetAppState(hwnd);
    }

    switch (uMsg)
    {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

            EndPaint(hwnd, &ps);
        }
            return 0;

        case WM_SIZE:
            pState->clientWidth = LOWORD(lParam);
            pState->clientHeight = HIWORD(lParam);
            return 0;

    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}