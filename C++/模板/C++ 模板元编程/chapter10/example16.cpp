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

        g++ -I..\..\boost_1_32_0 -I..\..\..\Blitz++-0.7 -c -o%TEMP%\metaprogram-chapter10-example16.o example16.cpp
        

*/

    #define __restrict__
    namespace {
    double j0(double);
    double j1(double);
    double y0(double);
    double y1(double);
    }
    #include <blitz/array.h>
    using namespace blitz;
    


void f(Array<float,2>& B) {

Array<float,2> A(3,3);

A = 1, 2, 3,
    4, 5, 6,
    7, 8, 9;


// add the first two rows and columns of A to B
B += A(Range(0,2), Range(0,2));

}

