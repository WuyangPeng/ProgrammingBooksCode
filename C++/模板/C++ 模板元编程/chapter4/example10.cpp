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

        g++ -I..\..\boost_1_32_0 -c -o%TEMP%\metaprogram-chapter4-example10.o example10.cpp
        

*/
#include <boost/mpl/bool.hpp>
#include <boost/mpl/equal.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/is_reference.hpp>
#include <boost/type_traits/is_scalar.hpp>
#include <string>

#include <boost/mpl/assert.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/static_assert.hpp>
namespace mpl = boost::mpl;
using namespace mpl::placeholders;

template <class T>
struct add_reference
{
    typedef T& type;
};

typedef mpl::vector<int, long, std::string> argument_types;

// build a list of parameter types for the argument types
typedef mpl::transform<
    argument_types, mpl::if_<
                        mpl::bool_<
                            boost::is_scalar<_1>::value || boost::is_reference<_1>::value>,
                        mpl::identity<_1>, add_reference<boost::add_const<_1>>>>::type param_types;

BOOST_MPL_ASSERT((mpl::equal<param_types, mpl::vector3<int const&, long const&, std::string const&>>));
