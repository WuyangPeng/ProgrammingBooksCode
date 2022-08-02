/*********************************************************************

  Filename:  stl_numr.cpp
  Section:   17.6   STL  Numerical Algorithms
  Compiler:  Borland C++     Version 5.0       Summer 1996
  C++ Distilled: Descriptions, Prescriptions and Style  By Ira Pohl

*********************************************************************/

//Use of as ostream_iterator iterator.

#include <iostream>
#include <numeric>
using namespace std;

int main()
{
   double v1[3] = {1.0, 2.5, 4.6},
          v2[3] = {1.0, 2.0, -3.5};
   double sum, inner_p;

   sum = accumulate(v1, v1 + 3, 0.0);
   inner_p = inner_product(v1, v1 + 3, v2, 0.0);
   cout << "sum = " << sum
        << ",product = " << inner_p << endl;
}

