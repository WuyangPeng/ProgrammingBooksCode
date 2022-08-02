/* /////////////////////////////////////////////////////////////////////////////
 * File:        method_properties_test.cpp
 *
 * Purpose:     Implementation file for the method_properties_test project.
 *
 * Created:     6th October 2003
 * Updated:     24th October 2003
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
#include <string.h>
#include <stlsoft.h>
#include <stlsoft_method_properties.h>

#define TEST_INTERNAL_PROPERTIES
#define TEST_EXTERNAL_PROPERTIES
#define UNION_FOR_EXTERNAL_PROPERTIES

#ifdef TEST_INTERNAL_PROPERTIES
stlsoft_ns_using(method_property_get)
stlsoft_ns_using(method_property_set)
stlsoft_ns_using(method_property_getset)
#endif /* TEST_INTERNAL_PROPERTIES */
#ifdef TEST_EXTERNAL_PROPERTIES
stlsoft_ns_using(method_property_get_external)
stlsoft_ns_using(method_property_set_external)
stlsoft_ns_using(method_property_getset_external)
stlsoft_ns_using(static_method_property_get_external)
stlsoft_ns_using(static_method_property_set_external)
stlsoft_ns_using(static_method_property_getset_external)
#endif /* TEST_EXTERNAL_PROPERTIES */
#ifndef UNION_FOR_EXTERNAL_PROPERTIES
# define STLSOFT_CF_ANONYMOUS_UNION_SUPPORT
#endif /* !UNION_FOR_EXTERNAL_PROPERTIES */

#include <string>

stlsoft_ns_using_std(string)

/* ////////////////////////////////////////////////////////////////////////// */

#define STLSOFT_CF_CLASS_CAN_PARAMETERIZE_TEMPLATE_WITH_PRIVATE_METHOD

#if defined(__BORLANDC__) || \
    defined(__DMC__) || \
    defined(__GNUC__) || \
    defined(__MWERKS__)
# undef STLSOFT_CF_CLASS_CAN_PARAMETERIZE_TEMPLATE_WITH_PRIVATE_METHOD
#endif /* STLSOFT_CF_CLASS_CAN_PARAMETERIZE_TEMPLATE_WITH_PRIVATE_METHOD */

/* ////////////////////////////////////////////////////////////////////////// */

typedef long    Internal_type;
typedef double  External_type;

/* ////////////////////////////////////////////////////////////////////////// */

#ifdef TEST_INTERNAL_PROPERTIES
class Internal_raw
{
    Internal_type   Prop1;
    Internal_type   Prop2;
    Internal_type   Prop3;

public:
    void dump_size() const
    {
        size_t  cbDataMemberTypes   =   sizeof(Internal_type) + sizeof(Internal_type) + sizeof(Internal_type);
        size_t  cbFields            =   sizeof(Prop1) + sizeof(Prop2) + sizeof(Prop3);
        size_t  cbProperties        =   0;
        size_t  cbMembers           =   cbFields + cbProperties;
        size_t  cbClass             =   sizeof(*this);
        size_t  cbPad               =   cbClass - cbMembers;
        size_t  cbPropertyCost      =   0;

        printf("\nInternal_raw\n==========\n");
        printf( " data member types:  %u\n", cbDataMemberTypes);
        printf( " fields:             %u\n", cbFields);
        printf( " members:            %u\n", cbMembers);
        printf( " class:              %u\n", cbClass);
        printf( " properties:         %u\n", cbProperties);
        printf( " pad:                %u\n", cbPad);
        printf( " property cost:      %d / %u\n", cbPropertyCost, cbClass);
    }
};

class Internal
{
public:
    typedef Internal    class_type;

#ifndef STLSOFT_CF_MEM_FUNC_AS_TEMPLATE_PARAM_SUPPORT
public:
    Internal()
        : Prop1(&Internal::get_Prop1)
        , Prop2(&Internal::set_Prop2)
        , Prop3(&Internal::get_Prop3, &Internal::set_Prop3)
    {}
#endif /* STLSOFT_CF_MEM_FUNC_AS_TEMPLATE_PARAM_SUPPORT */


public:
    /// These methods must be defined before the template
    Internal_type get_Prop1() const
    {
        return Prop1.m_value;
    }
    void set_Prop1(Internal_type v)
    {
        Prop1.m_value = v;
    }
    Internal_type get_Prop2() const
    {
        return Prop2.m_value;
    }
    void set_Prop2(Internal_type v)
    {
        Prop2.m_value = v;
    }
    Internal_type get_Prop3() const
    {
        return Prop3.m_value;
    }
    void set_Prop3(Internal_type v)
    {
        Prop3.m_value = v;
    }

#ifdef STLSOFT_CF_CLASS_CAN_PARAMETERIZE_TEMPLATE_WITH_PRIVATE_METHOD
private:
#else
public:
#endif /* STLSOFT_CF_CLASS_CAN_PARAMETERIZE_TEMPLATE_WITH_PRIVATE_METHOD */
    static ptrdiff_t Prop1_offset() { return stlsoft_raw_offsetof(Internal, Prop1); }
    static ptrdiff_t Prop2_offset() { return stlsoft_raw_offsetof(Internal, Prop2); }
    static ptrdiff_t Prop3_offset() { return stlsoft_raw_offsetof(Internal, Prop3); }
public:
#ifdef STLSOFT_CF_MEM_FUNC_AS_TEMPLATE_PARAM_SUPPORT
//  method_property_get<Internal_type, Internal_type, Internal, &Internal::Prop1_offset, &Internal::get_Prop1>                                      Prop1;

    STLSOFT_METHOD_PROPERTY_GET(Internal_type, Internal_type, Internal, get_Prop1, Prop1);
    STLSOFT_METHOD_PROPERTY_SET(Internal_type, Internal_type, Internal, set_Prop2, Prop2);
    STLSOFT_METHOD_PROPERTY_GETSET(Internal_type, Internal_type, Internal_type, Internal, get_Prop3, set_Prop3, Prop3);
#else /* ? STLSOFT_CF_MEM_FUNC_AS_TEMPLATE_PARAM_SUPPORT */
    method_property_get<Internal_type, &Internal::Prop1_offset, Internal_type, Internal>                                                            Prop1;
    method_property_set<Internal_type, &Internal::Prop2_offset, Internal_type, Internal>                                                            Prop2;
    method_property_getset<Internal_type, Internal_type, Internal_type, &Internal::Prop3_offset, Internal>                                          Prop3;
#endif /* STLSOFT_CF_MEM_FUNC_AS_TEMPLATE_PARAM_SUPPORT */

    void dump_size() const
    {
        size_t  cbDataMemberTypes   =   sizeof(Internal_type) + sizeof(Internal_type) + sizeof(Internal_type);
        size_t  cbFields            =   0;
        size_t  cbProperties        =   sizeof(Prop1) + sizeof(Prop2) + sizeof(Prop3);
        size_t  cbMembers           =   cbFields + cbProperties;
        size_t  cbClass             =   sizeof(*this);
        size_t  cbPad               =   cbClass - cbMembers;
        size_t  cbPropertyCost      =   cbProperties - cbDataMemberTypes;

        printf("\nInternal\n======\n");
        printf( " data member types:  %u\n", cbDataMemberTypes);
        printf( " fields:             %u\n", cbFields);
        printf( " members:            %u\n", cbMembers);
        printf( " class:              %u\n", cbClass);
        printf( " properties:         %u\n", cbProperties);
        printf( " pad:                %u\n", cbPad);
        printf( " property cost:      %d / %u\n", cbPropertyCost, cbClass);
    }
};


class InternalWithString
{
public:
    string const &get_Prop3() const
    {
        return Prop3.m_value;
    }
    void set_Prop3(char const *v)
    {
        Prop3.m_value = v;
    }

    static ptrdiff_t Prop3_offset() { return stlsoft_raw_offsetof(InternalWithString, Prop3); }
    method_property_getset<string, string const &, char const *, InternalWithString, &InternalWithString::Prop3_offset, &InternalWithString::get_Prop3, &InternalWithString::set_Prop3> Prop3;
};
#endif /* TEST_INTERNAL_PROPERTIES */

#ifdef TEST_EXTERNAL_PROPERTIES
class External_raw
{
    External_type   m_value;

public:
    void dump_size() const
    {
        size_t  cbDataMemberTypes   =   sizeof(External_type);
        size_t  cbFields            =   sizeof(m_value);
        size_t  cbProperties        =   0;
        size_t  cbMembers           =   cbFields + cbProperties;
        size_t  cbClass             =   sizeof(*this);
        size_t  cbPad               =   cbClass - cbMembers;
        size_t  cbPropertyCost      =   0;

        printf("\nInternal_raw\n==========\n");
        printf( " data member types:  %u\n", cbDataMemberTypes);
        printf( " fields:             %u\n", cbFields);
        printf( " members:            %u\n", cbMembers);
        printf( " class:              %u\n", cbClass);
        printf( " properties:         %u\n", cbProperties);
        printf( " pad:                %u\n", cbPad);
        printf( " property cost:      %d / %u\n", cbPropertyCost, cbClass);
    }
};

class External
{
public:
#if 0
    void *operator new (size_t cb)
    {
        void *pv = ::operator new(cb);

printf("\n*********** %u, %u *************\n", cb, sizeof(External));

        memset(pv, 0x33, cb);

        return pv;
    }
#endif /* 0 */

    External()
#ifndef STLSOFT_CF_MEM_FUNC_AS_TEMPLATE_PARAM_SUPPORT
        : Propg(&External::get_Prop)
        , Props(&External::set_Prop)
        , Prop(&External::get_Prop, &External::set_Prop)
#endif /* STLSOFT_CF_MEM_FUNC_AS_TEMPLATE_PARAM_SUPPORT */
    {}

public:
    typedef External_type   value_type;

    value_type get_Prop() const
    {
        return m_value;
    }
    void set_Prop(value_type value)
    {
        m_value = value;
    }

#ifdef STLSOFT_CF_CLASS_CAN_PARAMETERIZE_TEMPLATE_WITH_PRIVATE_METHOD
private:
#else
public:
#endif /* STLSOFT_CF_CLASS_CAN_PARAMETERIZE_TEMPLATE_WITH_PRIVATE_METHOD */
    static ptrdiff_t Propg_offset() { return stlsoft_raw_offsetof(External, Propg); }
    static ptrdiff_t Props_offset() { return stlsoft_raw_offsetof(External, Props); }
    static ptrdiff_t Prop_offset() { return stlsoft_raw_offsetof(External, Prop); }
public:
#ifdef STLSOFT_CF_MEM_FUNC_AS_TEMPLATE_PARAM_SUPPORT
# ifdef STLSOFT_CF_ANONYMOUS_UNION_SUPPORT
    union
    {
# endif /* STLSOFT_CF_ANONYMOUS_UNION_SUPPORT */
    method_property_get_external<value_type, External, &External::Propg_offset, &External::get_Prop>                                Propg;
    method_property_set_external<value_type, External, &External::Props_offset, &External::set_Prop>                                Props;
    method_property_getset_external<value_type, value_type, External, &External::Prop_offset, &External::get_Prop, &External::set_Prop> Prop;
# ifdef STLSOFT_CF_ANONYMOUS_UNION_SUPPORT
    };
# endif /* STLSOFT_CF_ANONYMOUS_UNION_SUPPORT */
#else /* ? STLSOFT_CF_MEM_FUNC_AS_TEMPLATE_PARAM_SUPPORT */
    method_property_get_external<value_type, External, &External::Propg_offset>                                                 Propg;
    method_property_set_external<value_type, External, &External::Props_offset>                                                 Props;
    method_property_getset_external<value_type, value_type, External, &External::Prop_offset>                                           Prop;
#endif /* STLSOFT_CF_MEM_FUNC_AS_TEMPLATE_PARAM_SUPPORT */

    void dump_size() const
    {
        size_t  cbDataMemberTypes   =   sizeof(External_type) + sizeof(External_type) + sizeof(External_type);
        size_t  cbFields            =   sizeof(m_value);
        size_t  cbProperties        =   sizeof(Propg) + sizeof(Props) + sizeof(Prop);
        size_t  cbMembers           =   cbFields + cbProperties;
        size_t  cbClass             =   sizeof(*this);
        size_t  cbPad               =   cbClass - cbMembers;
        size_t  cbPropertyCost      =   cbClass - cbFields;

        printf("\nExternal\n========\n");
        printf( " data member types:  %u\n", cbDataMemberTypes);
        printf( " fields:             %u\n", cbFields);
        printf( " members:            %u\n", cbMembers);
        printf( " class:              %u\n", cbClass);
        printf( " properties:         %u\n", cbProperties);
        printf( " pad:                %u\n", cbPad);
        printf( " property cost:      %d / %u\n", cbPropertyCost, cbClass);
    }

private:
    value_type  m_value;
};
#endif /* TEST_EXTERNAL_PROPERTIES */

/* ////////////////////////////////////////////////////////////////////////// */

int main(int /* argc */, char ** /*argv*/)
{
    puts("method_properties_test: " __STLSOFT_COMPILER_LABEL_STRING);

#ifdef STLSOFT_CF_MEM_FUNC_AS_TEMPLATE_PARAM_SUPPORT
    puts("Using member-function as template parameters\n");
#else /* ? STLSOFT_CF_MEM_FUNC_AS_TEMPLATE_PARAM_SUPPORT */
    puts("Not using member-function as template parameters\n");
#endif /* STLSOFT_CF_MEM_FUNC_AS_TEMPLATE_PARAM_SUPPORT */

    ////////////////////////////////////

#ifdef TEST_INTERNAL_PROPERTIES
    size_t      sz1 =   sizeof(Internal);

    printf("sizeof(Internal): %d\n", sz1);

    Internal_raw().dump_size();
    Internal().dump_size();
#endif /* TEST_INTERNAL_PROPERTIES */

#ifdef TEST_EXTERNAL_PROPERTIES
    size_t      sz2 =   sizeof(External);

    printf("sizeof(External): %d\n", sz2);

    External_raw().dump_size();
    External().dump_size();
    printf("\n");
#endif /* TEST_EXTERNAL_PROPERTIES */

    ////////////////////////////////////

#ifdef TEST_INTERNAL_PROPERTIES
    Internal    simple1;
    int         v1;
    int         v2;
    int         v3;

    v1 = simple1.Prop1;
    v2 = simple1.get_Prop2();
    v3 = simple1.Prop3;

    printf("simple1, random initialised: %d %d %d\n", v1, v2, v3);

    printf("simple1, setting to 101, 202 and 303\n");
    simple1.set_Prop1(101);
    simple1.Prop2 = 202;
    simple1.Prop3 = 303;

    v1 = simple1.Prop1;
    v2 = simple1.get_Prop2();
    v3 = simple1.Prop3;

    printf("simple1: %d %d %d\n", v1, v2, v3);

    ////////////////////////////////////

    printf("sizeof(InternalWithString): %u\n", sizeof(InternalWithString));
    printf("sizeof(std::string): %u\n", sizeof(string));
    printf("sizeof(InternalWithString::Prop3): %u\n", sizeof(InternalWithString().Prop3));

    InternalWithString  iws;

    iws.Prop3 = "Hello Natty!";

    string          s   =   iws.Prop3;

#endif /* TEST_INTERNAL_PROPERTIES */

    ////////////////////////////////////

#ifdef TEST_EXTERNAL_PROPERTIES
    External    &simple2 = *new External();
    double      v4;

    v4 = simple2.Propg;

    printf("simple2, random initialised: %G\n", v4);

    printf("simple2, setting to 303.0303\n");

    simple2.Prop    =   (External::value_type)303.0303;
    simple2.Props   =   2 * simple2.Prop;

    v4 = simple2.Prop;

    printf("simple2: %G\n", v4);
#endif /* TEST_EXTERNAL_PROPERTIES */

    return 0;
}

/* ////////////////////////////////////////////////////////////////////////// */
