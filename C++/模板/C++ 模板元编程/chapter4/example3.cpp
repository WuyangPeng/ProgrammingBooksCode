/*

    Copyright David Abrahams 2003-2004
    Copyright Aleksey Gurtovoy 2003-2004

    Distributed under the Boost Software License, Version 1.0. 
    (See accompanying file LICENSE_1_0.txt or copy at 
    http://www.boost.org/LICENSE_1_0.txt)
            
    This file was automatically extracted from the source of 
    "C++ Template Metaprogramming", by David Abrahams and 
    Aleksey Gurtovoy.

    It FAILS to compile, as expected, with GCC 3.4.2 on Windows using
    the following command: 

        g++ -I..\..\boost_1_32_0 -c -o%TEMP%\metaprogram-chapter4-example3.o example3.cpp
        

*/

#include <boost/mpl/assert.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/static_assert.hpp>
namespace mpl = boost::mpl;
using namespace mpl::placeholders;

template <class T>
struct param_type;

template <class T>
class holder
{
public:
    holder(typename param_type<T>::type x)
        : x{ x }
    {
    }
    // ...
private:
    T x;
};

#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_scalar.hpp>

template <class T>
struct param_type : mpl::if_<typename boost::is_scalar<T>::type, T, T const&>
{
};

int a[4];
// holder<int (&)[4]> x(a);
holder<int> y(a[0]);
// holder<int[4]> z(a);
