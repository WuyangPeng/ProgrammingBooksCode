/*********************************************************************

  Filename:  mult.cpp
  Section:   10     Functions
  Compiler:  Borland C++     Version 5.0       Summer 1996
  C++ Distilled: Descriptions, Prescriptions and Style  By Ira Pohl

*********************************************************************/

#include <iostream.h>
#include <complex.h>
#include <assert.h>

int mult(int n, int k = 2)
{
   assert(k > 1);
   if (k == 2)
      return (n * n);
   else
      return (mult(n, k - 1) * n);
}

double mult(double x, int k = 2)
{
   assert(k > 1);
   if (k == 2)
      return (x * x);
   else
      return (mult(x, k - 1) * x);
}



complex mult(complex w, int k = 2)
{
   assert(k > 1);
   if (k == 2)
      return (w * w);
   else
      return (mult(w, k - 1) * w);
}

int main()
{
   int i = 3;
   double d = 2.5;
   complex w(3,3.5); //3.0 + 3.5i

   cout << "\n3 squared and 3 cubed\n";
   cout << mult(i) << ", " << mult(i, 3)  << endl;
   cout << "\n2.5 squared and 2.5 to the 4th power\n";
   cout << mult(d) << ", " << mult(d, 4) << endl;
   cout << "\n3+3.5i to the 7th power\n";
   cout << mult(w, 7) << endl;
}

