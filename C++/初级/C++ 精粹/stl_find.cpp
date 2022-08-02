/*********************************************************************

  Filename:  stl_find.cpp
  Section:   17.6   STL  Sequence Algorithms
  Compiler:  Borland C++     Version 5.0       Summer 1996
  C++ Distilled: Descriptions, Prescriptions and Style  By Ira Pohl

*********************************************************************/

//Use of as istream_iterator iterator.
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

int main()
{
   string words[5] = { "my", "hop", "mop",
                       "hope", "cope"};
   string*   where;

   where = find(words, words + 5, "hop");
   cout << *++where << endl;                //mop
   sort(words, words + 5);
   where = find(words, words + 5, "hop");
   cout << *++where << endl;               //hope
}

