#include <windows.h>
#include <gdiplus.h>
#include "Images.h"
#pragma comment (lib,"Gdiplus.lib")

using namespace Gdiplus;

void WelcomeImage(HDC hdc) {
    Graphics graphics(hdc);
    Image welcome(L"EDOG_LOGO_START_SIT(200X200).png");
    graphics.DrawImage(&welcome, 450, 100, 400, 400);
}

void StandEyeClosedImage(HDC hdc) {
    Graphics graphics(hdc);
    Image standeyeclosed(L"EDOG_STAND_EYECLOSED(200X200).png");
    graphics.DrawImage(&standeyeclosed, 450, 100, 400, 400);
}

void StandEyeOpenedImage(HDC hdc) {
    Graphics graphics(hdc);
    Image standeyeopened(L"EDOG_STAND_YEE!(200X200).png");
    graphics.DrawImage(&standeyeopened, 450, 100, 400, 400);
}

void SitEyeClosedImage(HDC hdc) {
    Graphics graphics(hdc);
    Image siteyeclosed(L"EDOG_SIT_EYECLOSED(200X200).png");
    graphics.DrawImage(&siteyeclosed, 450, 100, 400, 400);
}

void SitEyeOpenedImage(HDC hdc) {
    Graphics graphics(hdc);
    Image siteyeopened(L"EDOG_SIT(200X200).png");
    graphics.DrawImage(&siteyeopened, 450, 100, 400, 400);
}