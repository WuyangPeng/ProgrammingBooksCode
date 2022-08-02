
#include <windows.h>

void f(short )
{}

void f(long )
{}

#define SASSERT(x)  do { int i[x]; } while(0)

const long THE_NUMBER = 65536;

int main()
{
#if 0
    SASSERT(1);

    SASSERT(sizeof(short) == 2);
    SASSERT(sizeof(int) == 2);
    SASSERT(sizeof(long) == 4);

    SASSERT(sizeof(short) <= sizeof(int));
    SASSERT(sizeof(int) <= sizeof(long));

    SASSERT(sizeof(4242) == 2);
    SASSERT(sizeof(65536) == 4);
#endif /* 0 */

    f(65536);
//  f(THE_NUMBER);

    return 0;
}
