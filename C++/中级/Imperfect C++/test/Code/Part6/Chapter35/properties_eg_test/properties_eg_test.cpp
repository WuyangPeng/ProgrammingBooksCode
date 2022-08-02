/* /////////////////////////////////////////////////////////////////////////////
 * File:        properties_eg_test.cpp
 *
 * Purpose:     Implementation file for the properties_eg_test project.
 *
 * Created:     1st October 2003
 * Updated:     6th October 2003
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

#ifdef __WATCOMC__
# define    typename    class
#endif /* __WATCOMC__ */

/* ////////////////////////////////////////////////////////////////////////// */

template<typename ID, typename T>
class property_base
{
protected:
    T * Holder()
    {
        return (T *)((unsigned char *)this - m_Offset);
    }
    const T * Holder() const
    {
        return (T *)((unsigned char *)this - m_Offset);
    }
private:
    static const ptrdiff_t m_Offset;
};

template<typename ID, typename T, typename V, typename R, void (T::*PFnSet)(R), R (T::*PFnGet)() const>
class property
    : property_base<ID, T>
{
//friend typename T;
public:
    property(V v = V())
        : m_value(v)
    {}

    property & operator=(R v)
    {
        (Holder()->*PFnSet)(v);

        return *this;
    }
    operator R () const
    {
        return (Holder()->*PFnGet)();
    }
public:
    V m_value;
};

#define DECLARE_PROPERTY(Class, Type, R, Name, Set, Get)    \
                                                            \
 class prop##Name{};                                        \
    property<prop##Name, Class, Type, R, Set, Get> Name


#define DEFINE_PROPERTY(Class, Name)                        \
                                                            \
    const ptrdiff_t property_base<Class::prop##Name, Class>::m_Offset = offsetof(Class, Name)


#pragma pack (push, 8)

class foo 
{
public:
    void set_Length(int val)
    {
        Length.m_value = val;
    }
    int get_Length() const
    {
        return Length.m_value;
    }
public:
    typedef int value_type;

    class propLength{};
    property<propLength, foo, int, int, &foo::set_Length, &foo::get_Length> Length;

//  DECLARE_PROPERTY(foo, int, int, Length, foo::set_Length, foo::get_Length);
};

DEFINE_PROPERTY(foo, Length);

//Of course this is the rough idea. It could be improved in various ways starting from R deduction and going to read-only or write-only props


/* ////////////////////////////////////////////////////////////////////////// */

int main(int /* argc */, char ** /*argv*/)
{
    /* . */
    foo f;

    size_t size = sizeof(f);

    f.Length = 5;

    int len = f.Length;

    printf("sizeof(foo): %u, sizeof(value_type): %u\n", sizeof(foo), sizeof(foo::value_type));

    return 0;
}

/* ////////////////////////////////////////////////////////////////////////// */
