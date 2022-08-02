// mem_offset_test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

struct X
{
    int     x;
    int     y;
    long    z;
};

template <typename C, typename T1, typename T2, T1 C::*P1, T1 C::*P2>
struct MemOrder
{
    MemOrder()
    {
        int i = (void*)P1 < (void*)P2;
    }

//  enum { value = (P1 < P2) };
};

int _tmain(int argc, _TCHAR* argv[])
{
    union U
    {
        int i;
        int X::*p;
    } u;

    u.p =   &X::x;

    MemOrder<X, int, int, &X::x, &X::y> p1;

    return 0;
}

