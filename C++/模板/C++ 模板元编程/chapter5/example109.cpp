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

        g++ -I..\..\boost_1_32_0 -c -o%TEMP%\metaprogram-chapter5-example109.o example109.cpp
        

*/
#include <boost/mpl/next.hpp>
#include <boost/mpl/prior.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/minus.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/begin.hpp>
#include <boost/mpl/end.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/clear.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/mpl/push_back.hpp>

#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/static_assert.hpp>
namespace mpl = boost::mpl;
using namespace mpl::placeholders;



struct none;
template <class Tiny, int N> struct tiny_at;

struct tiny_tag {};

template <class T0 = none, class T1 = none, class T2 = none>
struct tiny
{
    typedef tiny_tag tag;
    typedef tiny type;
    typedef T0 t0;
    typedef T1 t1;
    typedef T2 t2;
};

namespace boost { namespace mpl {
   template <>
   struct at_impl<tiny_tag>
   {
       template <class Tiny, class N>
       struct apply : tiny_at<Tiny, N::value>
       {};
   };
}}


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



#include <boost/mpl/deref.hpp>

namespace boost { namespace mpl {

   template <class Tiny, class Pos>
   struct deref< tiny_iterator<Tiny,Pos> >
     : at<Tiny,Pos>
   {
   };

}}      



  #include <boost/mpl/advance.hpp>
  #include <boost/mpl/distance.hpp>

namespace boost { namespace mpl {

   // random access iterator requirements
   template <class Tiny, class Pos, class N>
   struct advance<tiny_iterator<Tiny,Pos>,N>
   {
       typedef tiny_iterator<
            Tiny
          , typename mpl::plus<Pos,N>::type
       > type;
    };

    template <class Tiny, class Pos1, class Pos2>
    struct distance< 
        tiny_iterator<Tiny,Pos1>
      , tiny_iterator<Tiny,Pos2>
    >
      : mpl::minus<Pos2,Pos1>
    {};
 
}}


namespace boost { namespace mpl {

   template <>
   struct begin_impl<tiny_tag>
   {
       template <class Tiny>
       struct apply
       {
            typedef tiny_iterator<Tiny,int_<0> > type;
       };
   };
}}


template <class T0, class T1, class T2>
struct tiny_size                
  : mpl::int_<3> {};

template <class T0, class T1>
struct tiny_size<T0,T1,none> 
  : mpl::int_<2> {};

template <class T0>
struct tiny_size<T0,none,none>   
  : mpl::int_<1> {};

template <>
struct tiny_size<none,none,none> 
  : mpl::int_<0> {};

namespace boost { namespace mpl {
   template <>
   struct end_impl<tiny_tag>
   {
       template <class Tiny>
       struct apply
       {
           typedef tiny_iterator<
               Tiny
             , typename tiny_size<
                   typename Tiny::t0
                 , typename Tiny::t1
                 , typename Tiny::t2
               >::type
           >
           type;
       };
   };
}}


namespace boost { namespace mpl {
   template <>
   struct size_impl<tiny_tag>
   {
       template <class Tiny>
       struct apply
         : tiny_size<
               typename Tiny::t0
             , typename Tiny::t1
             , typename Tiny::t2
           >
       {};
   };
}}


namespace boost { namespace mpl {
   template <>
   struct clear_impl<tiny_tag>
   {
       template <class Tiny>
       struct apply : tiny<>
       {};
   };
   template <>
   struct push_front_impl<tiny_tag>
   {
       template <class Tiny, class T>
       struct apply
         : tiny<T, typename Tiny::t0, typename Tiny::t1>
       {};
   };
}}


template <class Tiny, class T, int N>
struct tiny_push_back;

template <class Tiny, class T>
struct tiny_push_back<Tiny,T,0>
  : tiny<T,none,none>
{};

template <class Tiny, class T>
struct tiny_push_back<Tiny,T,1>
  : tiny<typename Tiny::t0,T,none>
{};

template <class Tiny, class T>
struct tiny_push_back<Tiny,T,2>
  : tiny<typename Tiny::t0,typename Tiny::t1,T>
{};

namespace boost { namespace mpl {
   template <>
   struct push_back_impl<tiny_tag>
   {
       template <class Tiny, class T>
       struct apply
         : tiny_push_back<
             Tiny, T, size<Tiny>::value
           >
       {};
   };
}}

#include <boost/mpl/push_back.hpp>
#include <boost/mpl/pop_back.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/mpl/back.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/empty.hpp>

void f()
{
    typedef tiny<> v0;
    typedef tiny<char> v1;
    typedef tiny<char,long> v2;
    typedef tiny<char,char,int> v3;

    BOOST_MPL_ASSERT_RELATION(mpl::size<v0>::value, ==, 0);
    BOOST_MPL_ASSERT_RELATION(mpl::size<v1>::value, ==, 1);
    BOOST_MPL_ASSERT_RELATION(mpl::size<v2>::value, ==, 2);
    BOOST_MPL_ASSERT_RELATION(mpl::size<v3>::value, ==, 3);

    BOOST_MPL_ASSERT(( mpl::empty<v0> ));
    BOOST_MPL_ASSERT_NOT(( mpl::empty<v1> ));
    BOOST_MPL_ASSERT_NOT(( mpl::empty<v2> ));
    BOOST_MPL_ASSERT_NOT(( mpl::empty<v3> ));

    BOOST_MPL_ASSERT((boost::is_same<mpl::front<v1>::type,char>));
    BOOST_MPL_ASSERT((boost::is_same<mpl::back<v1>::type,char>));
    BOOST_MPL_ASSERT((boost::is_same<mpl::front<v2>::type,char>));
    BOOST_MPL_ASSERT((boost::is_same<mpl::back<v2>::type,long>));
    BOOST_MPL_ASSERT((boost::is_same<mpl::front<v3>::type,char>));
    BOOST_MPL_ASSERT((boost::is_same<mpl::back<v3>::type,int>));
}

void g()
{
    typedef tiny<> v0;

    typedef mpl::push_back<v0,int>::type v1;
    BOOST_MPL_ASSERT((boost::is_same<mpl::back<v1>::type,int>));

    typedef mpl::push_front<v1,char>::type v2;
    BOOST_MPL_ASSERT((boost::is_same<mpl::back<v2>::type,int>));
    BOOST_MPL_ASSERT((boost::is_same<mpl::front<v2>::type,char>));

    typedef mpl::push_back<v2,long>::type v3;
    BOOST_MPL_ASSERT((boost::is_same<mpl::back<v3>::type,long>));
}

void h()
{
    typedef tiny<> v0;
    typedef tiny<char> v1;
    typedef tiny<char,long> v2;
    typedef tiny<char,char,char> v3;

    BOOST_MPL_ASSERT_RELATION(mpl::size<v0>::value, ==, 0);
    BOOST_MPL_ASSERT_RELATION(mpl::size<v1>::value, ==, 1);
    BOOST_MPL_ASSERT_RELATION(mpl::size<v2>::value, ==, 2);
    BOOST_MPL_ASSERT_RELATION(mpl::size<v3>::value, ==, 3);
}


