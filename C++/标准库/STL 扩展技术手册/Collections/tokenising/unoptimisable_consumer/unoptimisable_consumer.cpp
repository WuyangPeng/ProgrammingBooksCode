// unoptimisable_consumer.cpp : Defines the entry point for the DLL application.
//

//#include "windows.h"

int __stdcall DllMain(void *, unsigned long, void *)
{
    return 1;
}

extern "C" void __declspec(dllexport) consume_string(char const *s, size_t len)
{
	((void)s);
	((void)len);
}
