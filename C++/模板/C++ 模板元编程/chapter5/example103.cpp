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

        g++ -I..\..\boost_1_32_0 -c -o%TEMP%\metaprogram-chapter5-example103.o example103.cpp
        

*/
#include <boost/mpl/vector.hpp>

#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/static_assert.hpp>
namespace mpl = boost::mpl;
using namespace mpl::placeholders;



  #include <boost/mpl/vector/vector10.hpp>
  using boost::mpl::vector0;
using boost::mpl::vector1;
using boost::mpl::vector2;
using boost::mpl::vector3;
  namespace protect {
  

namespace boost { namespace mpl {

  struct void_; // "no argument" marker

  // primary template declaration
  template <class T0 = void_, class T1 = void_, /* etc. */class T2 = void_, class T3 = void_>
  struct vector;

  // specializations
  template<>
  struct vector<> : vector0<> {};

  template<class T0>
  struct vector<T0> : vector1<T0> {};

  template<class T0, class T1>
  struct vector<T0,T1> : vector2<T0,T1> {};

  template<class T0, class T1, class T2>
  struct vector<T0,T1,T2> : vector3<T0,T1,T2> {};

  /* etc. */
}}

}

