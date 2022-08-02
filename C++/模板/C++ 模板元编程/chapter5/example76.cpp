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

        g++ -I..\..\boost_1_32_0 -c -o%TEMP%\metaprogram-chapter5-example76.o example76.cpp
        

*/
#include <boost/mpl/map.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/has_key.hpp>
#include <boost/mpl/key_type.hpp>
#include <boost/mpl/deref.hpp>

#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/static_assert.hpp>
namespace mpl = boost::mpl;
using namespace mpl::placeholders;



          typedef mpl::map1<mpl::pair<int,int> > S; 
          typedef int k;
          typedef int k2;
          typedef mpl::pair<int,int> t;
          typedef mpl::begin<S>::type pos1;
          typedef pos1 pos2;
          enum { tst=

mpl::has_key<
    S
  , mpl::key_type<
        S
      , mpl::deref<pos1>::type
    >::type
>::value

}; BOOST_STATIC_ASSERT(tst);

