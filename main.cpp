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

//    Gdiplus::GdiplusStartupInput gdiplusStartupInput;
//    ULONG_PTR           gdiplusToken;
//    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

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


//    SetTimer(hwnd, 1, 100, NULL);
    MSG msg = {};
    bool active = true;
    while (active) {
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            if (msg.message == WM_QUIT){
                active = false;
            }
        }

        if (pState->game) {
            pState->game->Click();
        }
        InvalidateRect(hwnd, NULL, true);
        UpdateWindow(hwnd);
        Sleep(1000 / 120);
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
        HWND hWnd,
        UINT uMsg,
        WPARAM wParam,
        LPARAM lParam) {
    StateInfo *pState;
    if (uMsg == WM_CREATE) {
        CREATESTRUCT *pCreate = reinterpret_cast<CREATESTRUCT *>(lParam);
        pState = reinterpret_cast<StateInfo *>(pCreate->lpCreateParams);
        SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR) pState);

        RECT winRect;

        if (GetClientRect(hWnd, &winRect)) {
            pState->clientWidth = winRect.right - winRect.left;
            pState->clientHeight = winRect.bottom - winRect.top;
        }

    } else {
        pState = GetAppState(hWnd);
    }

    if (pState && pState->game) {
        pState->game->GetInput(hWnd, uMsg, lParam, wParam);
    }
    switch (uMsg) {

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        case WM_PAINT: {


            pState->game->Draw(hWnd);


        }
            return 0;

        case WM_SIZE:
            pState->clientWidth = LOWORD(lParam);
            pState->clientHeight = HIWORD(lParam);
            pState->game = new Game(hWnd, pState->clientWidth, pState->clientHeight);
            return 0;

    }
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}