/* /////////////////////////////////////////////////////////////////////////////
 * File:        arithmetic_op_test.cpp
 *
 * Purpose:     Implementation file for the arithmetic_op_test project.
 *
 * Created:     6th January 2004
 * Updated:     7th January 2004
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

#ifdef __BORLANDC__
# pragma warn -8080
# pragma warn -8013
# pragma warn -8004
#elif defined(__INTEL_COMPILER)
# pragma warning(disable : 383 444)
#endif /* __BORLANDC__ */

#include <stdio.h>

#include <stlsoft.h>

typedef stlsoft_ns_qual(ss_sint32_t)    sint32_t;
typedef stlsoft_ns_qual(ss_uint8_t)     uint8_t;
typedef stlsoft_ns_qual(ss_uint16_t)    uint16_t;
typedef stlsoft_ns_qual(ss_uint32_t)    uint32_t;
typedef stlsoft_ns_qual(ss_uint64_t)    uint64_t;

#define static_assert                   stlsoft_static_assert

#include <stlsoft_limit_traits.h>

/* ////////////////////////////////////////////////////////////////////////// */

template <class T, class B>
inline void test(T *, B b)
{
    T   t1;         // Default construction
    T   t2  =   0;
//  T   t3  =   B(-1);
    T   t3  =   b;
    T   t4  =   t2; // Copy construction - assigment form
    T   t5(t2);     // Copy construction - function call form
    T   t6((unsigned short)1);

    t1 = t2;            // Copy assigment
    t1 = b;             // Assigment

    t2 = 10;            // Value assignment
    t3 = 20;            // Value assignment
    t4 = 500;           // Value assignment

    t1 = t2 + t3;       // Addition
    t1 = t2 + 11;       // Addition
    t1 += t4;
    t1 += 11;

    t1 = t2 - t3;
    t1 -= t4;

    t1 = t2 * t3;
    t1 *= t4;

    t1 = t2 / (t3 + 1);
    t1 /= (t4 + 1);

    t1 = t2 % (t3 + 1);
    t1 %= (t4 + 1);

    if(t1 < t2)
    {
    }
    else if(t1 != t2)
    {
    }
    else
    {
        if(t1 == t2)
        {}
    }

    STLSOFT_SUPPRESS_UNUSED(t1);
    STLSOFT_SUPPRESS_UNUSED(t2);
    STLSOFT_SUPPRESS_UNUSED(t3);
    STLSOFT_SUPPRESS_UNUSED(t4);
    STLSOFT_SUPPRESS_UNUSED(t5);
    STLSOFT_SUPPRESS_UNUSED(t6);
}

/* ////////////////////////////////////////////////////////////////////////// */

#define ACMELIB_LITTLE_ENDIAN

struct uinteger64
{
#if defined(ACMELIB_LITTLE_ENDIAN)
    uint32_t    lowerVal;
    uint32_t    upperVal;
#elif defined(ACMELIB_BIG_ENDIAN)
    uint32_t    upperVal;
    uint32_t    lowerVal;
#else
# error Need to discriminate further, if neither ACMELIB_LITTLE_ENDIAN or ACMELIB_BIG_ENDIAN
#endif /* endian */
};

class UInteger64
    : protected uinteger64
{
public:
    typedef UInteger64  class_type;

    // This assumes little endian
    typedef union
    {
        uint64_t    i;
        uinteger64  s;
    } ui64_union;

    ui64_union &get_union_()
    {
        uinteger64          *p1 =   this;
        ui64_union  *p2 =   reinterpret_cast<ui64_union*>(p1);

        return *p2;
    }

    ui64_union const &get_union_() const
    {
        uinteger64 const    *p1 =   this;
        ui64_union const    *p2 =   reinterpret_cast<ui64_union const*>(p1);

        return *p2;
    }

public:
    UInteger64()
    {}
    UInteger64(uint64_t i)
    {
        get_union_().i = i;
    }
#if 0
    UInteger64(uint32_t i)
    {
        get_union_().i = i;
    }
    UInteger64(int i);
#if defined(__STLSOFT_COMPILER_IS_INTEL)
    UInteger64(unsigned long i);

#elif defined(__STLSOFT_COMPILER_IS_BORLAND) || \
      defined(__STLSOFT_COMPILER_IS_MWERKS) || \
      defined(__STLSOFT_COMPILER_IS_COMO) || \
      defined(__STLSOFT_COMPILER_IS_DMC) || \
      defined(__STLSOFT_COMPILER_IS_GCC) || \
      defined(__STLSOFT_COMPILER_IS_WATCOM)
    UInteger64(unsigned int i);

#elif defined(__STLSOFT_COMPILER_IS_MSVC)
#if defined(STLSOFT_CF_32BIT_INT_EXTENDED_TYPE_IS_DISTINCT)
    UInteger64(unsigned int i);
#endif /* STLSOFT_CF_32BIT_INT_EXTENDED_TYPE_IS_DISTINCT */
    UInteger64(unsigned long i);

#endif /* compiler */
#endif /* 0 */

#if 0
    UInteger64(class_type const &rhs)
    {
        lowerVal = rhs.lowerVal;
        upperVal = rhs.upperVal;
    }
#endif /* 0 */

    class_type &operator +=(class_type const &rhs)
    {
        get_union_().i += rhs.get_union_().i;

        return *this;
    }

    class_type &operator -=(class_type const &rhs)
    {
        get_union_().i -= rhs.get_union_().i;

        return *this;
    }

    class_type &operator *=(class_type const &rhs)
    {
        get_union_().i *= rhs.get_union_().i;

        return *this;
    }

    class_type &operator /=(class_type const &rhs)
    {
        get_union_().i /= rhs.get_union_().i;

        return *this;
    }

    class_type &operator %=(class_type const &rhs)
    {
        get_union_().i %= rhs.get_union_().i;

        return *this;
    }

    class_type &operator ^=(class_type const &rhs)
    {
        get_union_().i ^= rhs.get_union_().i;

        return *this;
    }


    bool IsEqual(class_type const &rhs) const
    {
        return get_union_().i == rhs.get_union_().i;
    }

    int Compare(class_type const &rhs) const
    {
        return get_union_().i - rhs.get_union_().i;
    }
};

inline UInteger64 operator +(UInteger64 const &lhs, UInteger64 const &rhs)
{
    return UInteger64(lhs) += rhs;
}

inline UInteger64 operator -(UInteger64 const &lhs, UInteger64 const &rhs)
{
    return UInteger64(lhs) -= rhs;
}

inline UInteger64 operator *(UInteger64 const &lhs, UInteger64 const &rhs)
{
    return UInteger64(lhs) *= rhs;
}

inline UInteger64 operator /(UInteger64 const &lhs, UInteger64 const &rhs)
{
    return UInteger64(lhs) /= rhs;
}

inline UInteger64 operator %(UInteger64 const &lhs, UInteger64 const &rhs)
{
    return UInteger64(lhs) %= rhs;
}

inline UInteger64 operator ^(UInteger64 const &lhs, UInteger64 const &rhs)
{
    return UInteger64(lhs) ^= rhs;
}

inline bool operator ==(UInteger64 const &lhs, UInteger64 const &rhs)
{
    return lhs.IsEqual(rhs);
}

inline bool operator !=(UInteger64 const &lhs, UInteger64 const &rhs)
{
    return !lhs.IsEqual(rhs);
}

inline bool operator <(UInteger64 const &lhs, UInteger64 const &rhs)
{
    return lhs.Compare(rhs) < 0;
}

/* ////////////////////////////////////////////////////////////////////////// */

int main(int /* argc */, char ** /*argv*/)
{
#if 0
    ::Sleep(100000);
#endif /* 0 */

    (void)puts("arithmetic_op_test: " __STLSOFT_COMPILER_LABEL_STRING);

    uint32_t    t32(stlsoft_ns_qual(limit_traits)<uint32_t>::maximum());
    uint64_t    t64(stlsoft_ns_qual(limit_traits)<uint64_t>::maximum());

    UInteger64  x1(t32);
    UInteger64  x2(t64);

    UInteger64  i;

    i = 10;
    i = (uint8_t)10;
    i = (uint16_t)10;
    i = (uint32_t)10;
    i = (uint64_t)10;
    i = (unsigned char)10;
    i = (unsigned short)10;
    i = (unsigned int)10;
    i = (unsigned long)10;
#ifdef STLSOFT_CF_64BIT_INT_IS___int64
    i = (unsigned __int64)10;
#endif /* STLSOFT_CF_64BIT_INT_IS___int64 */
    i = x2;

    STLSOFT_SUPPRESS_UNUSED(x1);

    /* . */
    test(static_cast<int*>(NULL),           stlsoft_ns_qual(limit_traits)<sint32_t>::maximum());
//  test(static_cast<double*>(NULL),        123456789.0123456789);
    test(static_cast<UInteger64*>(NULL),    stlsoft_ns_qual(limit_traits)<uint64_t>::maximum());

    uint64_t    blah    =   stlsoft_ns_qual(limit_traits)<uint64_t>::maximum();
//  UInteger64  x(blah);

//  STLSOFT_SUPPRESS_UNUSED(x);
    STLSOFT_SUPPRESS_UNUSED(blah);

//  printf("%I64d\n", x2);

    return 0;
}

/* ////////////////////////////////////////////////////////////////////////// */
