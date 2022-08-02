// Beginning Game Programming, Third Edition
// Chapter 1 - HelloWorld program

#include <windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nShowCmd)
{
    MessageBox(NULL, "Motoko Kusanagi has hacked your system!",
        "Public Security Section 9", MB_OK | MB_ICONEXCLAMATION);
}

