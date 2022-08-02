/* /////////////////////////////////////////////////////////////////////////////
 * File:        poab_test.cpp
 *
 * Purpose:     Implementation file for the poab_test project.
 *
 * Created:     3rd December 2003
 * Updated:     4th March 2004
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

#if defined(__WATCOMC__)
typedef char const                      *string_t;
#elif defined(WIN32)
# include <stlsoft_simple_string.h>
typedef stlsoft::basic_simple_string<char>  string_t;
#else
# include <string>
# if !defined(__DMC__) && \
     (  !defined(_MSC_VER) || \
        _MSC_VER > 1020)
using std::string;
# endif /* compiler */
typedef string                          string_t;
#endif /* os */

#ifndef COMP_NAME
# error You must define COMP_NAME, e.g. "CodeWarrior 8"
#endif /* COMP_NAME */

#define stringize_(x)   #x
#define stringize(x)    stringize_(x)

#define COMPILER        stringize(COMP_NAME)


#include "object.h"

#include <stdio.h>
#include <stdlib.h>

/* ////////////////////////////////////////////////////////////////////////// */

class Object1
    : public IObject
{
public:
    typedef Object1     class_type;

public:
    virtual void SetName(char const *s)
    {
        m_name = s;
    }
    virtual char const *GetName() const
    {
        return m_name;
    }

#ifndef POAB_COMPILER_HAS_COMPATIBLE_VTABLES
public:
    Object1()
        : IObject(GetVTable())
    {}
    Object1(Object1 const &rhs)
        : IObject(GetVTable())
        , m_name(rhs.m_name)
    {}

private:
    static void SetName_(IObject *this_, char const *s)
    {
        static_cast<class_type*>(this_)->SetName(s);
    }
    static char const *GetName_(IObject const *this_)
    {
        return static_cast<class_type const*>(this_)->GetName();
    }

    static vtable_t *GetVTable()
    {
        static vtable_t s_vt = MakeVTable();

        return &s_vt;
    }

    static vtable_t MakeVTable()
    {
        vtable_t vt = { SetName_, GetName_ };

        return vt;
    }
#endif /* !POAB_COMPILER_HAS_COMPATIBLE_VTABLES */

public:
    void *operator new(size_t cb)
    {
        return malloc(cb);
    }
private:
    char const *m_name;
};

/* ////////////////////////////////////////////////////////////////////////// */

class Object2
    : public IObject
{
public:
    typedef Object2     class_type;

public:
    virtual ~Object2()
    {}

    virtual void SetName(char const *s)
    {
        m_name = s;
    }
    virtual char const *GetName() const
    {
#ifdef __WATCOMC__
        return m_name;
#else /* ? __WATCOMC__ */
        return m_name.c_str();
#endif /* __WATCOMC__ */
    }

#ifndef POAB_COMPILER_HAS_COMPATIBLE_VTABLES
public:
    Object2()
        : IObject(GetVTable())
    {}

private:
    static void SetName_(IObject *this_, char const *s)
    {
        static_cast<class_type*>(this_)->SetName(s);
    }
    static char const *GetName_(IObject const *this_)
    {
        return static_cast<class_type const*>(this_)->GetName();
    }

    static vtable_t *GetVTable()
    {
        static vtable_t s_vt = MakeVTable();

        return &s_vt;
    }

    static vtable_t MakeVTable()
    {
        vtable_t vt = { SetName_, GetName_ };

        return vt;
    }
#endif /* !POAB_COMPILER_HAS_COMPATIBLE_VTABLES */

public:
    void *operator new(size_t cb)
    {
        return malloc(cb);
    }
private:
    string_t    m_name;
};

class Object3
    : public Object2
{
public:
#ifndef __WATCOMC__
    virtual void SetName(char const *s)
    {
        Object2::SetName((string_t("[") + s + "]").c_str());
    }
#endif /* !__WATCOMC__ */
};

/* ////////////////////////////////////////////////////////////////////////// */

extern "C"
IObject *create_Object(int i, char const *s)
{
    printf("Creating object in C++ (%u, %s)\n", sizeof(IObject), COMPILER);

    IObject *pobj;

    switch(i)
    {
        case    0:
//          delete new Object1();
            pobj = new Object1(Object1());
            break;
        case    1:
            pobj = new Object2;
            break;
        default:
        case    2:
            pobj = new Object3;
            break;
    }

    if(NULL != pobj)
    {
#ifdef POAB_COMPILER_HAS_COMPATIBLE_VTABLES
        printf("Using C++ vtable\n");
#else /* ? POAB_COMPILER_HAS_COMPATIBLE_VTABLES */
        printf("Using portable vtable\n");
#endif /* POAB_COMPILER_HAS_COMPATIBLE_VTABLES */

        pobj->SetName(s);
    }

    return pobj;
}

/* ////////////////////////////////////////////////////////////////////////// */
