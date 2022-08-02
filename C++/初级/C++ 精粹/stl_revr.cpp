/*********************************************************************

  Filename:  stl_revr.cpp
  Section:   17.6   STL Sequence Algorithms
  Compiler:  Borland C++     Version 5.0       Summer 1996
  C++ Distilled: Descriptions, Prescriptions and Style  By Ira Pohl

*********************************************************************/

//Use of as istream_iterator iterator.
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

int main()
{
   string first_names[5] = {"laura", "ira",
        "buzz", "debra", "twinkle"};
   string last_names[5] = {"pohl", "pohl",
        "dolsberry", "dolsberry", "star"};
   vector<string> names(first_names, first_names + 5);
   vector<string> names2(10);
   vector<string>::iterator p;

   copy(last_names, last_names + 5, names2.begin());
   copy(names.begin(), names.end(), names2.begin() + 5);
   reverse(names2.begin(), names2.end());
   for (p = names2.begin(); p != names2.end(); ++p)
      cout << *p <<'\t';
}

