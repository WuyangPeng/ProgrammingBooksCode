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

        g++ -I..\..\boost_1_32_0 -c -o%TEMP%\metaprogram-appendixC-example7.o example7.cpp
        

*/

#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/static_assert.hpp>
namespace mpl = boost::mpl;
using namespace mpl::placeholders;



#define N 3

template< int i, int test > struct deep
  : deep<i-1,test>
{};

template< int test> struct deep<0,test>
{
    enum { value = 0 };
};

template< int n > struct test
{
    enum { value = deep<N,n>::value };
};

int main()
{
    return test<0>::value + test<1>::value + test<2>::value
        + test<3>::value + test<4>::value + test<5>::value
        + test<6>::value + test<7>::value + test<8>::value
        + test<9>::value;
}
