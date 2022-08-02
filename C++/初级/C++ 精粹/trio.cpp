/*********************************************************************

  Filename:  trio.cpp
  Section:   12.4   Pointer to Class Member
  Compiler:  Borland C++     Version 5.0       Summer 1996
  C++ Distilled: Descriptions, Prescriptions and Style  By Ira Pohl

*********************************************************************/

//Implementation of a safe array type vect with exceptions
// with exception handling and overloaded functions

#include  <iostream.h>
class trio {
public:
   int a, b, c;
} x, y, *q = &y;

int trio::*p = &trio::b;

int main ()
{
   x.a = 1;
   x.b = 2;
   x.c = 3;
   y.a = 4;
   y.b = 5;
   y.c = 6;
   cout << x.*p << endl;        //gets x.b
   cout << q ->*p << endl;      //gets y.b
}

