
#include <stddef.h>

int null_func_enter(void *pv)
{
    return NULL != pv;
}

int null_func_leave(void *pv)
{
    return NULL != pv;
}

int do_stuff(int volatile *pi)
{
    int r   =   0;

#if 1
    int i;
    for(i = 0; i < 1000/* 000 */; ++i)
    {
        if(i ^ *pi)
        {
            ++r;
        }
    }
#endif /* 1 */

    return r;
}