#ifndef CPSWINDOWSAPITOOLS_H
#define CPSWINDOWSAPITOOLS_H

#ifdef _WIN32
#include <dwmapi.h>
#pragma comment(lib, "dwmapi.lib")
#endif

namespace CPS{

template <typename T>
void setWindowsThemeToDark(T &window){
#ifdef _WIN32
    const bool dark = true;
    const int value = dark ? 1 : 0;
    DwmSetWindowAttribute((HWND)window.winId(), 19, &value, sizeof(value));
#endif
}

} // end of CPS

#endif // CPSWINDOWSAPITOOLS_H
