/*********************************************************************

  Filename:  power2.cpp
  Section:   10.4   Default Arguments
  Compiler:  Borland C++     Version 5.0       Summer 1996
  C++ Distilled: Descriptions, Prescriptions and Style  By Ira Pohl

*********************************************************************/

#include <iostream>
//pow() defaults to squaring n
int pow(int n, int k = 2)      //k = 2 is default
{
   if (k == 2)
      return (n * n);
   else
      return (pow(n, k - 1) * n);
}


int main()
{
   int r = 1;
   int r_sqrd, r_5th;

   while (r != 0) {
      cout << "Enter an integer  (or 0 to terminate): ";
      cin >> r;
      if (r != 0) {
         r_sqrd = pow(r);   //return r*r
         r_5th = pow(r, 5); //return r*r*r*r*r
         cout << "r_sqrd is " << r_sqrd << endl;
         cout << "r_5th is " << r_5th << endl;
      }
   }
}

