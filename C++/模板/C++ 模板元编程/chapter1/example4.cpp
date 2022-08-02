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

        g++ -I..\..\boost_1_32_0  -o%TEMP%\metaprogram-chapter1-example4.exe example4.cpp
        

*/

unsigned binary(unsigned long N)
{
    return N == 0 ? 0 : N % 10 + 2 * binary(N / 10);
}

#include <iostream>

int main()
{
    std::cout << binary(101010) << std::endl;
    return 0;
}
