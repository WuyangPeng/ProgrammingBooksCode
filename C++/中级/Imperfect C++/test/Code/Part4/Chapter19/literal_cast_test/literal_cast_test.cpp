/* /////////////////////////////////////////////////////////////////////////////
 * File:        literal_cast_test.cpp
 *
 * Purpose:     Implementation file for the literal_cast_test project.
 *
 * Created:     25th August 2003
 * Updated:     5th March 2004
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

#define _STLSOFT_NO_NAMESPACE

#include <stlsoft.h>
#include <stlsoft_literal_cast.h>

/* ////////////////////////////////////////////////////////////////////////// */

#if 0
template<   ss_typename_param_k T
#ifdef __STLSOFT_CF_NATIVE_64BIT_INTEGER_SUPPORT
        ,   ss_sint64_t         V
#else /* ? __STLSOFT_CF_NATIVE_64BIT_INTEGER_SUPPORT */
        ,   long                V
#endif /* __STLSOFT_CF_NATIVE_64BIT_INTEGER_SUPPORT */
        >
struct literal_cast
{
private:
    static void constraint()
    {
        stlsoft_static_assert(V <= limit_traits<T>::maximum_value);
        stlsoft_static_assert(V >= limit_traits<T>::minimum_value);

        const int   __literal_cast_value_out_of_range__ = V <= limit_traits<T>::maximum_value && V >= limit_traits<T>::minimum_value;

        stlsoft_static_assert(__literal_cast_value_out_of_range__);
    }

public:
    ~literal_cast()
    {
        void (*pfn)() = constraint;
    }

//  static const T  value           =   T(V);

    operator T () const
    {
        return T(V);
    }
};
#endif /* 0 */

/* ////////////////////////////////////////////////////////////////////////// */

const int   I128    =   128;


int main(int /* argc */, char ** /*argv*/)
{
#if 0
    ::Sleep(100000);
#endif /* 0 */

    puts("literal_cast_test: " __STLSOFT_COMPILER_LABEL_STRING);

    char    c   =   100000;

#if 1
    ss_sint8_t  s8;

    s8 = literal_cast<ss_sint8_t, 0>();
    s8 = literal_cast<ss_sint8_t, 100>();
//  s8 = literal_cast<ss_sint8_t, 1000>();
//  s8 = literal_cast<ss_sint8_t, 10000000>();
//  s8 = literal_cast<ss_sint8_t, 10000000000000LL>();

    s8 = literal_cast<ss_sint8_t, 0U>();
    s8 = literal_cast<ss_sint8_t, 100U>();
    s8 = literal_cast<ss_sint8_t, 127U>();
//  s8 = literal_cast<ss_sint8_t, I128>();
    s8 = literal_cast<ss_sint8_t, -128>();
//  s8 = literal_cast<ss_sint8_t, -129>();

    ss_uint8_t  u8;

    u8 = literal_cast<ss_uint8_t, 0>();
//  u8 = literal_cast<ss_uint8_t, -1>();
    u8 = literal_cast<ss_uint8_t, I128>();
    u8 = literal_cast<ss_uint8_t, 255>();
//  u8 = literal_cast<ss_uint8_t, 256>();

    ss_uint32_t u32;

    u32 = literal_cast<ss_uint32_t, 0>();
    u32 = literal_cast<ss_uint32_t, 100000>();
    u32 = literal_cast<ss_uint32_t, 1000000000>();
//  u32 = literal_cast<ss_uint32_t, 10000000000000LL>();

    ss_sint64_t s64;

    s64 = 0;
    s64 = literal_cast<ss_sint64_t, 0>();
    s64 = 100000;
    s64 = literal_cast<ss_sint64_t, 100000>();
    s64 = __STLSOFT_GEN_SINT64_SUFFIX(10000000000000);
    s64 = literal_cast<ss_sint64_t, __STLSOFT_GEN_SINT64_SUFFIX(10000000000000)>();
    s64 = __STLSOFT_LIMIT_TRAITS__SINT64_MAX;
    s64 = literal_cast<ss_sint64_t, __STLSOFT_LIMIT_TRAITS__SINT64_MAX>();
    s64 = __STLSOFT_LIMIT_TRAITS__SINT64_MIN;
    s64 = ss_sint64_t(__STLSOFT_LIMIT_TRAITS__SINT64_MIN);
    s64 = literal_cast<ss_sint64_t, __STLSOFT_LIMIT_TRAITS__SINT64_MIN>();

//  s64 = literal_cast<ss_sint64_t, __STLSOFT_LIMIT_TRAITS__UINT64_MAX>(); // Change of sign

    ss_uint64_t u64;

    u64 = literal_cast<ss_uint64_t, 1>();
    u64 = literal_cast<ss_uint64_t, 0>();
    u64 = literal_cast<ss_uint64_t, -1>();
    u64 = literal_cast<ss_uint64_t, 100000>();
    u64 = literal_cast<ss_uint64_t, __STLSOFT_GEN_UINT64_SUFFIX(10000000000000)>();
//  u64 = literal_cast<ss_uint64_t, limit_traits<ss_uint64_t>::maximum_value>();
    u64 = literal_cast<ss_uint64_t, __STLSOFT_LIMIT_TRAITS__UINT64_MIN>();
    u64 = literal_cast<ss_uint64_t, __STLSOFT_LIMIT_TRAITS__UINT64_MAX>();
#endif /* 0 */

    return 0;
}

/* ////////////////////////////////////////////////////////////////////////// */
