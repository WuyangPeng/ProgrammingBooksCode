/*

    Copyright David Abrahams 2003-2004
    Copyright Aleksey Gurtovoy 2003-2004

    Distributed under the Boost Software License, Version 1.0. 
    (See accompanying file LICENSE_1_0.txt or copy at 
    http://www.boost.org/LICENSE_1_0.txt)
            
    This file was automatically extracted from the source of 
    "C++ Template Metaprogramming", by David Abrahams and 
    Aleksey Gurtovoy.

    It was built successfully with GCC 3.4.2 on Windows using
    the following command: 

        g++ -I..\..\boost_1_32_0 -c -o%TEMP%\metaprogram-chapter9-example37.o example37.cpp
        

*/
#include <boost/mpl/bool.hpp>

#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/static_assert.hpp>
namespace mpl = boost::mpl;
using namespace mpl::placeholders;


typedef char yes;      // sizeof(yes) == 1
typedef char (&no)[2]; // sizeof(no)  == 2


template <class T>
struct is_class_or_union
{
    // SFINAE eliminates this when the type of arg is invalid
    template <class U> 
    static yes tester(int U::*arg);
    
    // overload resolution prefers anything at all over "..."
    template <class U> 
    static no tester(...);
    
    // see which overload is chosen when U == T
    static bool const value
       = sizeof(is_class_or_union::tester<T>(0)) == sizeof(yes);

    typedef mpl::bool_<value> type;
};

struct X{};
BOOST_STATIC_ASSERT(is_class_or_union<X>::value);
BOOST_STATIC_ASSERT(!is_class_or_union<int>::value);
