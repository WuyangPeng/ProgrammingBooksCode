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

        g++ -I..\..\boost_1_32_0 -c -o%TEMP%\metaprogram-chapter3-example23.o example23.cpp
        

*/

#include <boost/mpl/int.hpp>
#include <boost/mpl/vector.hpp>

namespace boost
{
    namespace mpl
    {
    }
}
namespace mpl = boost::mpl;

#include <boost/mpl/minus.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/static_assert.hpp>

#include <boost/mpl/placeholders.hpp>
using namespace mpl::placeholders;

#include <boost/static_assert.hpp>
#include <boost/type_traits/add_pointer.hpp>
#include <boost/type_traits/is_same.hpp>

template <class T>
struct add_pointer
{
    typedef T* type;
};
