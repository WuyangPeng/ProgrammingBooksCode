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

        g++ -I..\..\boost_1_32_0 -I..\..\..\FC++.1.5 -c -o%TEMP%\metaprogram-chapter10-example35.o example35.cpp
        

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


template <class,class> struct plus_result;

struct plus
{
   template <class T, class U>
   typename plus_result<T,U>::type11
   operator()(T t, U u) const
   {
       return t + u;
   }
};
