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

        g++ -I..\..\boost_1_32_0 -c -o%TEMP%\metaprogram-chapter2-example23.o example23.cpp
        

*/

template <class T, class S>
T polymorphic_downcast(S&);

struct A
{
};
struct B : A
{
};

B b;
A* a_ptr = &b;
B* b_ptr = polymorphic_downcast<B*>(a_ptr);

A& a_ref = b;
B& b_ref = polymorphic_downcast<B&>(b_ref);
