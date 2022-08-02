
#include "cmangle.h"

int MANGLE_CALLCONV cfunc()
{
    union
    {
        int     i;
        void    *pv;
    }   u;

    u.pv = &u.i;

    return u.i;
}
