#include <windows.h>
#include <stdlib.h>
#include <string>
#include <tchar.h>
#include <gdiplus.h>
#include "Buttons.h"
#include "Images.h"
#pragma comment (lib,"Gdiplus.lib")
using namespace std;

using namespace Gdiplus;

static TCHAR szWindowClass[] = _T("DesktopApp");

static TCHAR szTitle[] = _T("E-DOG");

HINSTANCE hInst;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HWND welcomebutton,sitbutton,standbutton,eatbutton,playbutton,aboutbutton;

string dog_status = "stand";

int eyetime = 1;


int WINAPI WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR     lpCmdLine,
    _In_ int       nCmdShow
)
{
    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR           gdiplusToken;

    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(wcex.hInstance, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

    if (!RegisterClassEx(&wcex)) {
        MessageBox(NULL,
            _T("Call to RegisterClassEx failed!"),
            _T("Windows Desktop Guided Tour"),
            NULL);

        return 1;
    }

    hInst = hInstance;

    HWND hWnd = CreateWindowEx(
        WS_EX_OVERLAPPEDWINDOW,
        szWindowClass,
        szTitle,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        1920,1080,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (!hWnd) {
        MessageBox(NULL,
            _T("Call to CreateWindow failed!"),
            _T("Windows Desktop Guided Tour"),
            NULL);

        return 1;
    }

    welcomebutton = CreateWelcomeButton(hWnd,hInst);
    aboutbutton = CreateAboutButton(hWnd,hInst);

    ShowWindow(hWnd,
        nCmdShow);
    UpdateWindow(hWnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    PAINTSTRUCT ps;
    HDC hdc;

    switch (message) {
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        WelcomeImage(hdc);
        EndPaint(hWnd, &ps);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_COMMAND:
        {
            switch (LOWORD(wParam)) {
            case 1001:
                sitbutton = CreateSitButton(hWnd,hInst);
                standbutton = CreateStandButton(hWnd,hInst);
                eatbutton = CreateEatButton(hWnd,hInst);
                playbutton = CreatePlayButton(hWnd,hInst);
                SetTimer(hWnd,(UINT_PTR)2001,500,(TIMERPROC)NULL);
                DestroyWindow(welcomebutton);
                break;
            case 1002:
                dog_status = "sit";
                break;
            case 1003:
                dog_status = "stand";
                break;
            case 1004:
                MessageBox(hWnd, _T("¹þ"), _T("ºÇ"), MB_OK | MB_ICONINFORMATION);
                break;
            case 1005:
                MessageBox(hWnd, _T("¹þ"), _T("ºÙ"), MB_OK | MB_ICONINFORMATION);
                break;
            case 1006:
                MessageBox(hWnd,_T("E-DOG 1.0"),_T("¹ØÓÚ"), MB_OK | MB_ICONINFORMATION);
            }
        }
        return DefWindowProc(hWnd, message, wParam, lParam);
    case WM_TIMER:
        switch (wParam)
        {
        case 2001:
            HDC hdc_temp;
            hdc_temp = GetDC(hWnd);
            eyetime++;
            if (dog_status == "stand") {
                if (eyetime % 2) StandEyeClosedImage(hdc_temp);
                else StandEyeOpenedImage(hdc_temp);
            }
            else if (dog_status == "sit") {
                if (eyetime % 2) SitEyeClosedImage(hdc_temp);
                else SitEyeOpenedImage(hdc_temp);
            }
            if (eyetime == 32767) eyetime = 1;
        }
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }
    return 0;
}