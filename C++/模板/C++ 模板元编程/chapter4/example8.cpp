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

        g++ -I..\..\boost_1_32_0  -o%TEMP%\metaprogram-chapter4-example8.exe example8.cpp
        

*/
#include <boost/type_traits/is_scalar.hpp>

#include <boost/mpl/assert.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/static_assert.hpp>
namespace mpl = boost::mpl;
using namespace mpl::placeholders;

#include <iostream>
template <class X>
void f(X const&, int z)
{
    if (boost::is_scalar<X>())  // invokes inherited operator bool()
    {
        // code here runs iff X is a scalar type
    }

    else
        std::cout << z << std::endl;
}
int main()
{
    f(1, 0);
    f("foo", 1);
}
