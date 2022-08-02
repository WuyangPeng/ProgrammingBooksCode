
#include "load_order.h"

static struct LoadOrder loadOrder(__FILE__);

void (*s_pfn)();

void funcA_()
{
    printf("funcA()\n");
}

__declspec(dllexport) void funcA()
{
    s_pfn();
}

// void funcB(void (*)());


int __stdcall DllMain(void *, unsigned reason, void *)
{
    if(1 == reason)
    {
        s_pfn = funcA_;
    }
    else if(0 == reason)
    {
        printf("Unloading DllMain(1)\n");

        s_pfn = NULL;
    }

    return 1;
}
