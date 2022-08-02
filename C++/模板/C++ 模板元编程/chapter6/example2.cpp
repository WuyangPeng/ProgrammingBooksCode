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

        g++ -I..\..\boost_1_32_0 -c -o%TEMP%\metaprogram-chapter6-example2.o example2.cpp
        

*/
#include <vector>
#include <algorithm>

#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/static_assert.hpp>
namespace mpl = boost::mpl;
using namespace mpl::placeholders;



   #include <boost/lambda/lambda.hpp>
   namespace ll
   {
       using boost::lambda::_1;

  #include <functional>
  void f(std::vector<int>& v)
  {
      typedef std::vector<int>::iterator v_iter;
  

std::transform(v.begin(), v.end(), v.begin(), _1 + 42);

  }
  
}

