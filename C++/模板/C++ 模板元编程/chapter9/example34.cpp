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

        g++ -I..\..\boost_1_32_0 -c -o%TEMP%\metaprogram-chapter9-example34.o example34.cpp
        

*/

#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/static_assert.hpp>
namespace mpl = boost::mpl;
using namespace mpl::placeholders;


template <class Derived>
struct vehicle
{};

template <class Derived>
struct screw
{};


template <class Vehicle>
void drive(vehicle<Vehicle> const& v)
{
    Vehicle const& v_ = static_cast<Vehicle const&>(v);
    // ...
};

template <class Screw>
void drive(screw<Screw> const& s)
{
    Screw const& s_ = static_cast<Screw const&>(s);
    // ...
};
