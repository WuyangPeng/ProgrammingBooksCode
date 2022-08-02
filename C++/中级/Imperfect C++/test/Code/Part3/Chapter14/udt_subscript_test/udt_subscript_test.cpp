/* /////////////////////////////////////////////////////////////////////////////
 * File:        udt_subscript_test.cpp
 *
 * Purpose:     Implementation file for the udt_subscript_test project.
 *
 * Created:     15th October 2003
 * Updated:     20th October 2003
 *
 * Status:      Wizard-generated
 *
 * License:     (Licensed under the Synesis Software Open License)
 *
 *              Copyright (C) 1999-2003, Synesis Software Pty Ltd.
 *              All rights reserved.
 *
 *              www:        http://www.synesis.com.au/software
 *
 *              email:      software@synesis.com.au
 *
 *              This source code is placed into the public domain 2003
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

#define _STLSOFT_COMPILE_VERBOSE

#include <stlsoft.h>
#include <stlsoft_nulldef.h>
#include <stlsoft_constraints.h>

/* ////////////////////////////////////////////////////////////////////////// */

class PtrConv
{
public:
    PtrConv()
    {}
    explicit PtrConv(void *)
    {}
    PtrConv &operator =(void *)
    {
        return *this;
    }
    PtrConv operator *() /* const */
    {
        static PtrConv  s_pc(0);

        return s_pc;
    }
    PtrConv const &operator *() const
    {
        static PtrConv  s_pc(0);

        return s_pc;
    }
};

/* ////////////////////////////////////////////////////////////////////////// */

struct Big
{
    char ar[10];
};

template<typename U>
char func(U const *);

Big func( ...);


#if 0

template<typename T>
struct is_pointer_type
{
    enum { result = sizeof( func(T) ) == 1 };

    ~is_pointer_type()
    {
        do
        {
            typedef int ai[(1 == sizeof(func(T))) ? 1 : 0];
        } while(0);
    }
};
#endif /* 0 */

/* ////////////////////////////////////////////////////////////////////////// */

template <typename T>
struct must_be_subscriptable
{
public:
    ~must_be_subscriptable()
    {
        void    (*pfn)(T const &) = constraints;

        ((void)pfn);
    }
private:
    static void constraints(T const &t)
    {
        // The compiler will bring you here if T is not subscriptable
        sizeof(t[0]);
    }
};

template <typename T>
struct must_subscript_as_decayable_pointer
    : must_be_subscriptable<T>
{
public:
    ~must_subscript_as_decayable_pointer()
    {
        void    (*pfn)(T const &) = constraints;

        ((void)pfn);
    }
private:
    static void constraints(T const &t)
    {
        // The compiler will bring you here if T has a user-defined 
        // subscript operator.
        sizeof(0[t]);
    }
};

// Built-in array/pointer
// UDT with implicit conversion to pointer
// UDT with subscript operator
// UDT with both subscript operator and implicit conversion to pointer

template <typename T>
void subscript(T const &t)
{
//  must_subscript_as_decayable_pointer<T>  x;

  sizeof(t[0]); // Compiler will balk here if T is not subscriptable
  sizeof(0[t]); // Compiler will balk here if T only has user-defined subscript operator
}

void subscript(void const * )
{}

void subscript(void * )
{}

struct Pointer
{
  operator short *() const
  {
    static short s_i;
    return &s_i;
  }
};

struct Subscript
{
  int operator [](size_t offset) const
  {
    return 0;
  }
#if 0
  operator short *() const
  {
    static short s_i;
    return &s_i;
  }
#endif /* 0 */
};

int main(int /* argc */, char ** /*argv*/)
{
    puts("udt_subscript_test: " __STLSOFT_COMPILER_LABEL_STRING);

  void        *pv = &pv;
  void const  *pcv = pv;
  int         ai[100];
  int         *pi = ai;
  Pointer     ptr;
  Subscript   subscr;

  subscript(pv);
  subscript(pcv);
  subscript(ai);
  subscript(pi);
  subscript(ptr);
//  subscript(subscr);

#if 1
    stlsoft::is_pointer_type<void*>     x1;
//  stlsoft::is_pointer_type<int>       x2;
//  stlsoft::is_pointer_type<PtrConv>   x3;

//  stlsoft::is_pointer_type<PtrConv>::constraints();
#else /* ? 0 */
    is_pointer_type<void*>      x1;
//  is_pointer_type<int>        x2;
    is_pointer_type<PtrConv>    x3;
#endif /* 0 */

    ((void)pv);

    return 0;
}

/* ////////////////////////////////////////////////////////////////////////// */
