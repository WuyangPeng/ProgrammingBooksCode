
#include "load_order.h"
#include <stdlib.h>

static struct LoadOrder loadOrder(__FILE__);

void (*s_fn)();

__declspec(dllexport) void funcB(void (*pfn)())
{
    atexit(pfn);

    s_fn = pfn;

    printf("funcB()\n");
}



struct TwoGone
{
    ~TwoGone()
    {
        printf("2 is now unloaded\n");

        s_fn();
    }

} twogone;

int __stdcall DllMain(void *, unsigned reason, void *)
{
    if(0 == reason)
    {
        printf("Unloading DllMain(2)\n");
    }

    return 1;
}
