/* /////////////////////////////////////////////////////////////////////////////
 * File:        real_address_test.cpp
 *
 * Purpose:     Implementation file for the real_address_test project.
 *
 * Created:     4th January 2004
 * Updated:     4th January 2004
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

#define _STLSOFT_NO_NAMESPACES

#include <stlsoft.h>

/* ////////////////////////////////////////////////////////////////////////// */

template<typename T>
T *get_address(T &t)
{
    return const_cast<T*>(reinterpret_cast<T const volatile*>(&reinterpret_cast<ss_byte_t const volatile &>(t)));
}

#if 0
template<typename T>
T const *get_address(T const &t)
{
    return reinterpret_cast<T const*>(&reinterpret_cast<ss_byte_t const &>(t));
}

template<typename T>
T *get_address(T volatile &t)
{
    return reinterpret_cast<T volatile*>(&reinterpret_cast<ss_byte_t volatile &>(t));
}

template<typename T>
T *get_address(T const volatile &t)
{
    return reinterpret_cast<T const volatile*>(&reinterpret_cast<ss_byte_t const volatile &>(t));
}
#endif /* 0 */

/* ////////////////////////////////////////////////////////////////////////// */

struct X
{};

struct Y
{
    X *operator &()
    {
        return NULL;
    }
};


/* ////////////////////////////////////////////////////////////////////////// */

int main(int /* argc */, char ** /*argv*/)
{
#if 0
    ::Sleep(100000);
#endif /* 0 */

    puts("real_address_test: " __STLSOFT_COMPILER_LABEL_STRING);

    /* . */
    X volatile  x;
    Y const     y;

    printf("address of x:      %p\n", &x);
    printf("address of y:      %p\n", &y);
    printf("real address of x: %p\n", get_address(x));
    printf("real address of y: %p\n", get_address(y));

    return 0;
}

/* ////////////////////////////////////////////////////////////////////////// */

#ifdef WIN32
#include <windows.h>
#else /* WIN32 */
