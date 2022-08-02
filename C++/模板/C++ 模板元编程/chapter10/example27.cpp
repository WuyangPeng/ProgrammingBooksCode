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

        g++ -I..\..\boost_1_32_0 -c -o%TEMP%\metaprogram-chapter10-example27.o example27.cpp
        

*/
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

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


void f(std::vector<int> v) {

std::for_each(v.begin(), v.end(),
  ( 
    switch_statement(
      _1,
      case_statement<0>(std::cout << constant("zero")),
      case_statement<1>(std::cout << constant("one")),
      default_statement(std::cout << constant("other: ") << _1)
    ), 
    std::cout << constant("\n") 
  )
);

}

