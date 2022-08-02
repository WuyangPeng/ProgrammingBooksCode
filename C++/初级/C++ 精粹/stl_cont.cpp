/*********************************************************************

  Filename:  stl_cont.cpp
  Section:   17     STL
  Compiler:  Borland C++     Version 5.0       Summer 1996
  C++ Distilled: Descriptions, Prescriptions and Style  By Ira Pohl

*********************************************************************/

//Using the list container.
#include <iostream>
#include <list>               //list container
#include <numeric>            //for accumulate
using namespace std;

void print(const list<double> &lst)
{                //using an iterator to traverse lst
   list<double>::const_iterator p;

   for (p = lst.begin();
        p !=lst.end(); ++p)
      cout << *p << '\t';
   cout << endl;
}

int main()
{
   double w[4] = { 0.9, 0.8, 88, -99.99 };
   list<double> z;

   for( int i = 0; i < 4; ++i)
      z.push_front(w[i]);
   print(z);
   z.sort();
   print(z);
   cout << "sum is "
        << accumulate(z.begin(), z.end(), 0.0)
        << endl;
}
