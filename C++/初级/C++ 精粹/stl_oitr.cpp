/*********************************************************************

  Filename:  stl_oitr.cpp
  Section:   17.5   STL  Ostream Iterators
  Compiler:  Borland C++     Version 5.0       Summer 1996
  C++ Distilled: Descriptions, Prescriptions and Style  By Ira Pohl

*********************************************************************/

//Use of as ostream_iterator iterator.

#include <iostream>
#include <iterator>
using namespace std;

int main()
{
   int d[5] = {2, 3, 5, 7, 11};             //primes
   ostream_iterator<int> out(cout, "\t");

   for (int i = 0; i < 5; ++i)
      *out = d[i] ;
}


