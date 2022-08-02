/*
 *  Copyright © 1997-2002 Metrowerks Corporation.  All Rights Reserved.
 *
 *  Questions and comments to:
 *       <mailto:support@metrowerks.com>
 *       <http://www.metrowerks.com/>
 */

#include <iostream>


template <typename T>
struct simple_incrementer
{
    void operator ()(T &t)
    {
        ++t;
    }
};

template <typename T>
struct simple_decrementer
{
    void operator ()(T &t)
    {
        --t;
    }
};

template< typename T
        , typename A = simple_incrementer<T>
        , typename R = simple_decrementer<T>
        >
class increment_scope
{
public:
    typedef T                   value_type;
    typedef A                   aquire_type;
    typedef R                   release_type;
    typedef increment_scope<T>  class_type;
    typedef value_type          &reference;

public:
    explicit increment_scope(reference var)
        : m_var(var)
    {
        aquire_type()(m_var);
    }
    ~increment_scope()
    {
        release_type()(m_var);
    }

// Members
private:
    reference   m_var;

// Not to be implemented
private:
    increment_scope(class_type const &);    
    increment_scope const &operator =(class_type const &);  
};


int main()
{
    using namespace std;

    int     i   =   0;

    cout << "i: " << i << endl;
    {
        increment_scope<int>    is(i);
        
        cout << "i: " << i << endl;
    }   
    cout << "i: " << i << endl;
    
    cout << "i: " << i << endl;
    {
        increment_scope<int, simple_decrementer<int>, simple_incrementer<int> > is(i);
        
        cout << "i: " << i << endl;
    }   
    cout << "i: " << i << endl;
    
    return 0;
}

