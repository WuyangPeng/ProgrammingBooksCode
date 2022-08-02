/* /////////////////////////////////////////////////////////////////////////////
 * File:        ptr_cast_test.cpp
 *
 * Purpose:     Implementation file for the ptr_cast_test project.
 *
 * Created:     20th December 2003
 * Updated:     21st December 2003
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

#include <stlsoft.h>
#include <stlsoft_meta.h>
#include <stlsoft_type_traits.h>
#include <stlsoft_ptr_cast.h>

#include <exception>
#include <stdexcept>
#include <typeinfo>

/* ////////////////////////////////////////////////////////////////////////// */

class A
{
public:
    virtual ~A()
    {}
};

class B
    : public A
{};

class D
    : public B
{
public:
    D()
    {
        printf("D::D()\n");
    }
    D(D const &)
    {
        printf("D::D(D const &)\n");
    }
};

class X
{};

/* ////////////////////////////////////////////////////////////////////////// */

void test_same(A const &)
{
    printf("is A\n");
}

void test_same(...)
{
    printf("is not A\n");
}

/* ////////////////////////////////////////////////////////////////////////// */

#if 0
template <typename TO, typename FROM>
inline TO ptr_cast_impl(one_t const &
{
}

template <typename TO, typename FROM>
inline TO ptr_cast<FROM &from>
{
    return ptr_cast_impl<TO, FROM>(is_pointer_type_func(FROM), from);
}
#endif /* 0 */


/* ////////////////////////////////////////////////////////////////////////// */

int main(int /* argc */, char ** /*argv*/)
{
#if 0
    ::Sleep(100000);
#endif /* 0 */

    puts("ptr_cast_test: " __STLSOFT_COMPILER_LABEL_STRING);

    /* . */
    try
    {
        D       *d_     =   new D();
        A       *a      =   dynamic_cast<B*>(d_);
        A       &ra     =   *a;
        A const &rca    =   ra;
        A const *pca    =   a;
        A       *pa     =   a;

#if 0
        test_same(a);
        test_same(ra);
        test_same(rca);
        test_same(d_);
        test_same(*d_);
#endif /* 0 */

        D       *pd1    =   dynamic_cast<D*>(static_cast<D*>(0));
        STLSOFT_SUPPRESS_UNUSED(pd1);

        D       *pd2    =   stlsoft::ptr_cast<D*>(static_cast<D*>(0));
        STLSOFT_SUPPRESS_UNUSED(pd2);


        D       &rd_    =   dynamic_cast<D&>(ra);
        STLSOFT_SUPPRESS_UNUSED(rd_);

        printf("ptr_cast<D const&>(rca)\n");
        D const &rd     =   stlsoft::ptr_cast<D const&>(rca);
        STLSOFT_SUPPRESS_UNUSED(rd);

        printf("ptr_cast<X const*>(&rca)\n");
        X const *px1    =   stlsoft::ptr_cast<X const*>(&rca);
        STLSOFT_SUPPRESS_UNUSED(px1);

        X const *px2    =   stlsoft::ptr_cast<X const*>(pca);
        STLSOFT_SUPPRESS_UNUSED(px2);


        printf("ptr_cast<X *>(&rca)\n");
        X *px3  =   stlsoft::ptr_cast<X *>(&ra);
        STLSOFT_SUPPRESS_UNUSED(px3);

        X *px4  =   stlsoft::ptr_cast<X *>(pa);
        STLSOFT_SUPPRESS_UNUSED(px4);

        printf("ptr_cast<X const&>(rca)\n");
        X const &rx     =   stlsoft::ptr_cast<X const&>(rca);
        STLSOFT_SUPPRESS_UNUSED(rx);

        STLSOFT_SUPPRESS_UNUSED(d_);
        STLSOFT_SUPPRESS_UNUSED(a);
        STLSOFT_SUPPRESS_UNUSED(ra);
        STLSOFT_SUPPRESS_UNUSED(rca);
        STLSOFT_SUPPRESS_UNUSED(pca);
        STLSOFT_SUPPRESS_UNUSED(pa);
    }
    catch(std::bad_cast const &e)
    {
        printf("Exception caught: %s\n", e.what());
    }
    catch(...)
    {
        printf("Exception caught: ...\n");
    }

    return 0;
}

/* ////////////////////////////////////////////////////////////////////////// */
