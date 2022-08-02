/* /////////////////////////////////////////////////////////////////////////////
 * File:        num_elements_test.cpp
 *
 * Purpose:     Implementation file for the num_elements_test project.
 *
 * Created:     3rd August 2003
 * Updated:     19th October 2003
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


#include <stlsoft.h>

#define NUM_ELEMENTS(x)   (sizeof((x)) / sizeof((x)[0]))



#if !defined(__WATCOMC__)
 #define USE_VECTOR
#endif /* !__WATCOMC__ */

#ifdef USE_VECTOR
 #include <vector>

 stlsoft_ns_using_std(vector)
#endif USE_VECTOR


typedef unsigned char   byte_t;

template <int N>
struct array_size_struct
{
    byte_t  c[N];
};

template <class T, int N>
array_size_struct<N> static_array_size_fn(T (&)[N]);

#define dimensionof(_x)     sizeof(static_array_size_fn(_x).c)


#if !defined(__STLSOFT_COMPILER_IS_MSVC) || \
    _MSC_VER > 1300
 #define    NO_STRUCT_VERSION
#endif /* !_MSC_VER || _MSC_VER > 1300 */

#ifdef NO_STRUCT_VERSION
template<typename T, int N>
char (&byte_array_of_same_dimension_as(T (&)[N]))[N];

#define dimensionof(x)     sizeof(byte_array_of_same_dimension_as((x)));
#endif /* NO_STRUCT_VERSION */


/* ////////////////////////////////////////////////////////////////////////// */

int main(int /* argc */, char ** /*argv*/)
{
    int         ai[23];
    int         *pi = ai;
#ifdef USE_VECTOR
    vector<int> vi(23);
#endif USE_VECTOR

    size_t cai = NUM_ELEMENTS(ai); // Ok
    size_t cpi = NUM_ELEMENTS(pi); // Ok - wrong!
#ifdef USE_VECTOR
    size_t cvi = NUM_ELEMENTS(vi); // Ok - wrong!
#endif USE_VECTOR

    cai = stlsoft_num_elements(ai); // Ok
#ifndef HIDE_ERROR_CASES
    cpi = stlsoft_num_elements(pi); // Error
#ifdef USE_VECTOR
    cvi = stlsoft_num_elements(vi); // Error
#endif USE_VECTOR
#endif /* !HIDE_ERROR_CASES */

    cai = dimensionof(ai); // Ok
#ifndef HIDE_ERROR_CASES
    cpi = dimensionof(pi); // Error
#ifdef USE_VECTOR
    cvi = dimensionof(vi); // Error
#endif USE_VECTOR
#endif /* !HIDE_ERROR_CASES */

#ifdef NO_STRUCT_VERSION
    cai = dimensionof(ai); // Ok
#ifndef HIDE_ERROR_CASES
    cpi = dimensionof(pi); // Error
#ifdef USE_VECTOR
    cvi = dimensionof(vi); // Error
#endif USE_VECTOR
#endif /* !HIDE_ERROR_CASES */
#endif /* NO_STRUCT_VERSION */

    ((void)pi);
    ((void)cai);
    ((void)cpi);
    ((void)cvi);

    return 0;
}

/* ////////////////////////////////////////////////////////////////////////// */
