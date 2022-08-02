/*

    Copyright David Abrahams 2003-2004
    Copyright Aleksey Gurtovoy 2003-2004

    Distributed under the Boost Software License, Version 1.0. 
    (See accompanying file LICENSE_1_0.txt or copy at 
    http://www.boost.org/LICENSE_1_0.txt)
            
    This file was automatically extracted from the source of 
    "C++ Template Metaprogramming", by David Abrahams and 
    Aleksey Gurtovoy.

    It FAILS to compile, as expected, with GCC 3.4.2 on Windows using
    the following command: 

        g++ -I..\..\boost_1_32_0 -c -o%TEMP%\metaprogram-chapter8-example7.o example7.cpp
        

*/
#include <boost/mpl/equal_to.hpp>

#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/static_assert.hpp>
namespace mpl = boost::mpl;
using namespace mpl::placeholders;


#include <boost/mpl/int.hpp>
#include <boost/mpl/multiplies.hpp>
#include <boost/mpl/equal.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/prior.hpp>
#include <boost/static_assert.hpp>

namespace mpl = boost::mpl;

template <class N>
struct factorial
  : mpl::eval_if<
        mpl::equal_to<N,mpl::int_<0> >     // check N == 0
      , mpl::int_<1>                    // 0! == 1
      , mpl::multiplies<                // N! == N * (N-1)!
            N
          , factorial<typename mpl::prior<N>::type>
        >
    >
{
    BOOST_STATIC_ASSERT(N::value >= 0); // for nonnegative N
};

factorial<mpl::int_<3> > xxx;



int const fact = factorial<mpl::int_<-6> >::value;
