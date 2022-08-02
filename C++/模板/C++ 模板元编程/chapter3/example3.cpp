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

        g++ -I..\..\boost_1_32_0 -c -o%TEMP%\metaprogram-chapter3-example3.o example3.cpp
        

*/

#include <boost/mpl/int.hpp>
#include <boost/mpl/vector.hpp>

namespace boost
{
    namespace mpl
    {
    }
}
namespace mpl = boost::mpl;

#include <boost/mpl/vector_c.hpp>
namespace
{
    typedef mpl::vector_c<int, 1, 0, 0, 0, 0, 0, 0> mass;
    typedef mpl::vector_c<int, 0, 1, 0, 0, 0, 0, 0> length;  // or position
    typedef mpl::vector_c<int, 0, 0, 1, 0, 0, 0, 0> time;
    typedef mpl::vector_c<int, 0, 0, 0, 1, 0, 0, 0> charge;
    typedef mpl::vector_c<int, 0, 0, 0, 0, 1, 0, 0> temperature;
    typedef mpl::vector_c<int, 0, 0, 0, 0, 0, 1, 0> intensity;
    typedef mpl::vector_c<int, 0, 0, 0, 0, 0, 0, 1> angle;

}

// base dimension:        m l  t ...
typedef mpl::vector_c<int, 0, 1, -1, 0, 0, 0, 0> velocity;  // l/t
typedef mpl::vector_c<int, 0, 1, -2, 0, 0, 0, 0> acceleration;  // l/(t2)
typedef mpl::vector_c<int, 1, 1, -1, 0, 0, 0, 0> momentum;  // ml/t
typedef mpl::vector_c<int, 1, 1, -2, 0, 0, 0, 0> force;  // ml/(t2)

typedef mpl::vector_c<int, 0, 0, 0, 0, 0, 0, 0> scalar;
