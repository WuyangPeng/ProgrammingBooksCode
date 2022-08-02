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

        g++ -I..\..\boost_1_32_0 -c -o%TEMP%\metaprogram-chapter10-example28.o example28.cpp
        

*/
#include <vector>
#include <iostream>


    #include <boost/spirit/phoenix.hpp>
    using namespace phoenix;
    void f(std::vector<int> a)
    {
    

for_each(a.begin(), a.end(), 
         if_(arg1 % 2 != 0)
         [ 
            std::cout << arg1 
         ]
         .else_
         [
            std::cout << val('.')
         ]
);

    }
    

