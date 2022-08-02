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

        g++ -I..\..\boost_1_32_0 -c -o%TEMP%\metaprogram-chapter2-example22.o example22.cpp
        

*/

template <class, class, class>
struct replace_type
{
    typedef int type;
};

typedef replace_type<void*, void, int>::type t1;  // int*

typedef replace_type<
    int const* [10], int const, long>::type t2;  // long* [10]

typedef replace_type<
    char& (*)(char&), char&, long&>::type t3;  // long& (*)(long&)
