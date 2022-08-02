
#define MESS_WITH_DEF

#include "unique_test_incl.h"

extern int do_multiply(int i1, int i2)
{
    return multiply(i1, i2);
}

extern void *get_multiply()
{
    return multiply;
}