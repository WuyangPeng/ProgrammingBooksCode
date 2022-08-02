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

        g++ -I..\..\boost_1_32_0 -c -o%TEMP%\metaprogram-chapter5-example107.o example107.cpp
        

*/
#include <boost/mpl/next.hpp>
#include <boost/mpl/prior.hpp>

#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/static_assert.hpp>
namespace mpl = boost::mpl;
using namespace mpl::placeholders;


struct none {}; // tag type to denote no element

template <class T0 = none, class T1 = none, class T2 = none>
struct tiny
{
    typedef tiny type;

    typedef T0 t0;
    typedef T1 t1;
    typedef T2 t2;

    // ...
};


#include <boost/mpl/iterator_tags.hpp>

template <class Tiny, class Pos>
struct tiny_iterator
{
    typedef mpl::random_access_iterator_tag category;
};


namespace boost { namespace mpl {

   // forward iterator requirement
   template <class Tiny, class Pos>
   struct next<tiny_iterator<Tiny,Pos> >
   {
       typedef tiny_iterator<
           Tiny
         , typename mpl::next<Pos>::type
       > type;
   };
    
    // bidirectional iterator requirement
   template <class Tiny, class Pos>
   struct prior<tiny_iterator<Tiny,Pos> >
   {
       typedef tiny_iterator<
           Tiny
         , typename mpl::prior<Pos>::type
       > type;
   };

}}


template <class Tiny, int N> struct tiny_at;

// partially specialized accessors for each index
template <class Tiny>
struct tiny_at<Tiny,0>
{
    typedef typename Tiny::t0 type;
};

template <class Tiny>
struct tiny_at<Tiny,1>
{
    typedef typename  Tiny::t1 type;
};

template <class Tiny>
struct tiny_at<Tiny,2>
{
    typedef typename Tiny::t2 type;
};



#include <boost/mpl/at.hpp>

namespace boost { namespace mpl {

  template <class T0, class T1, class T2, class Pos>
  struct at<tiny<T0,T1,T2>, Pos>
    : tiny_at<tiny<T0,T1,T2>,Pos::value>
  {
  };

}}


template<class Sequence, class N>
struct at
  : mpl::at_impl<typename Sequence::tag>
      ::template apply<Sequence,N>
{
};
