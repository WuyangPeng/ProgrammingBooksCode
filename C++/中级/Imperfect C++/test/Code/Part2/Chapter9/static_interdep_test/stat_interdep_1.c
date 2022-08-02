
#include "stat_interdep.h"

int func1(int level)
{
    if(0 == level)
    {
        return 0;
    }
    else
    {
        return func2(level - 1);
    }
}

