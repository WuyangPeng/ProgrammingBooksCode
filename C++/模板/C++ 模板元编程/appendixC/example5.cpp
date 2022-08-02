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

        g++ -I..\..\boost_1_32_0 -c -o%TEMP%\metaprogram-appendixC-example5.o example5.cpp
        

*/

#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/static_assert.hpp>
namespace mpl = boost::mpl;
using namespace mpl::placeholders;


template<unsigned n, bool done = (n < 2)> 
struct lookup
{
    static unsigned const v1
      = lookup<n-1>::value;

    static unsigned const value = v1
#ifndef BASELINE // do memoized lookup
      + lookup<((n%2) ? 0 : n-2)>::value
#endif
      ;
};

template<unsigned n>
struct lookup<n,true>
{
    static unsigned const value = n;
};

lookup<5> x;

