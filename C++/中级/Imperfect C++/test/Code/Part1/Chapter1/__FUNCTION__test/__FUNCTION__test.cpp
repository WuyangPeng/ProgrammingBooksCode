/* /////////////////////////////////////////////////////////////////////////////
 * File:        __FUNCTION__test.c
 *
 * Purpose:     Implementation file for the __FUNCTION__test project.
 *
 * Created:     17th March 2004
 * Updated:     17th March 2004
 *
 * Status:      Wizard-generated
 *
 * License:     (Licensed under the Synesis Software Open License)
 *
 *              Copyright (C) 1999-2004, Synesis Software Pty Ltd.
 *              All rights reserved.
 *
 *              www:        http://www.synesis.com.au/software
 *
 *              email:      software@synesis.com.au
 *
 *              This source code is placed into the public domain 2004
 *              by Synesis Software Pty Ltd. There are no restrictions
 *              whatsoever to your use of the software. 
 *
 *              This source code is provided by Synesis Software Pty Ltd "as is"
 *              and any warranties, whether expressed or implied, including, but
 *              not limited to, the implied warranties of merchantability and
 *              fitness for a particular purpose are disclaimed. In no event
 *              shall the Synesis Software Pty Ltd be liable for any direct,
 *              indirect, incidental, special, exemplary, or consequential
 *              damages (including, but not limited to, procurement of
 *              substitute goods or services; loss of use, data, or profits; or
 *              business interruption) however caused and on any theory of
 *              liability, whether in contract, strict liability, or tort
 *              (including negligence or otherwise) arising in any way out of
 *              the use of this software, even if advised of the possibility of
 *              such damage. 
 *
 *              Neither the name of Synesis Software Pty Ltd nor the names of
 *              any subdivisions, employees or agents of Synesis Software Pty
 *              Ltd, nor the names of any other contributors to this software
 *              may be used to endorse or promote products derived from this
 *              software without specific prior written permission. 
 *
 * ////////////////////////////////////////////////////////////////////////// */

#include <stdio.h>
#include <functional>
#include <stlsoft.h>

/* ////////////////////////////////////////////////////////////////////////// */

#ifndef __FUNCTION__
# define STLSOFT_STRINGIZE_(x)  #x
# define STLSOFT_STRINGIZE(x)   STLSOFT_STRINGIZE_(x)
# define __FUNCTION__           "function defined in " __FILE__ "(" STLSOFT_STRINGIZE(__LINE__) ")"
#endif /* __FUNCTION__ */

/* ////////////////////////////////////////////////////////////////////////// */

template<typename T>
struct call_is_valid
{
public:
    void operator ()(T *p) const
    {
        stlsoft_assert(p->is_valid());
    }
};

template<   typename R
        ,   typename T
        >
struct call_mem_fun_t
{
public:
    call_mem_fun_t(R (T::*pmf)())
        : m_pmf(pmf)
    {}

    void operator ()(T *p) const
    {
        stlsoft_assert((p->*m_pmf)());
    }

private:
    R (T::*m_pmf)();
};

template<   typename R
        ,   typename T
        >
inline call_mem_fun_t<R, T> call_mem_fun(R (T::*pmf)())
{
    return call_mem_fun_t<R, T>(pmf);
}


template<   typename T
        ,   typename F  =   call_is_valid<T>
        >
class check_invariant
{
public:
    check_invariant(T *p, F f = F())
        : m_p(p)
        , m_f(f)
    {
        m_f(m_p);
    }
    check_invariant(T &r, F f = F())
        : m_p(&r)
        , m_f(f)
    {
        m_f(m_p);
    }
    ~check_invariant()
    {
        m_f(m_p);
    }

private:
    T   *m_p;
    F   m_f;
};

class Thing
{
public:
    typedef Thing   class_type;

public:
    Thing()
    {}

public:
    bool is_valid()
    {
        return false;
    }

    int SomeMethod()
    {
//      check_invariant<class_type> check(this);
        check_invariant<class_type, call_mem_fun_t<bool, Thing> >   check(this, call_mem_fun(&Thing::is_valid));

        return -1;
    }
};

/* ////////////////////////////////////////////////////////////////////////// */

void some_func()
{
    printf("Function: %s\n", __FUNCTION__);
}

int main(/* int argc, char *argv[] */)
{
    /* . */
    Thing   t;

    some_func();

    t.SomeMethod();

    return 0;
}

/* ////////////////////////////////////////////////////////////////////////// */
