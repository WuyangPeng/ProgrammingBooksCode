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

        g++ -I..\..\boost_1_32_0 -c -o%TEMP%\metaprogram-chapter10-example25.o example25.cpp
        

*/
#include <string>
#include <algorithm>

            #include <boost/lambda/lambda.hpp>
            #include <boost/lambda/control_structures.hpp>
            #include <boost/lambda/switch.hpp>
            namespace boost { namespace lambda {
              template<int N> 
              struct
              plain_return_type_2<arithmetic_action<plus_action>, char[N], std::string> {
                 typedef std::string type;
              };
            }} // namespace boost::lambda
            using namespace boost::lambda;
            using boost::lambda::_1;
            using boost::lambda::_2;
            std::string world("world");
            float pi = 3.14;


void f() {

float a[5][10]; 
int i;
std::for_each(a, a+5, 
  for_loop(var(i)=0, var(i)<10, ++var(i), 
     _1[var(i)] /= 2
  )
);

}

