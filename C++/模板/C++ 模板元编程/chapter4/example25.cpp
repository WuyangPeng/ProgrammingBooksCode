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

        g++ -I..\..\boost_1_32_0 -c -o%TEMP%\metaprogram-chapter4-example25.o example25.cpp
        

*/
#include <list>

#include <boost/mpl/assert.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/static_assert.hpp>
namespace mpl = boost::mpl;
using namespace mpl::placeholders;

#include <algorithm>

template <class Container, class Value>
typename Container::iterator container_find(Container& c, Value const& v)
{
    return std::find(c.begin(), c.end(), v);
}

template <class T>
int eat(T)
{
    return 0;
}

std::list<int> x(10);
std::list<int> const y(10);
int a = eat(container_find(x, 3));
