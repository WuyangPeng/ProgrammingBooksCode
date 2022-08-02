/* /////////////////////////////////////////////////////////////////////////////
 * File:        properties_test.cpp
 *
 * Purpose:     Implementation file for the properties_test project.
 *
 * Created:     29th September 2003
 * Updated:     4th October 2003
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
#include <stlsoft_simple_string.h>

/* ////////////////////////////////////////////////////////////////////////// */

typedef stlsoft_ns_qual(basic_simple_string)<char>  string_t;

/* ////////////////////////////////////////////////////////////////////////// */

// Define this to see the other mechanism, currently only implemented for property_get_external<>
//
// With this, DMC++ and VC 6 work.
//#define PROPERTY_GET_SUPPORTED_B

/* ////////////////////////////////////////////////////////////////////////// */

#if defined(__COMO__) || \
    (   defined(__DMC__) && \
        __DMC__ >= 0x0837) || \
    defined(__GNUC__) || \
    defined(__INTEL_COMPILER) || \
    (   defined(__MWERKS__) && \
        (__MWERKS__ & 0xff00) >= 0x3000) || \
    (   defined(_MSC_VER) && \
        _MSC_VER >= 1310) || \
    defined(__VECTORC)
# define    MEM_FUNC_AS_TEMPLATE_PARAM_SUPPORT
#elif defined(__BORLANDC__) || \
      (  defined(__DMC__) && \
         __DMC__ < 0x0837) || \
      ( defined(__MWERKS__) && \
        (__MWERKS__ & 0xff00) < 0x3000) || \
      ( defined(_MSC_VER) && \
        _MSC_VER >= /* 1300 */ 0)
 /* Not supported */
#else
# error Compiler not supported
#endif /* compiler */



#define SIMPLE_PROPERTY_GET_SUPPORTED

#define SIMPLE_PROPERTY_SET_SUPPORTED

#define PROPERTY_GET_SUPPORTED

#define PROPERTY_SET_SUPPORTED

#define PROPERTY_GETSET_SUPPORTED


#if defined(__STLSOFT_COMPILER_IS_COMO) || \
    defined(__STLSOFT_COMPILER_IS_INTEL)
 /* Works fine */
#elif defined(__STLSOFT_COMPILER_IS_BORLAND)
 /* Borland supports all except get-set */
#elif defined(__STLSOFT_COMPILER_IS_DMC)
# if __DMC__ < 0x0837
//# undef PROPERTY_GET_SUPPORTED
//# undef PROPERTY_SET_SUPPORTED
//# undef PROPERTY_GETSET_SUPPORTED
# endif /* __DMC__ */
#elif defined(__STLSOFT_COMPILER_IS_MWERKS)
# if (__MWERKS__ & 0xff00) < 0x3000
# undef PROPERTY_GET_SUPPORTED
# undef PROPERTY_SET_SUPPORTED
# undef PROPERTY_GETSET_SUPPORTED
# else
# endif /* __MWERKS__ */
#elif defined(__STLSOFT_COMPILER_IS_MSVC)
# if _MSC_VER >= 1310 
 /* Works fine */
# else
#  if _MSC_VER < 1100
#   define typename class
#  endif /* _MSC_VER < 1100 */
#  ifndef MEM_FUNC_AS_TEMPLATE_PARAM_SUPPORT
#   undef PROPERTY_GET_SUPPORTED
#  endif /* MEM_FUNC_AS_TEMPLATE_PARAM_SUPPORT */
#  undef PROPERTY_SET_SUPPORTED
#  undef PROPERTY_GETSET_SUPPORTED
# endif /* _MSC_VER */
#endif /* compiler */

/* ////////////////////////////////////////////////////////////////////////// */

#ifdef SIMPLE_PROPERTY_GET_SUPPORTED

template<   typename V
        ,   typename R
        >
class simple_property_get_external
{
public:
    simple_property_get_external(V &value)
        : m_value(value)
    {}

// Accessors
public:
    operator R() const
    {
        return m_value;
    }

// Members
private:
    V   &m_value;
};

#endif /* SIMPLE_PROPERTY_GET_SUPPORTED */

/* ////////////////////////////////////////////////////////////////////////// */

#ifdef SIMPLE_PROPERTY_SET_SUPPORTED

template<   typename V
        ,   typename R
        >
class simple_property_set_external
{
public:
    simple_property_set_external(V &value)
        : m_value(value)
    {}

// Accessors
public:
    simple_property_set_external &operator =(R value)
    {
        m_value = value;

        return *this;
    }

// Members
private:
    V   &m_value;
};

#endif /* SIMPLE_PROPERTY_SET_SUPPORTED */

/* ////////////////////////////////////////////////////////////////////////// */

#ifdef PROPERTY_GET_SUPPORTED

template<   typename T
        ,   typename R
#ifdef MEM_FUNC_AS_TEMPLATE_PARAM_SUPPORT
        ,   R (T::*PFn)(void) const
#endif /* MEM_FUNC_AS_TEMPLATE_PARAM_SUPPORT */
        >
class property_get_external
{
public:
#ifndef MEM_FUNC_AS_TEMPLATE_PARAM_SUPPORT
    property_get_external(T &object, R (T::*fn)(void) const) 
#else
    property_get_external(T &object) 
#endif /* !MEM_FUNC_AS_TEMPLATE_PARAM_SUPPORT */
        : m_object(object)
#ifndef MEM_FUNC_AS_TEMPLATE_PARAM_SUPPORT
        , m_fn(fn)
#endif /* MEM_FUNC_AS_TEMPLATE_PARAM_SUPPORT */
    {}

// Accessors
public:
    operator R() const
    {
#ifndef MEM_FUNC_AS_TEMPLATE_PARAM_SUPPORT
        return (m_object.*m_fn)();
#else
        return (m_object.*PFn)();
#endif /* !MEM_FUNC_AS_TEMPLATE_PARAM_SUPPORT */
    }

// Members
private:
    T   &m_object;
#ifndef MEM_FUNC_AS_TEMPLATE_PARAM_SUPPORT
    R (T::*m_fn)(void) const;
#endif /* !MEM_FUNC_AS_TEMPLATE_PARAM_SUPPORT */

// Not to be implemented
private:
    property_get_external &operator =(R );
};

template<   typename R
        ,   R (*PFn)(void)
        >
class static_property_get_external
{
// Accessors
public:
    operator R() const
    {
        return (*PFn)();
    }

// Not to be implemented
private:
    static_property_get_external &operator =(R );
};

#endif /* PROPERTY_GET_SUPPORTED */

/* ////////////////////////////////////////////////////////////////////////// */

#ifdef PROPERTY_SET_SUPPORTED

template<   typename T
        ,   typename R
        ,   void (T::*PFn)(R )
        >
class property_set_external
{
public:
    property_set_external(T &object) 
        : m_object(object)
    {}

// Accessors
public:
    property_set_external &operator =(R value)
    {
        (m_object.*PFn)(value);

        return *this;
    }

// Members
private:
    T   &m_object;
};


template<   typename R
        ,   void (*PFn)(R )
        >
class static_property_set_external
{
// Accessors
public:
    static_property_set_external &operator =(R value)
    {
        (*PFn)(value);

        return *this;
    }
};

#endif /* PROPERTY_SET_SUPPORTED */

/* ////////////////////////////////////////////////////////////////////////// */

#ifdef PROPERTY_GETSET_SUPPORTED

template<   typename T
        ,   typename RG
        ,   RG (T::*PFnGet)(void) const
        ,   typename RS
        ,   void (T::*PFnSet)(RS )
        >
class property_getset_external
{
public:
    property_getset_external(T &object) 
        : m_object(object)
    {}

// Accessors
public:
    operator RG() const
    {
        return (m_object.*PFnGet)();
    }
    property_getset_external &operator =(RS value)
    {
        (m_object.*PFnSet)(value);

        return *this;
    }

// Members
private:
    T   &m_object;
};

template<   typename RG
        ,   RG (*PFnGet)(void)
        ,   typename RS
        ,   void (*PFnSet)(RS )
        >
class static_property_getset
{
// Accessors
public:
    operator RG() const
    {
        return (*PFnGet)();
    }
    static_property_getset &operator =(RS value)
    {
        (*PFnSet)(value);

        return *this;
    }
};

#endif /* PROPERTY_GETSET_SUPPORTED */

/* ////////////////////////////////////////////////////////////////////////// */

class Thingy
{
public:
    Thingy(int v1, int v2, double v5, char const *s)
        : m_var1(v1)
        , m_var2(v2)
        , m_var5(v5)
        , m_str(s)
#ifdef SIMPLE_PROPERTY_GET_SUPPORTED
        , Prop1(m_var1)
        , PropS1(m_str)
#endif /* SIMPLE_PROPERTY_GET_SUPPORTED */
#ifdef SIMPLE_PROPERTY_SET_SUPPORTED
        , Prop2(m_var2)
        , PropS2(m_str)
#endif /* SIMPLE_PROPERTY_SET_SUPPORTED */
#ifdef PROPERTY_GET_SUPPORTED
# ifndef MEM_FUNC_AS_TEMPLATE_PARAM_SUPPORT
        , Prop3(*this, &Thingy::get_Prop3)
# else
        , Prop3(*this)
# endif /* !MEM_FUNC_AS_TEMPLATE_PARAM_SUPPORT */
#endif /* PROPERTY_GET_SUPPORTED */
#ifdef PROPERTY_SET_SUPPORTED
        , Prop4(*this)
#endif /* PROPERTY_SET_SUPPORTED */
#ifdef PROPERTY_GETSET_SUPPORTED
        , Prop5(*this)
#endif /* PROPERTY_GETSET_SUPPORTED */
    {
        ++sm_count;
    }

// Operations
public:
    void ChangeVar1()
    {
        m_var1 *= m_var1;
    }

// Accessors
public:
    double get_Var2() const;
    double get_Prop3() const
    {
        return m_var1 * m_var2;
    }
    void set_Prop4(double const &d)
    {
        m_var2 = d;
    }

    double get_Prop5() const
    {
        return m_var5;
    }
    void set_Prop5(double const &v)
    {
        m_var5 = v;
    }

    static double get_DCount()
    {
        return sm_count;
    }
    static void set_DCount(double const &v)
    {
        sm_count = (int)v;
    }

// Properties
public:
#ifdef SIMPLE_PROPERTY_GET_SUPPORTED
    simple_property_get_external<int, int const>                                                        Prop1;
    simple_property_get_external<string_t, string_t const &>                                            PropS1;
    static simple_property_get_external<int, int const>                                                 StaticProp1;
#endif /* SIMPLE_PROPERTY_GET_SUPPORTED */
#ifdef SIMPLE_PROPERTY_SET_SUPPORTED
    simple_property_set_external<double, double const>                                                  Prop2;
    simple_property_set_external<string_t, char const *>                                                PropS2;
#endif /* SIMPLE_PROPERTY_SET_SUPPORTED */
#ifdef PROPERTY_GET_SUPPORTED
# ifndef MEM_FUNC_AS_TEMPLATE_PARAM_SUPPORT
    property_get_external<Thingy, double>                                                               Prop3;
# else
    property_get_external<Thingy, double, &Thingy::get_Prop3>                                           Prop3;
# endif /* !MEM_FUNC_AS_TEMPLATE_PARAM_SUPPORT */
    static static_property_get_external<double, &Thingy::get_DCount>                                    StaticProp3;
#endif /* PROPERTY_GET_SUPPORTED */
#ifdef PROPERTY_SET_SUPPORTED
    property_set_external<Thingy, double const &, &Thingy::set_Prop4>                                   Prop4;
    static static_property_set_external<double const &, &Thingy::set_DCount>                            StaticProp4;
#endif /* PROPERTY_SET_SUPPORTED */
#ifdef PROPERTY_GETSET_SUPPORTED
    property_getset_external<Thingy, double, &Thingy::get_Prop5, double const &, &Thingy::set_Prop5>    Prop5;
#endif /* PROPERTY_GETSET_SUPPORTED */

// Members
private:
    int         m_var1;
    string_t    m_str;
    double      m_var2;
    double      m_var5;
    static int  sm_count;
};

/* static */ int                                                                Thingy::sm_count = 0;
#ifdef SIMPLE_PROPERTY_GET_SUPPORTED
/* static */ simple_property_get_external<int, int const>                       Thingy::StaticProp1(Thingy::sm_count);
#endif /* SIMPLE_PROPERTY_GET_SUPPORTED */
#ifdef PROPERTY_GET_SUPPORTED
/* static */ static_property_get_external<double, &Thingy::get_DCount>          Thingy::StaticProp3;
#endif /* PROPERTY_GET_SUPPORTED */
#ifdef PROPERTY_SET_SUPPORTED
/* static */ static_property_set_external<double const &, &Thingy::set_DCount>  Thingy::StaticProp4;
#endif /* PROPERTY_SET_SUPPORTED */

/* ////////////////////////////////////////////////////////////////////////// */

int main(int /* argc */, char ** /*argv*/)
{
    puts("properties_test: " __STLSOFT_COMPILER_LABEL_STRING);


#ifdef SIMPLE_PROPERTY_GET_SUPPORTED
    puts("  Supports simple_property_get_external<>");
#endif /* SIMPLE_PROPERTY_GET_SUPPORTED */
#ifdef PROPERTY_GET_SUPPORTED
    puts("  Supports property_get_external<>");
#endif /* PROPERTY_GET_SUPPORTED */
#ifdef PROPERTY_SET_SUPPORTED
    puts("  Supports property_set_external<>");
#endif /* PROPERTY_SET_SUPPORTED */
#ifdef PROPERTY_GETSET_SUPPORTED
    puts("  Supports property_getset_external<>");
#endif /* PROPERTY_GETSET_SUPPORTED */

    /* . */
    Thingy      t(10, 20, 9999.99, "Some string value");
    int         v1      =   0;
    int         count   =   0;
    double      dcount  =   0.0;
    double      v2      =   0.0;
    double      v3      =   0.0;
    double      v4      =   0.0;
    double      v5      =   0.0;
    string_t    s;

    ((void)v1); ((void)v2); ((void)v3); ((void)v4); ((void)v5); ((void)dcount);
    
#ifdef SIMPLE_PROPERTY_GET_SUPPORTED

    simple_property_get_external<int, int const>    Prop1_(t.Prop1);
    v1 = sizeof(Prop1_);

    ((void)v1); ((void)v2); ((void)v3); ((void)v4); ((void)v5); ((void)dcount);

    v1 = Prop1_;

    ((void)v1); ((void)v2); ((void)v3); ((void)v4); ((void)v5); ((void)dcount);

    v1 = t.Prop1;
    s = t.PropS1;
#endif /* SIMPLE_PROPERTY_GET_SUPPORTED */
#ifdef SIMPLE_PROPERTY_SET_SUPPORTED
    t.Prop2 = v2 + 1.0;
    t.PropS2 = "Set the string # 1";
#endif /* SIMPLE_PROPERTY_SET_SUPPORTED */
#ifdef PROPERTY_GET_SUPPORTED
    v3 = t.Prop3;
#endif /* PROPERTY_GET_SUPPORTED */
#ifdef PROPERTY_GETSET_SUPPORTED
    v5 = t.Prop5;
#endif /* PROPERTY_GETSET_SUPPORTED */

    ((void)v1); ((void)v2); ((void)v3); ((void)v4); ((void)v5);

    t.ChangeVar1();

#ifdef SIMPLE_PROPERTY_GET_SUPPORTED
    v1 = t.Prop1;
    s = t.PropS1;
#endif /* SIMPLE_PROPERTY_GET_SUPPORTED */
#ifdef SIMPLE_PROPERTY_SET_SUPPORTED
    t.Prop2 = v2 + 1.0;
    t.PropS2 = "Set the string # 2";
#endif /* SIMPLE_PROPERTY_SET_SUPPORTED */
#ifdef PROPERTY_GET_SUPPORTED
    v3 = t.Prop3;
#endif /* PROPERTY_GET_SUPPORTED */
#ifdef PROPERTY_GETSET_SUPPORTED
    v5 = t.Prop5;
#endif /* PROPERTY_GETSET_SUPPORTED */

    ((void)v1); ((void)v2); ((void)v3); ((void)v4); ((void)v5); ((void)dcount);

#ifdef PROPERTY_SET_SUPPORTED
    t.Prop4 = 0.1;
#endif /* PROPERTY_SET_SUPPORTED */

#ifdef SIMPLE_PROPERTY_GET_SUPPORTED
    v1 = t.Prop1;
    s = t.PropS1;
#endif /* SIMPLE_PROPERTY_GET_SUPPORTED */
#ifdef SIMPLE_PROPERTY_SET_SUPPORTED
    t.Prop2 = v2 + 1.0;
    t.PropS2 = "Set the string # 3";
#endif /* SIMPLE_PROPERTY_SET_SUPPORTED */
#ifdef PROPERTY_GET_SUPPORTED
    v3 = t.Prop3;
#endif /* PROPERTY_GET_SUPPORTED */
#ifdef PROPERTY_GETSET_SUPPORTED
    v5 = t.Prop5;
#endif /* PROPERTY_GETSET_SUPPORTED */

    ((void)v1); ((void)v2); ((void)v3); ((void)v4); ((void)v5); ((void)dcount);

#ifdef PROPERTY_GETSET_SUPPORTED
    t.Prop5 = 0.01;
#endif /* PROPERTY_GETSET_SUPPORTED */

#ifdef SIMPLE_PROPERTY_GET_SUPPORTED
    v1 = t.Prop1;
    s = t.PropS1;
#endif /* SIMPLE_PROPERTY_GET_SUPPORTED */
#ifdef SIMPLE_PROPERTY_SET_SUPPORTED
    t.Prop2 = v2 + 1.0;
    t.PropS2 = "Set the string # 4";
#endif /* SIMPLE_PROPERTY_SET_SUPPORTED */
#ifdef PROPERTY_GET_SUPPORTED
    v3 = t.Prop3;
#endif /* PROPERTY_GET_SUPPORTED */
#ifdef PROPERTY_GETSET_SUPPORTED
    v5 = t.Prop5;
#endif /* PROPERTY_GETSET_SUPPORTED */

//  t.Prop1 = 30;

#ifdef PROPERTY_GET_SUPPORTED
    count = Thingy::StaticProp1;

    dcount = Thingy::StaticProp3;

    ((void)dcount);

    Thingy::StaticProp4 = 10.0;

    dcount = Thingy::StaticProp3;
#endif /* PROPERTY_GET_SUPPORTED */

    ((void)s);
    ((void)dcount);
    ((void)count);
    ((void)v5);
    ((void)v4);
    ((void)v3);
    ((void)v2);
    ((void)v1);

    return 0;
}

/* ////////////////////////////////////////////////////////////////////////// */
