/*********************************************************************

  Filename:  stl_stak.cpp
  Section:   17.1   STL  Container Adaptors
  Compiler:  Borland C++     Version 5.0       Summer 1996
  C++ Distilled: Descriptions, Prescriptions and Style  By Ira Pohl

*********************************************************************/

#include <iostream>
#include <vector>
#include <stack>
#include <string>
using namespace std;

int main()
{
   stack<string, vector<string> > str_stack;
   string quote[3] =
    {"The wheel that squeaks the loudest\n",
     "Is the one that gets the grease\n",
     "Josh Billings\n" };

   for (int i =0; i < 3; ++i)
      str_stack.push(quote[i]);
   while (!str_stack.empty()) {
      cout << str_stack.top();
      str_stack.pop();
   }
}


