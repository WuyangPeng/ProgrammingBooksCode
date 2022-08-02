
#include "stat_interdep.h"

int func2(int level)
{
    if(0 == level)
    {
        return 0;
    }
    else
    {
        return func1(level - 1);
    }
}

