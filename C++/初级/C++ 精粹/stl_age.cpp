/*********************************************************************

  Filename:  map_age.cpp
  Section:   17.1   STL Associative Containers
  Compiler:  Borland C++     Version 5.0       Summer 1996
  C++ Distilled: Descriptions, Prescriptions and Style  By Ira Pohl

*********************************************************************/

#include <iostream>
#include <map>
#include <string>
using namespace std;

int main()
{
   map<string, int, less<string> > name_age;

   name_age["Pohl,Laura"] = 7;
   name_age["Dolsberry,Betty"] = 39;
   name_age["Pohl,Tanya"] = 14;
   cout << "Laura is  "
        << name_age["Pohl,Laura"]
        << " years old." << endl;
}

