
#include <stdio.h>

#ifdef _MSC_VER
# include <iostream>
#endif /* _MSC_VER */

enum
{
    big = 0x1234567812345678
//        0x  12FFC012345678
};

int main()
{
#if defined(__DMC__) || \
    defined(__MWERKS__) || \
    defined(__WATCOMC__)
    printf("%lld\n", big);
#elif defined(__GNUC__) || \
      defined(_MSC_VER)
    __int64 i32 = big;

#ifdef _MSC_VER
    std::cout << (__int64)big << std::endl;
#endif /* _MSC_VER */

//  __int64 i64 = big;
//  __int32 i32 = big;
    printf("%I64d\n", big);
#if 0
    __int32 lo = i64;
    __int32 hi = i64 >> 32;
    printf("0x%08x%08x\n", hi, lo);

    i64 = (((__int64)hi) << 32) | lo;
    printf("%I64d\n", i64);
#endif /* 0 */

#else
# error Compiler not recognised
#endif /* */

    return 0;
}

// 1311768465173141112
