#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <new>
#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include "game/Game.h"

using namespace std;

struct StateInfo {
    Game *game;
    int clientWidth, clientHeight;
    int colCount, rowCount;
    vector<vector<string>> content;
};


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow) {

    const wchar_t CLASS_NAME[] = L"Main Break Out Class";

    WNDCLASS wc = {};

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    StateInfo *pState = new(std::nothrow) StateInfo;

    if (pState == NULL) {
        return 0;
    }

    HWND hwnd = CreateWindowEx(
            0,
            CLASS_NAME,
            L"Breakout",
            WS_OVERLAPPED,

            CW_USEDEFAULT, CW_USEDEFAULT, 1920, 1080,

            NULL,
            NULL,
            hInstance,
            pState
    );

    if (hwnd == NULL) {
        return 1;
    }

    ShowWindow(hwnd, SW_SHOWMAXIMIZED);


    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

inline StateInfo *GetAppState(
        HWND hwnd) {
    LONG_PTR ptr = GetWindowLongPtr(hwnd, GWLP_USERDATA);
    StateInfo *pState = reinterpret_cast<StateInfo *>(ptr);
    return pState;
}

LRESULT CALLBACK WindowProc(
        HWND hwnd,
        UINT uMsg,
        WPARAM wParam,
        LPARAM lParam) {
    StateInfo *pState;
    if (uMsg == WM_CREATE) {
        CREATESTRUCT *pCreate = reinterpret_cast<CREATESTRUCT *>(lParam);
        pState = reinterpret_cast<StateInfo *>(pCreate->lpCreateParams);
        SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR) pState);

        RECT winRect;

        if (GetClientRect(hwnd, &winRect)) {
            pState->clientWidth = winRect.right - winRect.left;
            pState->clientHeight = winRect.bottom - winRect.top;
        }

    } else {
        pState = GetAppState(hwnd);
    }
//    pState->game->GetInput(uMsg, wParam, lParam);
    switch (uMsg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            pState->game->Draw(hdc);
//            FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
//            HDC memHdc = CreateCompatibleDC(hdc);
//            HBRUSH hbrush = CreateSolidBrush(RGB(200,200,200));
//            SelectObject(hdc,hbrush);
//            Rectangle(hdc, 200, 200, 500, 500);
//            DeleteObject(hbrush);

            EndPaint(hwnd, &ps);
        }
            return 0;

        case WM_SIZE:
            pState->clientWidth = LOWORD(lParam);
            pState->clientHeight = HIWORD(lParam);
            pState->game = new Game(pState->clientWidth, pState->clientHeight);
            return 0;

    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}