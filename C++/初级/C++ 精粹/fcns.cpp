/*********************************************************************

  Filename:  fcns.cpp
  Section:   5      Linkage
  Compiler:  Borland C++     Version 5.0       Summer 1996
  C++ Distilled: Descriptions, Prescriptions and Style  By Ira Pohl

*********************************************************************/

// works with my_types.h and mainfile.cpp

//fcns.c to be separately compiled
#include <iostream.h>
#include "my_types.h"


void foo(c_string s)
{
   cout <<"\nOutput: " << s;
}

void title()
{
   cout << "\nTEST TYPEDEFS";
}

void pr_onoff()
{
   if (x == OFF)
       cout << "\nOFF";
   else
       cout << "\nON";
}

