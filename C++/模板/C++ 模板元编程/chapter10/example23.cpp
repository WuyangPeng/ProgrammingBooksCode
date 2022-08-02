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

        g++ -I..\..\boost_1_32_0 -c -o%TEMP%\metaprogram-chapter10-example23.o example23.cpp
        

*/
#include <string>
#include <algorithm>


#include <ext/functional>


struct Visitor { void visit(int) const; };

struct X { float foo(float) const; } obj;


    template <class T> int test(T);
    using namespace std;
    namespace ext = __gnu_cxx;
    using namespace ext;
    double const pi = 3.14;
    

int test1 = test(
bind1st(std::plus<std::string>(), "hello, ")

); int test2 = test(
compose2(
    std::multiplies<float>()
  , bind2nd(std::minus<float>(), 1)
  , identity<float>())

); int test3 = test(
mem_fun_ref(&X::foo)(obj, pi)

);
            void test4(int*first,int*last,Visitor v)
            { 
                 std::for_each(
    first
  , last
  , bind1st(mem_fun_ref(&Visitor::visit), v));

}

