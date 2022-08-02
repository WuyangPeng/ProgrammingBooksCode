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

        g++ -I..\..\boost_1_32_0 -c -o%TEMP%\metaprogram-appendixB-example14.o example14.cpp
        

*/
#include <boost/type_traits/add_const.hpp>
#include <iterator>

#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/static_assert.hpp>
namespace mpl = boost::mpl;
using namespace mpl::placeholders;


// Member type declarations
template <class C>
struct something
{
    typedef typename C::value_type value_type;
    typedef typename value_type::is_const is_const;
};


template <class T>
struct input_iterator_part_impl
{
    typedef typename boost::add_const<T>::type const_T;
};



template <class> class non_type_parameter;

template <
      class T
    , typename non_type_parameter<T>::type value
        = typename non_type_parameter<T>::type()
>
struct initialized
{};


template <class Sequence>
typename Sequence::iterator          // in return type
find(
    Sequence seq
  , typename Sequence::value_type x  // in parameter types
)
{
    typename Sequence::iterator it   // inside function body
      = seq.begin();    
    return 1;
}



  template <class,class> class projection_iterator_gen;
  template <class> class select1st;

template <class Sequence>
struct key_iterator_generator
{
    typedef typename projection_iterator_gen<
        select1st<typename Sequence::value_type>
      , typename Sequence::const_iterator
    >::type type;
};


template <class Iterator>
struct category_index
{
    template <long N> struct index
    {
        typedef char(&type)[N];
    };

    int category(std::input_iterator_tag)
    { return sizeof(typename index<1>::type); }

    int category(std::forward_iterator_tag)
    { return sizeof(typename index<2>::type); }
};

template <>
template <long N> 
struct category_index<int*>::index
{
    typedef char(&type)[N + 1];
};
