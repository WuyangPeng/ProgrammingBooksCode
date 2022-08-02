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

        g++ -I..\..\boost_1_32_0 -c -o%TEMP%\metaprogram-chapter4-example16.o example16.cpp
        

*/
#include <boost/mpl/integral_c.hpp>

#include <boost/mpl/assert.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/static_assert.hpp>
namespace mpl = boost::mpl;
using namespace mpl::placeholders;

namespace cw_bug_workaround
{
    template <class T, T N>
    struct integral_c
    {
        static const T value = N;
        typedef integral_c<T, N> type;

        typedef T value_type;

        typedef mpl::integral_c<T, N + 1> next;
        typedef mpl::integral_c<T, N - 1> prior;
        operator T() const
        {
            return N;
        }
    };

}
