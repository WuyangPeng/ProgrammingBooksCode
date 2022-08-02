/*********************************************************************

  Filename:  style.cpp
  Section:   4      Declarations and Scope Rules
  Compiler:  Borland C++     Version 5.0       Summer 1996
  C++ Distilled: Descriptions, Prescriptions and Style  By Ira Pohl

*********************************************************************/

//Separate declarations from statements with a blank line.
//Start file level declarations in column 1.
//Declarations should be as local as possible.
//Use typedef to replace multi-token type declarations.
//This program produces tables of functions in the range [0, 1]
//Section 4 Ask Dr P
//Ira Pohl July 1996

#include <iostream>
#include <math>
#include <string>
using namespace std;

typedef double (*dbl_fcn)(double);

int main()
{
   double x;
   dbl_fcn  f[3] = {sqrt, sin, cos};
   string  name[3] = {"square root", "sine", "cosine"};

   for (int i = 0; i < 3; ++i) {
      cout << name[i] << endl;
      for(x = 0.0; x < 1.0; x += 0.1)
         cout <<  f[i](x) << " , ";
      cout << endl;
   }
}
