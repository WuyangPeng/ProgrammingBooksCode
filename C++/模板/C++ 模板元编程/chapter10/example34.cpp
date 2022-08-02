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

        g++ -I..\..\boost_1_32_0 -I..\..\..\FC++.1.5  -o%TEMP%\metaprogram-chapter10-example34.exe example34.cpp
        

*/
#include <cstddef>
              using std::ptrdiff_t;
              using std::size_t;
              #define BOOST_FCPP_ENABLE_LAMBDA
              #include "fcpp/prelude.hpp"
              #include "fcpp/lambda.hpp"
              using namespace boost::fcpp;
              lambda_var<3> Y;
              struct gee { 
                  template <class T> void operator=(T); 
              } g;
              
lambda_var<1> X;
lambda_var<2> Fun;


    #include <boost/lambda/lambda.hpp>
    using namespace boost::lambda;

    template <class F1, class F2>
    void compare_result(F1 f1, F2 f2, int x, int y)
    {
        assert(f1(x, y) == f2(x, y));
    }
    int main()
    {
        int a = 7;
        int b = 5;
        compare_result(

// Boost Lambda:
-(3 * _1) + _2 

,
lambda(X,Y)[ negate[ 3 %multiplies% X ] %plus% Y ]

, a, b);
    }
    

