#include <iostream>
#include <Windows.h>
using namespace std;

#include "App.h"

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

App* app;
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int main()
{
    // the handle for the window, filled by a function
    HWND hWnd;
    // this struct holds information for the window class
    WNDCLASSEX wc;

    // clear out the window class for use
    ZeroMemory(&wc, sizeof(WNDCLASSEX));

    // fill in the struct with the needed information
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_DBLCLKS | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = NULL;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.lpszClassName = L"MainWindow";

    // register the window class
    RegisterClassEx(&wc);

    RECT* lpRect = new RECT();
    lpRect->left = 260;
    lpRect->top = 150;
    lpRect->right = 2060;
    lpRect->bottom = 1150;

    const int cx = GetSystemMetrics(SM_CXBORDER);
    const int cy = GetSystemMetrics(SM_CYBORDER);
    lpRect->top -= cy;
    lpRect->left -= cx;
    lpRect->right += cx;
    lpRect->bottom += cy;
    

    // create the window and use the result as the handle
    hWnd = CreateWindowEx(NULL,
        L"MainWindow",    // name of the window class
        L"SVIT Browser",   // title of the window
        WS_OVERLAPPEDWINDOW,    // window style
        lpRect->left,    // x-position of the window
        lpRect->top,    // y-position of the window
        lpRect->right - lpRect->left,
        lpRect->bottom - lpRect->top,    // width of the window
        NULL,    // we have no parent window, NULL
        NULL,    // we aren't using menus, NULL
        NULL,    // application handle
        NULL);    // used with multiple windows, NULL

    LONG lStyle = GetWindowLong(hWnd, GWL_STYLE);
    lStyle &= ~(WS_CAPTION | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU);
    SetWindowLong(hWnd, GWL_STYLE, lStyle);

    // display the window on the screen
    ShowWindow(hWnd, SW_HIDE);

    RECT rc;
    GetWindowRect(hWnd, &rc);
    app = new App(hWnd, rc.right - rc.left, rc.bottom - rc.top);

    // this struct holds Windows event messages
    MSG msg = { 0 };

    // Enter the infinite message loop
    while (TRUE)
    {
        // Check to see if any messages are waiting in the queue
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            // translate keystroke messages into the right format
            TranslateMessage(&msg);

            // send the message to the WindowProc function
            DispatchMessage(&msg);

            // check to see if it's time to quit
            if (msg.message == WM_QUIT)
                break;
        }

        app->update(hWnd);
    }

    // return this part of the WM_QUIT message to Windows
    app->~App();
    UnregisterClass(L"MainWindow", NULL);
    return msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    // sort through and find what code to run for the message given
    switch (message)
    {
        // this message is read when the window is closed
    case WM_LBUTTONDOWN:
        POINT d;
        GetCursorPos(&d);
        ScreenToClient(hWnd, &d);
        app->mouseDown(d);
        break;
    case WM_LBUTTONUP:
        POINT u;
        GetCursorPos(&u);
        ScreenToClient(hWnd, &u);
        app->mouseUp(u);
        break;
    case WM_MOUSEWHEEL:
        app->mouseWheel(GET_WHEEL_DELTA_WPARAM(wParam));
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
        break;
    }

    // Handle any messages the switch statement didn't
    return DefWindowProc(hWnd, message, wParam, lParam);
}