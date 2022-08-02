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

        g++ -I..\..\boost_1_32_0 -I..\..\boost_prerelease -c -o%TEMP%\metaprogram-chapter10-example20.o example20.cpp
        

*/


    #include <boost/named_params.hpp>

    struct slew_t; // tag types
    struct name_t;

    boost::keyword<name_t> name;    // keyword objects
    boost::keyword<slew_t> slew;

    struct keywords
      : boost::keywords<name_t, slew_t> {};
    
    BOOST_NAMED_PARAMS_FUN(int, f, 2, 2, keywords) 
    { return 0; }

    int x = 
    

f(slew = .799, name = "z");
