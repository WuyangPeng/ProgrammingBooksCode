

#define BUILDING_THING

#include "explicit_cpp_server.h"
#include <stdio.h>

void Thing::PublicMethod(char const *s)
{
    printf("Thing::PublicMethod(%s)\n", s);
}

void Thing::PrivateMethod(char const *s)
{
    printf("Thing::PrivateMethod(%s)\n", s);
}
