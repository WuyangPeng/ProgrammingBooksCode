/*
 *  Copyright © 1997-2002 Metrowerks Corporation.  All Rights Reserved.
 *
 *  Questions and comments to:
 *       <mailto:support@metrowerks.com>
 *       <http://www.metrowerks.com/>
 */

#include <iostream>

////////////////////////////////////////////////////////////////////////////////

class Parent1
{
public:
    Parent1(int )
    {}
};

class Child1
    : public Parent1
{
public:
    Child1(int i)
     : Parent1(i)
    {}
};

////////////////////////////////////////////////////////////////////////////////

class Parent2
{
public:
    Parent2(int )
    {}
};

class Intermediate2a
    : public virtual Parent2
{
public:
    Intermediate2a(int i)
        : Parent2(i)
    {}
};

class Intermediate2b
    : public virtual Parent2
{
public:
    Intermediate2b(int i)
        : Parent2(i)
    {}
};

class Child2
    : public Intermediate2a
    , public Intermediate2b
{
public:
    Child2(int i)
        : Intermediate2a(i)
        , Intermediate2b(i)
        , Parent2(i)
    {}
};

////////////////////////////////////////////////////////////////////////////////

class Child3
{
public:
    Child3(int i)
        : m_i(i)
    {}

    int const m_i;
};

////////////////////////////////////////////////////////////////////////////////

class Child4
{
public:
    Child4(int &i)
        : m_i(i)
    {}

    int &m_i;
};

////////////////////////////////////////////////////////////////////////////////

class Child5
{
public:
    Child5(int i)
        : m_i(i)
    {}

    int m_i;
};

////////////////////////////////////////////////////////////////////////////////

class Child6
{
public:
    Child6(int i)
    {
        memset(m_array, i, sizeof(m_array));
    }

    int m_array[10];
};

////////////////////////////////////////////////////////////////////////////////

int g_array[10];

class Child7
{
public:
    Child7(int i)
//      : m_array({ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 })
//      : m_array(g_array)
    {
        typedef int array_10_t[10];
        
        array_10_t  array = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

//      m_array = array;        
//      memset(m_array, i, sizeof(m_array));
    }

    int /*const*/ m_array[10];
};

////////////////////////////////////////////////////////////////////////////////

struct X
{
    X()
        : m_r(m_i)
        , m_i(1)
    {}
    
public:
    
};

////////////////////////////////////////////////////////////////////////////////

int main()
{
    int     i   =   99;

    Child1  child1(0);
    Child2  child2(0);
    Child3  child3(0);
    Child4  child4(i);
    Child5  child5(i);
    Child6  child6(i);
    
    return 0;
}

