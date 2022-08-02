/*********************************************************************

  Filename:  array.cpp
  Section:   13     Templates
  Compiler:  Borland C++     Version 5.0       Summer 1996
  C++ Distilled: Descriptions, Prescriptions and Style  By Ira Pohl

*********************************************************************/

// Note = this file modified to use T not TYPE
//Get storage off stack for array
//  Title: array

#include <iostream.h>

template <typename T = int, int n = 100>
class array_n {
public:
   T  a[n];
};

int main()
{
   array_n<double, 50>  x, y;


   int i;

   for (i = 0; i < 50; ++i)
      x.a[i] = i;
   for (i = 0; i < 50; ++i)
      y.a[i] = i * 2;
   for (i = 0; i < 50; ++i)
      cout << x.a[i] << "\t";
   for (i = 0; i < 50; ++i)
      cout << y.a[i] << "\t";
   x = y;                     //should work efficiently
   for (i = 0; i < 50; ++i)
      cout << x.a[i] << "\t";
}
