/* /////////////////////////////////////////////////////////////////////////////
 * File:        Templ_ctor.cpp
 *
 * Purpose:     templ_ctor main implementation file.
 *
 * Created:     14th January 2003
 * Updated:     14th January 2003
 *
 * Copyright:   Synesis Software Pty Ltd, (c) 1999-2003. All rights reserved.
 *
 * Home:        www.synesis.com.au/software
 *
 * ////////////////////////////////////////////////////////////////////////// */


#include <vector>
#include <string>

#include <stdio.h>
/*
void printf(char const *, ...)
{}
*/

/* ////////////////////////////////////////////////////////////////////////// */

class Heavy
{
public:
    explicit Heavy(int i = 1)
        : m_value(i)
    {
        printf("Heavy(): 0x%08x\n", this);
    }
    Heavy(Heavy const &rhs)
        : m_value(100 + rhs.m_value)
    {
        printf("Heavy(Heavy const &): 0x%08x\n", this);
    }
    ~Heavy()
    {
        printf("~Heavy(): 0x%08x\n", this);
    }

    Heavy &operator =(Heavy const &)
    {
        printf("&operator =(Heavy const &): 0x%08x\n", this);

        return *this;
    }

public:
    int m_value;
};

class Base
{
public:
    Base(Heavy const &src)
        : m_value(src.m_value)
    {
        printf("Base(Heavy const &src): 0x%08x, 0x%08x: %d\n", this, &src, src.m_value);
    }
    Base(int const &i)
        : m_value(i)
    {
        printf("Base(Heavy const &src): 0x%08x, 0x%08x: %d\n", this, 0, i);
    }
    Base(Heavy const *src)
        : m_value(src->m_value)
    {
        printf("Base(Heavy const *src): 0x%08x, 0x%08x: %d\n", this, src, src->m_value);
    }
    ~Base()
    {
        printf("~Base(): 0x%08x, %d\n", this, m_value);
    }

private:
    int const &m_value;
};


template <typename T>
struct argument_proxy
{
public:
    argument_proxy(T &t)
        : m_t(t)
    {}

    operator T &() const
    {
        return m_t;
    }

protected:
    T   &m_t;
};

template <typename T>
struct argument_proxy<T*>
{
public:
    argument_proxy(T *t)
        : m_t(t)
    {}

    operator T *() const
    {
        return m_t;
    }

protected:
    T   *m_t;
};

template <typename T>
struct argument_proxy<T const *>
{
public:
    argument_proxy(T const *t)
        : m_t(t)
    {}

    operator T const *() const
    {
        return m_t;
    }

protected:
    T const *m_t;
};

template <typename T>

template <typename B>
class DerivedBoltin
    : public B
{
public:
#if 1
  template <typename T1>
  DerivedBoltin(T1 &t1)
    : B(t1)
  {}
  template <typename T1>
  DerivedBoltin(T1 *t1)
    : B(t1)
  {}
#else
  template <typename T1>
  DerivedBoltin(argument_proxy<T1> t1)
    : B(t1)
  {}
#endif /* 0 */
};


/* ////////////////////////////////////////////////////////////////////////// */

int main(int /* argc */, char ** /*argv*/)
{
    Heavy const         sv;
    int const           i   =   33;
    int const *const    ri  =   &i;

    printf("\nBy ptr\n");
    DerivedBoltin<Base> derived1(&sv);
//  DerivedBoltin<Base> derived1(argument_proxy<Heavy const *>(&sv));

    printf("\nBy ref\n");
    DerivedBoltin<Base> derived2(sv);

    printf("\nliteral\n");
    DerivedBoltin<Base> derived3(i);

    printf("\nint\n");
    DerivedBoltin<Base> derived4(i/*Heavy()*/);

    printf("\nint\n");
    DerivedBoltin<Base> derived5(*ri);

    printf("\ntemp Heavy\n");
    Heavy   h(999);
    DerivedBoltin<Base> derived6(h);

    printf("\n");

    return 0;
}

/* ////////////////////////////////////////////////////////////////////////// */
