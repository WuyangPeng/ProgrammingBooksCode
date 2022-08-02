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

        g++ -I..\..\boost_1_32_0 -c -o%TEMP%\metaprogram-appendixB-example15.o example15.cpp
        

*/
#include <iterator>

#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/static_assert.hpp>
namespace mpl = boost::mpl;
using namespace mpl::placeholders;



namespace {

template <class Iterator, long N> struct index
{
    typedef char(&type)[N];
};

template <class Iterator>
struct category_index
{
    int category(std::input_iterator_tag)
    { return sizeof(typename index<Iterator,1>::type); }

    int category(std::forward_iterator_tag)
    { return sizeof(typename index<Iterator,2>::type); }
};

}

