
#include "RoboCatPCH.h"

#if _WIN32
int WINAPI WinMain([[maybe_unused]] _In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, [[maybe_unused]] _In_ int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
}
#else
const char** __argv;
int __argc;
int main(int argc, const char** argv)
{
    __argc = argc;
    __argv = argv;
}
#endif
