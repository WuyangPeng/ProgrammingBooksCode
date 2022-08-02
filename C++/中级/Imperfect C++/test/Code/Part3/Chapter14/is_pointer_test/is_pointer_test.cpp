/* /////////////////////////////////////////////////////////////////////////////
 * File:        is_pointer_test.cpp
 *
 * Purpose:     Implementation file for the is_pointer_test project.
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

struct Pointer
{
  operator short *() const
  {
    static short s_i;
    return &s_i;
  }
};

/* ////////////////////////////////////////////////////////////////////////// */

int main(int /* argc */, char ** /*argv*/)
{
    puts("is_pointer_test: " __STLSOFT_COMPILER_LABEL_STRING);

    void        *pv = &pv;
    void const  *pcv = pv;
    int         ai[100];
    int         *pi = ai;
    char const  *strings[] =
    {
            "non-pointer"
        ,   "pointer"
    };

#define test_type(t)    \
                        \
    printf("%-20s: %s\n", #t, strings[stlsoft::is_pointer_type<t>::value])

    test_type(void);
    test_type(void*);
    test_type(void const*);
    test_type(bool);
    test_type(Pointer);

    return 0;
}

/* ////////////////////////////////////////////////////////////////////////// */
