
#include <stdio.h>

struct X
{
    static const int    x/*     =   10 */;
};

int main()
{
    printf("X::x: %d\n", X::x);

    return X::x;
}

#ifdef __VECTORC__
int X::x = 10;
#endif /* __VECTORC__ */
