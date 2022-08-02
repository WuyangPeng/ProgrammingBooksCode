/* /////////////////////////////////////////////////////////////////////////////
 * File:        properties_2_test.cpp
 *
 * Purpose:     Implementation file for the properties_2_test project.
 *
 * Created:     1st October 2003
 * Updated:     29th June 2004
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

#if defined(__STLSOFT_COMPILER_IS_MSVC) && \
    !defined(__STLSOFT_COMPILER_IS_COMO)
# pragma warning(disable : 4786)
#endif /* _MSC_VER */

stlsoft_ns_using(byte_t)

#include <stddef.h>

#undef stlsoft_raw_offsetof
#define stlsoft_raw_offsetof    offsetof

//#define USE_STRING

#if defined(__STLSOFT_COMPILER_IS_WATCOM) || \
    defined(__STLSOFT_COMPILER_IS_COMO)
# undef USE_STRING
#endif /* watcom || como */


#ifdef USE_STRING
# include <string>

# if !defined(__DMC__)
using std::string;
# endif /* !__DMC__ */
#endif /* USE_STRING */

#if defined(__STLSOFT_COMPILER_IS_WATCOM) || \
    (   defined(__STLSOFT_COMPILER_IS_MSVC) && \
        _MSC_VER < 1100)
# define typename   class
#endif /* __STLSOFT_COMPILER_IS_WATCOM */

/* ////////////////////////////////////////////////////////////////////////// */

//#define   TEMPLATE_FRIEND_FRIEND
//#define   TEMPLATE_FRIEND_FRIEND_CLASS
//#define   TEMPLATE_FRIEND_FRIEND_MAKER
//#define   TEMPLATE_FRIEND_FRIEND_MAKER_TEMPLATE

//#define   TEMPLATE_FRIEND_FRIEND_MAKER_FRIEND_TYPE_IS_CLASS


#if defined(__STLSOFT_COMPILER_IS_BORLAND)
# define    TEMPLATE_FRIEND_FRIEND
# define    TEMPLATE_FRIEND_FRIEND_MAKER_FRIEND_TYPE_IS_CLASS
#elif defined(__STLSOFT_COMPILER_IS_COMO)
# define    TEMPLATE_FRIEND_FRIEND /* Works in non-strict only */
# define    TEMPLATE_FRIEND_FRIEND_MAKER /* Works in non-strict only */
# define    TEMPLATE_FRIEND_FRIEND_MAKER_TEMPLATE /* Works in non-strict only */
# define    TEMPLATE_FRIEND_FRIEND_MAKER_FRIEND_TYPE_IS_CLASS
#elif defined(__STLSOFT_COMPILER_IS_DMC)
# define    TEMPLATE_FRIEND_FRIEND
# define    TEMPLATE_FRIEND_FRIEND_CLASS
# define    TEMPLATE_FRIEND_FRIEND_MAKER
# define    TEMPLATE_FRIEND_FRIEND_MAKER_TEMPLATE
# define    TEMPLATE_FRIEND_FRIEND_MAKER_FRIEND_TYPE_IS_CLASS
#elif defined(__STLSOFT_COMPILER_IS_GCC)
# if __GNUC__ < 3
#  define   TEMPLATE_FRIEND_FRIEND /* Not 3.2 */
# else /* ? __GNUC__ */
#  define   TEMPLATE_FRIEND_FRIEND_MAKER /* Not 2.95 */
#  define   TEMPLATE_FRIEND_FRIEND_MAKER_TEMPLATE /* Not 2.95 */
# endif /* __GNUC__ */
////# define    TEMPLATE_FRIEND_FRIEND_MAKER_FRIEND_TYPE_IS_CLASS
#elif defined(__STLSOFT_COMPILER_IS_INTEL)
# define    TEMPLATE_FRIEND_FRIEND
# define    TEMPLATE_FRIEND_FRIEND_MAKER
# define    TEMPLATE_FRIEND_FRIEND_MAKER_TEMPLATE
# define    TEMPLATE_FRIEND_FRIEND_MAKER_FRIEND_TYPE_IS_CLASS
#elif defined(__STLSOFT_COMPILER_IS_MSVC)
# define    TEMPLATE_FRIEND_FRIEND
# define    TEMPLATE_FRIEND_FRIEND_MAKER
# define    TEMPLATE_FRIEND_FRIEND_MAKER_TEMPLATE /* Not in 4.2 */
////# define    TEMPLATE_FRIEND_FRIEND_MAKER_FRIEND_TYPE_IS_CLASS
#elif defined(__STLSOFT_COMPILER_IS_MWERKS)
# define    TEMPLATE_FRIEND_FRIEND_CLASS
# define    TEMPLATE_FRIEND_FRIEND_MAKER
# define    TEMPLATE_FRIEND_FRIEND_MAKER_TEMPLATE
# define    TEMPLATE_FRIEND_FRIEND_MAKER_FRIEND_TYPE_IS_CLASS
#elif defined(__STLSOFT_COMPILER_IS_WATCOM)
# define    TEMPLATE_FRIEND_FRIEND
# define    TEMPLATE_FRIEND_FRIEND_CLASS
# define    TEMPLATE_FRIEND_FRIEND_MAKER
# define    TEMPLATE_FRIEND_FRIEND_MAKER_FRIEND_TYPE_IS_CLASS
#else
# error Compiler not tested with the direct_property_get_internal template
#endif

/* ////////////////////////////////////////////////////////////////////////// */

template<   typename    V   /* The actual property value type */
        ,   typename    R   /* The return type */
        ,   typename    C   /* The enclosing class */
        >
class direct_property_get_internal
{
public:
    typedef direct_property_get_internal<V, R, C>   class_type;

private:
    direct_property_get_internal(R value)
        : m_value(value)
    {}

    class_type &operator =(R value)
    {
        m_value = value;

        return *this;
    }

    STLSOFT_DECLARE_TEMPLATE_PARAM_AS_FRIEND(C);

public:
    operator R () const
    {
        return m_value;
    }

private:
    V   m_value;
};


template<   typename    V   /* The actual property value type */
        ,   typename    R   /* The return type */
        ,   typename    C   /* The enclosing class */
        >
class direct_property_set_internal
{
public:
    typedef direct_property_set_internal<V, R, C>   class_type;

private:
    direct_property_set_internal(R value)
        : m_value(value)
    {}

    operator R () const
    {
        return m_value;
    }

    STLSOFT_DECLARE_TEMPLATE_PARAM_AS_FRIEND(C);

public:
    class_type &operator =(R value)
    {
        m_value = value;

        return *this;
    }

private:
    V   m_value;
};


template<   typename    T
        ,   typename    R
#ifdef STLSOFT_CF_MEM_FUNC_AS_TEMPLATE_PARAM_SUPPORT
        ,   R (T::*PFn)() const
#endif /* STLSOFT_CF_MEM_FUNC_AS_TEMPLATE_PARAM_SUPPORT */
        ,   ptrdiff_t   (*PFnOff)()
        >
class property_get_external
{
public:
    operator R () const
    {
        ptrdiff_t   offset  =   (*PFnOff)();
        T           *pT     =   (T*)((byte_t*)this - offset);

        return (pT->*PFn)();
    }

#ifndef STLSOFT_CF_MEM_FUNC_AS_TEMPLATE_PARAM_SUPPORT
private:
    property_get_external(R (T::*pfn)() const)
        : PFn(pfn)
    {}

    STLSOFT_DECLARE_TEMPLATE_PARAM_AS_FRIEND(T);

private:
    R (T::*PFn)() const;

#endif /* STLSOFT_CF_MEM_FUNC_AS_TEMPLATE_PARAM_SUPPORT */
};


template<   typename T
        ,   typename V
        ,   typename R
#ifdef STLSOFT_CF_MEM_FUNC_AS_TEMPLATE_PARAM_SUPPORT
        ,   R (T::*PFn)() const
#endif /* STLSOFT_CF_MEM_FUNC_AS_TEMPLATE_PARAM_SUPPORT */
        ,   ptrdiff_t   (*PFnOff)()
        >
class property_get_internal
{
#ifdef STLSOFT_CF_MEM_FUNC_AS_TEMPLATE_PARAM_SUPPORT
    typedef property_get_internal<T, V, R, PFn, PFnOff> class_type;
#else
    typedef property_get_internal<T, V, R, PFnOff>      class_type;
#endif /* STLSOFT_CF_MEM_FUNC_AS_TEMPLATE_PARAM_SUPPORT */

private:
    property_get_internal(R value)
        : m_value(value)
    {}

#ifndef STLSOFT_CF_MEM_FUNC_AS_TEMPLATE_PARAM_SUPPORT
private:
    R (T::*PFn)(void) const;

private:
    property_get_internal(R (T::*pfn)(void) const)
        : PFn(pfn)
    {}

    STLSOFT_DECLARE_TEMPLATE_PARAM_AS_FRIEND(T);

#endif /* STLSOFT_CF_MEM_FUNC_AS_TEMPLATE_PARAM_SUPPORT */

    class_type &operator =(R value)
    {
        m_value = value;

        return *this;
    }

    void set_value(R value)
    {
        m_value = value;
    }
    R get_value() const
    {
        return m_value;
    }

    STLSOFT_DECLARE_TEMPLATE_PARAM_AS_FRIEND(T);

// Accessors
public:
    operator R() const
    {
        ptrdiff_t   offset  =   (*PFnOff)();
        T           *pT     =   (T*)((byte_t*)this - offset);

        return (pT->*PFn)();
    }

// Members
private:
    V   m_value;
};


/* ////////////////////////////////////////////////////////////////////////// */

#pragma pack(push, 1)

class Thing
{
public:
    Thing(int i1, int i2, char const *s3)
        : DirIntProp1(i1)
        , DirIntProp2(i2)
#ifdef USE_STRING
        , DirIntProp3(s3)
#endif /* USE_STRING */
        , m_IndExtProp1_value(41)
#ifndef STLSOFT_CF_MEM_FUNC_AS_TEMPLATE_PARAM_SUPPORT
        , IndExtProp1(&Thing::get_IndExtProp1)
#endif /* STLSOFT_CF_MEM_FUNC_AS_TEMPLATE_PARAM_SUPPORT */
        , IndIntProp1(73)
    {}

public:
    void Set_DirIntProp1(int i)
    {
        DirIntProp1 = i;
    }
    int Get_DirIntProp2() const
    {
        return DirIntProp2;
    }
#ifdef USE_STRING
    void SetProp3(char const *s)
    {
        DirIntProp3 = s;
    }
#endif /* USE_STRING */

    int get_IndExtProp1() const
    {
        return m_IndExtProp1_value;
    }

    int get_IndIntProp1() const
    {
        return IndIntProp1.get_value();
    }

#if 0
    static ptrdiff_t get_Value2Offset() { enum { offset = stlsoft_raw_offsetof(Thing, Value2) }; return offset; }
    static ptrdiff_t get_Value3Offset() { enum { offset = stlsoft_raw_offsetof(Thing, Value3) }; return offset; }
    union
    {
        PropertyGet<Thing, int, &Thing::get_Value2, &Thing::get_Value2Offset>       Value2;
        PropertyGet<Thing, int, &Thing::get_Value3, &Thing::get_Value3Offset>       Value3;
    };
#endif /* 0 */


public:
    direct_property_get_internal<int, int, Thing>                   DirIntProp1;
    direct_property_set_internal<int, int, Thing>                   DirIntProp2;
#ifdef USE_STRING
    direct_property_get_internal<string, string const &, Thing>     DirIntProp3;
#endif /* USE_STRING */

    static ptrdiff_t get_IndExtProp1Offset() { enum { offset = stlsoft_raw_offsetof(Thing, IndExtProp1) }; return offset; }
    static ptrdiff_t get_IndIntProp1Offset() { enum { offset = stlsoft_raw_offsetof(Thing, IndIntProp1) }; return offset; }
#ifdef STLSOFT_CF_MEM_FUNC_AS_TEMPLATE_PARAM_SUPPORT
    property_get_external<Thing, int, &Thing::get_IndExtProp1, &Thing::get_IndExtProp1Offset>       IndExtProp1;
    property_get_internal<Thing, int, int, &Thing::get_IndIntProp1, &Thing::get_IndIntProp1Offset>  IndIntProp1;
#else
    property_get_external<Thing, int, &Thing::get_IndExtProp1Offset>                                IndExtProp1;
    property_get_internal<Thing, int, int, &Thing::get_IndIntProp1Offset>                           IndIntProp1;
#endif /* STLSOFT_CF_MEM_FUNC_AS_TEMPLATE_PARAM_SUPPORT */


private:
    int m_IndExtProp1_value;
};


/* ////////////////////////////////////////////////////////////////////////// */

int main(int /* argc */, char ** /*argv*/)
{
//  puts("properties_2_test: " __STLSOFT_COMPILER_LABEL_STRING);

    /* . */
    Thing   thing(7, 9, "thing7");
    int     v1 = 0;
    int     v2 = 0;
    size_t  sz = 0;

    ((void)v1); ((void)v2); ((void)sz);

    sz = sizeof(int);

    ((void)v1); ((void)v2); ((void)sz);

    sz = sizeof(thing);

    ((void)v1); ((void)v2); ((void)sz);

    v1                  =   thing.DirIntProp1;
    thing.DirIntProp2   =   v2;

    ((void)v1); ((void)v2); ((void)sz);

    v1 = thing.IndExtProp1;

    ((void)v1); ((void)v2); ((void)sz);

    v1 = thing.IndIntProp1;

    ((void)v1); ((void)v2); ((void)sz);

#if 0
    thing.DirIntProp1 = 10;
    thing.DirIntProp2 = 10;
    thing.DirIntProp3 = "naughty";
    thing.DirIntProp3 = string("naughty");
#endif /* 0 */

    thing.Set_DirIntProp1(v1 * 10);

    v1                  =   thing.DirIntProp1;
    thing.DirIntProp2   =   v2;

    ((void)v1); ((void)v2); ((void)sz);

    v2 = thing.Get_DirIntProp2();

    v1                  =   thing.DirIntProp1;
    thing.DirIntProp2   =   v2 * 2;


    ((void)v1); ((void)v2); ((void)sz);

    v1                  =   thing.DirIntProp1;
    thing.DirIntProp2   =   v2;

#ifdef USE_STRING
    {
        string  v3 = 0;
        sz = sizeof(string);

        ((void)v1); ((void)v2); ((void)sz);

        v3  =   thing.DirIntProp3;
        v3  =   thing.DirIntProp3;
        v3  =   thing.DirIntProp3;
        thing.SetProp3("easy peasy");

        v3  =   thing.DirIntProp3;
    }
#endif /* USE_STRING */

//  thing.DirIntProp1 = 10;

    ((void)v1); ((void)v2); ((void)sz);

    return v1 + v2 + sz;
}

/* ////////////////////////////////////////////////////////////////////////// */

#if defined(__BORLANDC__) || \
    defined(__COMO__) || \
    defined(__DMC__) || \
    (   defined(__GNUC__) && \
        __GNUC__ < 3) || \
    defined(__INTEL_COMPILER) || \
    defined(__WATCOMC__) || \
    defined(_MSC_VER)
# define    DECLARE_TEMPLATE_PARAM_AS_FRIEND(T)     friend T
#elif defined(__MWERKS__)
# define    DECLARE_TEMPLATE_PARAM_AS_FRIEND(T)     friend class T
#elif defined(__GNUC__) && \
      __GNUC__ >= 3

# define    DECLARE_TEMPLATE_PARAM_AS_FRIEND(T)     \
                                                    \
    struct friend_maker                             \
    {                                               \
        typedef T T2;                               \
    };                                              \
                                                    \
    typedef typename friend_maker::T2 friend_type;  \
                                                    \
    friend friend_type

#endif /* compiler */


# if  defined(__BORLANDC__) || \
      defined(__COMO__) || \
      defined(__DMC__) || \
      defined(__INTEL_COMPILER) || \
      defined(__MWERKS__) || \
      defined(__WATCOMC__)
#  define DECLARE_TEMPLATE_PARAM_AS_FRIEND_CLASS_QUAL       class
# else
#  define DECLARE_TEMPLATE_PARAM_AS_FRIEND_CLASS_QUAL
# endif /* compiler */

# if (  defined(_MSC_VER) && \
        _MSC_VER < 1100) || \
    defined(__WATCOMC__)
#  define DECLARE_TEMPLATE_PARAM_AS_FRIEND_TYPENAME_TYPE
# else
#  define DECLARE_TEMPLATE_PARAM_AS_FRIEND_TYPENAME_TYPE    typename
# endif /* compiler */

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
        _MSC_VER >= 1300)
#else
# error Compiler not supported
#endif /* compiler */

/* ////////////////////////////////////////////////////////////////////////// */
