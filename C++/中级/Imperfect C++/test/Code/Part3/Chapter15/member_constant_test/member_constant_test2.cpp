
#include <stdio.h>


#include "member_constant_test.h"


extern "C" void mod2_fn()
{
    printf("mod2: &g_z.z == %p\n", &g_z.z);
//  printf("mod2: &Y::y == %p\n", &Y::y);
}
