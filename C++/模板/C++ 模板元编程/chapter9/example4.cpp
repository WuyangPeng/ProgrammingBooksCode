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

        g++ -I..\..\boost_1_32_0  -o%TEMP%\metaprogram-chapter9-example4.exe example4.cpp
        

*/
#include <boost/mpl/vector.hpp>
#include <boost/mpl/for_each.hpp>

#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/static_assert.hpp>
namespace mpl = boost::mpl;
using namespace mpl::placeholders;

#include <iostream>
#include <typeinfo>
typedef mpl::vector<int&, long&, char*&> s;

struct visit_type    // generalized visitation function object
{
    template <class Visitor>
    void operator()(Visitor) const
    {
        Visitor::visit();
    }
};

template <class T>   // specific visitor for type printing
struct print_visitor
{
    static void visit()
    {
        std::cout << typeid(T).name() << std::endl;
    }
};

int main()
{
    mpl::for_each<s, print_visitor<_1> >(visit_type());
}
