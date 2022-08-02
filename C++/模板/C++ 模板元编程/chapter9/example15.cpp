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

        g++ -I..\..\boost_1_32_0 -c -o%TEMP%\metaprogram-chapter9-example15.o example15.cpp
        

*/
#include <boost/mpl/vector.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/fold.hpp>

#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/static_assert.hpp>
namespace mpl = boost::mpl;
using namespace mpl::placeholders;

#include <iostream>
#include <typeinfo>
typedef mpl::vector<int&, long&, char*&> s;
#include <functional>

    template <class T, class U>
    int test_type_of(U const&)
    {
        BOOST_MPL_ASSERT((boost::is_same<T,U>));
        return 0;
    }
    

// fine-grained struct element; stores a T and inherits More
template <class T, class More>
struct store : More
{
    T value;
};

typedef mpl::vector<short[2], long, char*, int> member_types;

struct empty {};

mpl::fold<
    member_types, empty, store<_2,_1>
>::type generated;


    namespace test_type_of0
    { //}
      int x = test_type_of<

store<int
  , store<char*
      , store<long
          , store<short[2], empty> > > >

>(
         generated
      ); //{
    }
    

long& x = static_cast<
            store<long, store<short[2], empty> >&
          >(generated).value;



namespace eggs {

template <class T, class U>
store<T,U> const& get(store<T,U> const& e)
{ 
    return e;
}

char* s = get<char*>(generated).value;

}

