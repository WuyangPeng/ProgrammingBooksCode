/* /////////////////////////////////////////////////////////////////////////////
 * File:        properties_hack_test.cpp
 *
 * Purpose:     Implementation file for the properties_hack_test project.
 *
 * Created:     1st October 2003
 * Updated:     1st October 2003
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
#include <stddef.h>
#include <windows.h>

/* ////////////////////////////////////////////////////////////////////////// */

//typedef unsigned __int8   byte;

/* ////////////////////////////////////////////////////////////////////////// */

//#pragma optimize("", off)

#pragma pack(push, 1)

template<   typename    T
        ,   typename    R
        ,   typename    R (T::*PFn)() const
        ,   ptrdiff_t   (*PFnOff)()
        >
class PropertyGet
{
public:
    operator R () const
    {
        T   *pT = (T*)((byte*)this - (*PFnOff)());

        return (pT->*PFn)();
    }
};

class Thing
{
public:
    Thing(int value1, int value2, int value3)
        : m_value1(value1)
        , m_value2(value2)
        , m_value3(value3)
    {}

    int get_Value1() const;
    int get_Value2() const;
    int get_Value3() const;
    int get_Value4() const;
    int get_Value5() const;
    int get_Value6() const;

public:
    class Prop1
    {
    public:
        operator int() const
        {
            Thing   *pThing = (Thing*)((byte*)this - offsetof(Thing, Value1));

            return pThing->get_Value1();
        }
    }       Value1;

#if 0
    class Value1Offset
    {
        enum { offset = offsetof(Thing, Value1) };
    };
#endif /* 0 */

    static ptrdiff_t get_Value2Offset() { enum { offset = offsetof(Thing, Value2) }; return offset; }
    static ptrdiff_t get_Value3Offset() { enum { offset = offsetof(Thing, Value3) }; return offset; }
#if 0
    static ptrdiff_t get_Value4Offset() { enum { offset = offsetof(Thing, Value4) }; return offset; }
    static ptrdiff_t get_Value5Offset() { enum { offset = offsetof(Thing, Value5) }; return offset; }
    static ptrdiff_t get_Value6Offset() { enum { offset = offsetof(Thing, Value6) }; return offset; }
#endif /* 0 */

    union
    {
        PropertyGet<Thing, int, &Thing::get_Value2, &Thing::get_Value2Offset>       Value2;
        PropertyGet<Thing, int, &Thing::get_Value3, &Thing::get_Value3Offset>       Value3;
#if 0
        PropertyGet<Thing, int, &Thing::get_Value4, &Thing::get_Value4Offset>       Value4;
        PropertyGet<Thing, int, &Thing::get_Value5, &Thing::get_Value5Offset>       Value5;
        PropertyGet<Thing, int, &Thing::get_Value6, &Thing::get_Value6Offset>       Value6;
#endif /* 0 */
    };

private:
    int m_value1;
    int m_value2;
    int m_value3;
};

/* ////////////////////////////////////////////////////////////////////////// */

int main(int argc, char **argv)
{
    /* . */
    Thing               thing(argc, 1 + 2 * argc, 1 + 3 * argc);
    volatile int        i1 = (int)thing.Value1;
#if 0
    volatile int        i2 = thing.Value2;
    volatile int        i3 = thing.Value3;
    volatile int        i4 = (int)thing.Value1;
    volatile int        i5 = thing.Value2;
    volatile int        i6 = thing.Value3;
#endif /* 0 */
    volatile size_t     sz = sizeof(thing);

    printf("i1 = %d; ", i1);
#if 0
    printf("i2 = %d; ", i2);
    printf("i3 = %d; ", i3);
    printf("i4 = %d; ", i4);
    printf("i5 = %d; ", i5);
    printf("i6 = %d; ", i6);
#endif /* 0 */
    printf("size = %u\n", sizeof(thing));

    return i1 + sz;
}

/* ////////////////////////////////////////////////////////////////////////// */

#pragma optimize("", off)

int Thing::get_Value1() const
{
    return m_value1;
}
int Thing::get_Value2() const
{
    return m_value2;
}
int Thing::get_Value3() const
{
    return m_value3;
}
int Thing::get_Value4() const
{
    return m_value1;
}
int Thing::get_Value5() const
{
    return m_value2;
}
int Thing::get_Value6() const
{
    return m_value3;
}

/* ////////////////////////////////////////////////////////////////////////// */
