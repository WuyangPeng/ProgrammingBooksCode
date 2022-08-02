/*********************************************************************

  Filename:  throw_it.cpp
  Section:   14.1   Throwing Exceptions
  Compiler:  Borland C++     Version 5.0       Summer 1996
  C++ Distilled: Descriptions, Prescriptions and Style  By Ira Pohl

*********************************************************************/

#include <iostream.h>

void foo()
{
   int  i;
   //will illustrate how an exception is thrown
   i = -15;
   throw i;
}

int main()
{
   try {
      foo();
   }
   catch(int n) { cerr << "exception caught\n " << n << endl;  }
}
