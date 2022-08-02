/*********************************************************************

  Filename:  stl_iitr.cpp
  Section:   17.4   STL  Istream Iterators
  Compiler:  Borland C++     Version 5.0       Summer 1996
  C++ Distilled: Descriptions, Prescriptions and Style  By Ira Pohl

*********************************************************************/

//Use of as istream_iterator iterator.
#include <iostream>
#include <iterator>
using namespace std;

int main()
{
   int d[5];
   cout << "\nEnter 5 integer: " << endl;
   istream_iterator<int, ptrdiff_t> in(cin);

   for (int i = 0; i < 4; ++i)
      d[i] = *in++;
   d[4] = *in;         //get last cached int
   for (int i = 0; i < 5; ++i)
      cout << "\nd[" << i << "] = " << d[i] << endl;

}

