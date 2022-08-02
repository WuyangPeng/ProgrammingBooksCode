/* /////////////////////////////////////////////////////////////////////////////
 * File:        field_properties_test.cpp
 *
 * Purpose:     Implementation file for the field_properties_test project.
 *
 * Created:     6th October 2003
 * Updated:     22nd October 2003
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
#include <stlsoft_field_properties.h>

//#define   TEST_INTERNAL_PROPERTIES
#define TEST_EXTERNAL_PROPERTIES

#ifdef TEST_INTERNAL_PROPERTIES
stlsoft_ns_using(field_property_get)
stlsoft_ns_using(field_property_set)
#endif /* TEST_INTERNAL_PROPERTIES */
#ifdef TEST_EXTERNAL_PROPERTIES
stlsoft_ns_using(field_property_get_external)
stlsoft_ns_using(field_property_set_external)
#endif /* TEST_EXTERNAL_PROPERTIES */

/* ////////////////////////////////////////////////////////////////////////// */

typedef long    Internal_type;
typedef double  External_type;

/* ////////////////////////////////////////////////////////////////////////// */

#ifdef TEST_INTERNAL_PROPERTIES
class Internal
{
public:
    field_property_get<Internal_type, Internal_type, Internal>  Prop1;
    field_property_set<Internal_type, Internal_type, Internal>  Prop2;

//  Internal() : Prop1(0) {}

public:
    void set_Value1(Internal_type v)
    {
        Prop1.m_value = v;
    }
    Internal_type get_Value2() const
    {
        return Prop2;
    }

    void dump_size() const
    {
        size_t  cbDataMemberTypes   =   sizeof(Internal_type) + sizeof(Internal_type);
        size_t  cbFields            =   0;
        size_t  cbProperties        =   sizeof(Prop1) + sizeof(Prop2);
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
#endif /* TEST_INTERNAL_PROPERTIES */

#ifdef TEST_EXTERNAL_PROPERTIES
class External
{
public:
#if 1
    field_property_get_external<volatile External_type, External_type>  Propg;
    field_property_set_external<volatile External_type, External_type>  Props;
#else /* ? 0 */
    static ptrdiff_t Propg_offset() { return (ptrdiff_t)(&External::Propg) - (ptrdiff_t)(&External::m_value); }
    static ptrdiff_t Props_offset() { return (ptrdiff_t)(&External::Props) - (ptrdiff_t)(&External::m_value); }
# ifdef STLSOFT_CF_ANONYMOUS_UNION_SUPPORT
    union
    {
# endif /* STLSOFT_CF_ANONYMOUS_UNION_SUPPORT */
    field_property_get_external<volatile External_type, External_type, &External::Propg_offset> Propg;
    field_property_set_external<volatile External_type, External_type, &External::Props_offset> Props;
# ifdef STLSOFT_CF_ANONYMOUS_UNION_SUPPORT
    };
# endif /* STLSOFT_CF_ANONYMOUS_UNION_SUPPORT */
#endif /* 0 */

public:
    External()
        : Propg(m_value)
        , Props(m_value)
    {}

    void dump_size() const
    {
        size_t  cbDataMemberTypes   =   sizeof(External_type) + sizeof(External_type);
        size_t  cbFields            =   sizeof(m_value);
        size_t  cbProperties        =   sizeof(Propg) + sizeof(Props);
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
    volatile External_type  m_value;
};
#endif /* TEST_EXTERNAL_PROPERTIES */

/* ////////////////////////////////////////////////////////////////////////// */

int main(int /* argc */, char ** /*argv*/)
{
    puts("field_properties_test: " __STLSOFT_COMPILER_LABEL_STRING);

    ////////////////////////////////////

#ifdef TEST_INTERNAL_PROPERTIES
    size_t      sz1 =   sizeof(Internal);

    printf("sizeof(Internal): %d\n", sz1);

    Internal().dump_size();
#endif /* TEST_INTERNAL_PROPERTIES */
    
#ifdef TEST_EXTERNAL_PROPERTIES
    size_t      sz2 =   sizeof(External);

    printf("sizeof(External): %d\n", sz2);

    External().dump_size();
#endif /* TEST_EXTERNAL_PROPERTIES */

    ////////////////////////////////////

#ifdef TEST_INTERNAL_PROPERTIES
    Internal        simple1;
    Internal_type   v1;
    Internal_type   v2;

#if 0
    field_property_get<Internal_type, Internal_type, Internal>  Prop1(simple1.Prop1);

    simple1.Prop1 = simple1.Prop1;

    field_property_set<Internal_type, Internal_type, Internal>  Prop2(simple1.Prop2);

    simple1.Prop2 = simple1.Prop2;
#endif /* 0 */

    v1 = simple1.Prop1;
    v2 = simple1.get_Value2();

    printf("simple1, random initialised: %d %d\n", v1, v2);

    printf("simple1, setting to 101 and 202\n");
    simple1.set_Value1(101);
    simple1.Prop2 = 202;

    v1 = simple1.Prop1;
    v2 = simple1.get_Value2();

    printf("simple1: %d %d\n", v1, v2);
#endif /* TEST_INTERNAL_PROPERTIES */

    ////////////////////////////////////

#ifdef TEST_EXTERNAL_PROPERTIES
    External        simple2;
    External_type   v3;

    v3 = simple2.Propg;

    printf("simple2, random initialised: %G\n", v3);

    printf("simple2, setting to 303.0303\n");

    simple2.Props = 303.0303;

    v3 = simple2.Propg;

    printf("simple2: %G\n", v3);
#endif /* TEST_EXTERNAL_PROPERTIES */

    return 0;
}

/* ////////////////////////////////////////////////////////////////////////// */
