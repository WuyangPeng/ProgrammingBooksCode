
#include <stdio.h>

extern "C"
__declspec(dllimport) char const 
//__stdcall 
*dm_fn(int);

int main()
{
    printf(dm_fn(0));

    return 0;
}

