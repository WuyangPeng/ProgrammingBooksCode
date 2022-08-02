// mil_ex_test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <stdexcept>

class X
{
public:
    X(int n)
    try
        : m_n(n)
        , m_p1(new __int8[200])
        , m_p2(new __int8[n])
    {
        printf("ctor body\n");
    }
    catch(std::bad_alloc &x)
    {
        printf("ctor-catch clause\n");
        printf("m_p1: %p, m_p2: %p\n", m_p1, m_p2);

        puts(x.what());

        throw;
    }

    void * operator new(size_t cb)
    {
        void    *pv =   ::operator new(cb);

        memset(pv, 0, cb);

        return pv;
    }

public:
    int     m_n;
    __int8  *m_p1;
    __int8  *m_p2;
};

int _tmain(int argc, _TCHAR* argv[])
{
    try
    {
#if 1
        X   x(0x70000000);
#else
        X   &x = *new X(0x70000000);
#endif

        printf("Succeeded\n");
    }
    catch(std::bad_alloc &x)
    {
        puts(x.what());
    }

    return 0;
}

