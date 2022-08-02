/* /////////////////////////////////////////////////////////////////////////////
 * File:        for_each_test.cpp
 *
 * Purpose:     Implementation file for the for_each_test project.
 *
 * Created:     27th January 2004
 * Updated:     27th January 2004
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

#include <stlsoft.h>

#include <algorithm>

/* ////////////////////////////////////////////////////////////////////////// */

namespace acmelib
{
    template< typename  C
            , typename  F
            >
    inline F for_each(C &c, F f)
    {
        return std::for_each(c.begin(), c.end(), f);
    }


    template< typename  T
            , size_t    N
            , typename  F
            >
    inline F for_each(T (&ar)[N], F f)
    {
        return std::for_each(&ar[0], &ar[N], f);
    }

} // namespace acmelib

/* ////////////////////////////////////////////////////////////////////////// */

#if (   defined(WIN32) || \
        defined(_WIN32)) && \
    !defined(_INC_WINDOWS)
extern "C" void __stdcall Sleep(unsigned long);

#endif /* WIN32 */

/* ////////////////////////////////////////////////////////////////////////// */

void print_int(int const &i)
{
    printf("%d ", i);
}

int main(int /* argc */, char ** /*argv*/)
{
#if 0
    ::Sleep(100000);
#endif /* 0 */

    puts("for_each_test: " __STLSOFT_COMPILER_LABEL_STRING);

    /* . */
    int ai[10];

    using namespace std;
//  using std::for_each;
    using namespace acmelib;
//  using acmelib::for_each;

    for_each(ai, print_int);

    return 0;
}

/* ////////////////////////////////////////////////////////////////////////// */
