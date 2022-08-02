
#include <stddef.h>

int do_stuff(int volatile *pi)
{
    int r   =   0;
#if 1
    int i;
    for(i = 0; i < 10000/* 00000 */; ++i)
    {
        if(i ^ *pi)
        {
            ++r;
        }
    }
#endif /* 1 */

    return r;
}