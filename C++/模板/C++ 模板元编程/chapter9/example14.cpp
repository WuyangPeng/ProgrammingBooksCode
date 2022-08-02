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

        g++ -I..\..\boost_1_32_0 -c -o%TEMP%\metaprogram-chapter9-example14.o example14.cpp
        

*/
#include <boost/mpl/vector.hpp>
#include <boost/type_traits/is_empty.hpp>

#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/static_assert.hpp>
namespace mpl = boost::mpl;
using namespace mpl::placeholders;

#include <iostream>
#include <typeinfo>
typedef mpl::vector<int&, long&, char*&> s;
#include <functional>

// base class template to be defined later
template <class F, bool F_empty, class G, bool G_empty>
class storage;

template <class R, class F, class G>
class compose_fg
  : storage<
        F, boost::is_empty<F>::value
      , G,boost::is_empty<G>::value
    >
{
   typedef storage<
       F,boost::is_empty<F>::value
     , G,boost::is_empty<G>::value
   > base;

 public:
    compose_fg(F const& f, G const& g)
      : base(f, g)
    {}

    template <class T>
    R operator()(T const& x) const
    {
        F const& f = this->get_f();
        G const& g = this->get_g();
        return f(g(x));
    }
};


template <class F, class G>
class storage<F,false,G,false> // neither F nor G is empty
{
 protected:
     storage(F const& f, G const& g)
       : f(f), g(g)
     {}
     F const& get_f() const { return f; }
     G const& get_g() const { return g; }
 private:
     F f;
     G g;
};

template <class F, class G>
class storage<F,false,G,true> // G is empty
  : private G
{
 protected:
     storage(F const& f, G const& g)
       : G(g), f(f)
     {}
     F const& get_f() const { return f; }
     G const& get_g() const { return *this; }
 private:
     F f;
};

template <class F, class G>
class storage<F,true,G,false> // F is empty
  : private F
{
 protected:
     storage(F const& f, G const& g)
       : F(f), g(g)
     {}
     F const& get_f() const { return *this; }
     G const& get_g() const { return g; }
 private:
     G g;
};

template <class F, class G>
class storage<F,true,G,true> // F and G are both empty
  : private F, private G
{
 protected:
     storage(F const& f, G const& g)
       : F(f), G(g)
     {}
     F const& get_f() const { return *this; }
     G const& get_g() const { return *this; }
};

 template <class T> T make();
 int x
   = make<compose_fg<int, std::negate<int>, std::logical_not<int> > >()(1)
   + make<compose_fg<int, int (*)(int), std::negate<int> > >()(2)
   + make<compose_fg<int, std::negate<int>, int (*)(int)> >()(3)
   + make<compose_fg<int, int (*)(int), int (*)(int)> >()(4);

