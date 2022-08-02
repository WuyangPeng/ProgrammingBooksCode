/* /////////////////////////////////////////////////////////////////////////////
 * File:        inherit_op_clash_test.cpp
 *
 * Purpose:     Implementation file for the inherit_op_clash_test project.
 *
 * Created:     5th January 2004
 * Updated:     5th January 2004
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

#define SUBSCRIPT_IS_SIZE_T
//#define INDEX_IS_SIZE_T

#ifdef SUBSCRIPT_IS_SIZE_T
# define subscript_arg_name "size_t"
typedef size_t              subscript_arg_type;
#else /* ? 0 */
# define subscript_arg_name "int"
typedef int                 subscript_arg_type;
#endif /* 0 */

#ifdef INDEX_IS_SIZE_T
# define indexer_name       "size_t"
typedef size_t              indexer_type;
#else /* ? 0 */
# define indexer_name       "int"
typedef int                 indexer_type;
#endif /* 0 */

/* ////////////////////////////////////////////////////////////////////////// */

struct X
{
    operator double const *() const
    {
        printf("X::operator double *\n");

        return &x[0];
    }
    operator double *()
    {
        printf("X::operator double *\n");

        return &x[0];
    }

    double  x[10];
#if 0
};

struct Y
    : public X
{
#endif /* 0 */
    double const &operator [](subscript_arg_type ) const
    {
        printf("Y::operator []\n");

        return x[0];
    }
    double &operator [](subscript_arg_type )
    {
        printf("Y::operator []\n");

        return x[0];
    }
};

typedef X   Y;

/* ////////////////////////////////////////////////////////////////////////// */

int main(int /* argc */, char ** /*argv*/)
{
#if 0
    ::Sleep(100000);
#endif /* 0 */

    puts("inherit_op_clash_test: " __STLSOFT_COMPILER_LABEL_STRING);

    puts("subscript_arg_type: " subscript_arg_name);
    puts("indexer_type: " indexer_name);

    /* . */
    X               x;
    Y               y;
    indexer_type    i;

    for(i = 0; i < stlsoft_num_elements(x.x); ++i)
    {
        x[i] = i;
    }

    for(i = 0; i < stlsoft_num_elements(y.x); ++i)
    {
        y[i] = i;
    }

    STLSOFT_SUPPRESS_UNUSED(i);
    STLSOFT_SUPPRESS_UNUSED(y);
    STLSOFT_SUPPRESS_UNUSED(x);

    return 0;
}

/* ////////////////////////////////////////////////////////////////////////// */
