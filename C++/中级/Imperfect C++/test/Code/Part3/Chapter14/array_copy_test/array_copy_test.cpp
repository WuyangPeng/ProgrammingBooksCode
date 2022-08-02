/* /////////////////////////////////////////////////////////////////////////////
 * File:        array_copy_test.cpp
 *
 * Purpose:     Implementation file for the array_copy_test project.
 *
 * Created:     19th October 2003
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

#include <stlsoft.h>
#include <stlsoft_integer_to_string.h>

#include <algorithm>

#include <string>

typedef std::string     string_t;

/* ////////////////////////////////////////////////////////////////////////// */

const size_t GOOD_DIM   =   15;
const size_t BAD_DIM    =   100;

/* ////////////////////////////////////////////////////////////////////////// */

#ifndef dimensionof
# define dimensionof    stlsoft_num_elements
#endif /* !dimensionof */

/* ////////////////////////////////////////////////////////////////////////// */

template<   typename    T
        ,   size_t      N
        >
struct array_copy
{
    typedef T                   value_type;
    typedef size_t              size_type;
    enum { dimension = N };
    typedef array_copy<T, N>    class_type;

    value_type  values[dimension];

    static size_type size()
    {
        return dimension;
    }
};

/* ////////////////////////////////////////////////////////////////////////// */

void fn(array_copy<int, GOOD_DIM> ai)
{
    printf("[");
    for(int i = 0; i < ai.size(); ++i)
    {
        printf("%d ", ai.values[i]);
    }
    printf("]\n");
}

void fn(array_copy<string_t, GOOD_DIM> ai)
{
    printf("[");
    for(int i = 0; i < ai.size(); ++i)
    {
        printf("%s ", ai.values[i].c_str());
    }
    printf("]\n");
}

void print_array(int (*pa2)[3][4])
{
    printf("[\n");
    for(int i = 0; i < dimensionof(*pa2); ++i)
    {
        printf("  [");
        for(int j = 0; j < dimensionof((*pa2)[0]); ++j)
        {
            printf("%2d ", (*pa2)[i][j]);
        }
        printf("]\n");
    }
    printf("]\n");
}

int main(int /* argc */, char ** /*argv*/)
{
    puts("array_copy_test: " __STLSOFT_COMPILER_LABEL_STRING);

    {   /* int. */
        size_t                      i;
        array_copy<int, GOOD_DIM>   ai10;
        array_copy<int, BAD_DIM>    ai100;

        for(i = 0; i < ai10.size(); ++i)
        {
            ai10.values[i] = i;
        }

        fn(ai10);

        array_copy<int, GOOD_DIM>       ai10b = ai10;

        for(i = 0; i < ai10.size(); ++i)
        {
            ai10.values[i] = -ai10.values[i];
        }

        fn(ai10);
        fn(ai10b);

//      fn(ai100);
    }

    {   /* string_t. */
        size_t                          i;
        array_copy<string_t, GOOD_DIM>  ai10;
        array_copy<string_t, BAD_DIM>   ai100;

        for(i = 0; i < ai10.size(); ++i)
        {
            char    sz[21];

            ai10.values[i] = stlsoft::integer_to_string(sz, (stlsoft::uint32_t)i);
        }

        fn(ai10);

        array_copy<string_t, GOOD_DIM>      ai10b = ai10;

        for(i = 0; i < ai10.size(); ++i)
        {
            std::reverse(ai10.values[i].begin(), ai10.values[i].end());
        }

        fn(ai10);
        fn(ai10b);

//      fn(ai100);
    }

    {
        int i, j, k;
        int v;

        int a3[2][3][4];
        int a2[3][4];
        int (*pa2)[3][4];

        for(v = 0, i = 0; i < dimensionof(a3); ++i)
        {
            for(j = 0; j < dimensionof(a3[0]); ++j)
            {
                for(k = 0; k < dimensionof(a3[0][0]); ++k, ++v)
                {
                    a3[i][j][k] = v;
                }
            }
        }

        for(v = 0, i = 0; i < dimensionof(a2); ++i)
        {
            for(j = 0; j < dimensionof(a2[0]); ++j, ++v)
            {
                a2[i][j] = v;
            }
        }

        pa2 = &a3[0];

        print_array(pa2);

        print_array(&a3[1]);

        pa2 = &a2;

        print_array(pa2);
    }

    return 0;
}

/* ////////////////////////////////////////////////////////////////////////// */
