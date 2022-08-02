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

        g++ -I..\..\boost_1_32_0 -c -o%TEMP%\metaprogram-chapter10-example6.o example6.cpp
        

*/


#include <cstdio>
int yym = 0;
int const yylen[] = { 3 };
int const yyvsp[] = { 3 };
int const yyn = 8;
int yyval = 0;
void f(int& yyssp) {

// ...
yym = yylen[yyn];
yyval = yyvsp[1-yym];
switch (yyn)
{
case 1:
{ std::printf("= %d\n", yyvsp[0]); std::fflush(stdout); }
break;
case 8:
{ yyval = yyvsp[-2] * yyvsp[0]; }
break;
case 9:
{ yyval = yyvsp[-2] / yyvsp[0]; }
break;
case 11:
{ yyval = yyvsp[-2] + yyvsp[0]; }
break;
case 12:
{ yyval = yyvsp[-2] - yyvsp[0]; }
break;
}
yyssp -= yym;
// ...

}

