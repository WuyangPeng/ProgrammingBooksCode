/*********************************************************************

  Filename:  stl_vect.cpp
  Section:   17.1   STL Sequence Containers
  Compiler:  Borland C++     Version 5.0       Summer 1996
  C++ Distilled: Descriptions, Prescriptions and Style  By Ira Pohl

*********************************************************************/

#include <iostream.h>
#include <deque>
#include <vector>

using namespace std;

int main()
{
   int data[5] = { 6, 8, 7, 6, 5 };
   vector<int> v(5, 6);            //5 element vector
   deque<int> d(data, data + 5);
   deque<int>::iterator p;

   cout << "\nDeque values" << endl;
   for (p = d.begin(); p != d.end(); ++p)
      cout << *p << '\t';      //print:6 8 7 6 5
   cout << endl;
   d.insert(d.begin(), v.begin(), v.end());
   for (p = d.begin(); p != d.end(); p++)
   cout << *p << '\t';   //print:6 6 6 6 6 6 8 7 6 5
}
