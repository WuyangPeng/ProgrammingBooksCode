/*********************************************************************

  Filename:  mainfile.cpp
  Section:   5      Linkage
  Compiler:  Borland C++     Version 5.0       Summer 1996
  C++ Distilled: Descriptions, Prescriptions and Style  By Ira Pohl

*********************************************************************/

//This file works with fcns.cpp and my_types.h to show linkage rules

#include  <iostream.h>
#include  "my_types.h"

int  x = 0;        //global x referred to in fcns.c

int main()
{
   c_string  f = "foo on you";
   ptr_f     pf = pr_onoff;

   foo("ENTER 0 or 1: ");
   cin >> x;
   if ( x == ON)
      pf = &title;
   pr_onoff();
   pf();
   x = !x;
   pf();
   foo(f);
}

