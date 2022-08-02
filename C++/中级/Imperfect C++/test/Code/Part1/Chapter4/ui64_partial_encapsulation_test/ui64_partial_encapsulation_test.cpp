/* /////////////////////////////////////////////////////////////////////////////
 * File:        ui64_partial_encapsulation_test.cpp
 *
 * Purpose:     Implementation file for the ui64_partial_encapsulation_test project.
 *
 * Created:     29th October 2003
 * Updated:     29th October 2003
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

#include "..\uinteger64\uinteger64.h"

#include <set>
#include <vector>
#include <algorithm>

#define USE_INHERITANCE
#define USE_COMPOSITION

#if defined(USE_INHERITANCE)
#elif defined(USE_COMPOSITION)
#else
# error Must specify USE_INHERITANCE or USE_COMPOSITION
#endif /* USE_INHERITANCE || USE_COMPOSITION */

/* ////////////////////////////////////////////////////////////////////////// */

class UInteger64
#if defined(USE_INHERITANCE)
    : public uinteger64
#endif /* USE_INHERITANCE */
{
public:
             UInteger64();
    explicit UInteger64(uint32_t lower);
             UInteger64(uint32_t upper, uint32_t lower);
//           UInteger64(UInteger64 const &);

    UInteger64 &Assign(uint32_t upper, uint32_t lower);
    UInteger64 &Assign(uint32_t lower);
//  UInteger64 &operator =(UInteger64 const &);

    UInteger64 &Add(uint32_t lower);
    UInteger64 &Add(uint32_t upper, uint32_t lower);
    static UInteger64 Add(UInteger64 const &i1, UInteger64 const &i2);

public:
    static bool IsLessThan(UInteger64 const &lhs, UInteger64 const &rhs);
    static bool IsEqual(UInteger64 const &lhs, UInteger64 const &rhs);
    static bool IsGreaterThan(UInteger64 const &lhs, UInteger64 const &rhs);

private:
    uinteger64 &_get_uinteger64()
#if defined(USE_INHERITANCE)
    {
        return *this;
    }
#elif defined(USE_COMPOSITION)
    {
        return m_value;
    }
public:
    uinteger64  m_value;
#endif /* USE_COMPOSITION */
};

/* ////////////////////////////////////////////////////////////////////////// */

inline bool operator ==(UInteger64 const &i1, UInteger64 const &i2)
{
    return UInteger64::IsEqual(i1, i2);
}
inline bool operator !=(UInteger64 const &i1, UInteger64 const &i2)
{
    return !operator ==(i1, i2);
}

/* ////////////////////////////////////////////////////////////////////////// */

typedef std::vector<UInteger64>     UInteger64_vector_t;
typedef std::set<UInteger64>        UInteger64_set_t;

int main(int /* argc */, char ** /*argv*/)
{
    puts("ui64_partial_encapsulation_test: " __STLSOFT_COMPILER_LABEL_STRING);

    /* . */
    UInteger64  i1(0x11111111, 0x22222222);
    UInteger64  i2;

    i2.Assign(0x10101010, 0x02020202);

    bool        bLess       = UInteger64::IsLessThan(i1, i2);  // Error!
//  bool        bEqual      = i1 == i2; // Error!
    bool        bEqual      =   UInteger64::IsEqual(i1, i2);
    bool        bGreater    =   UInteger64::IsGreaterThan(i1, i2);

//  i1 + i2; // Error!
    UInteger64  i3;
    UInteger64  i4 = i3;
    UInteger64  i5;

    i3 = UInteger64::Add(i1, i2);

    i5 = i3;

#if 0
    UInteger64_vector_t vi;

    vi.push_back(i1);
    vi.push_back(i2);
    vi.push_back(i3);
    vi.push_back(i4);
#else /* ? 0 */
    UInteger64_set_t    vi;

    vi.insert(vi.begin(), i1);
    vi.insert(vi.begin(), i2);
    vi.insert(vi.begin(), i3);
    vi.insert(vi.begin(), i4);
#endif /* 0 */

    std::find(vi.begin(), vi.end(), UInteger64(0x11111111, 0x22222222));

    return 0;
}

/* ////////////////////////////////////////////////////////////////////////// */

UInteger64::UInteger64()
{
    _get_uinteger64().lowerVal = 0;
    _get_uinteger64().upperVal = 0;
}

UInteger64::UInteger64(uint32_t lower)
{
    _get_uinteger64().lowerVal = lower;
    _get_uinteger64().upperVal = 0;
}

UInteger64::UInteger64(uint32_t upper, uint32_t lower)
{
    _get_uinteger64().lowerVal = lower;
    _get_uinteger64().upperVal = upper;
}

#if 0
UInteger64::UInteger64(UInteger64 const &rhs)
{
    _get_uinteger64().lowerVal = rhs._get_uinteger64().lowerVal;
    _get_uinteger64().upperVal = rhs._get_uinteger64().upperVal;
}
#endif /* 0 */

UInteger64 &UInteger64::Assign(uint32_t upper, uint32_t lower)
{
    _get_uinteger64().lowerVal = lower;
    _get_uinteger64().upperVal = upper;

    return *this;
}

#if 0
    Assign(uint32_t lower);
    UInteger64 &operator =(UInteger64 const &);

    UInteger64 &Add(uint32_t lower);
    UInteger64 &Add(uint32_t upper, uint32_t lower);
    static UInteger64 Add(UInteger64 const &i1, UInteger64 const &i2);
#endif /* 0 */
