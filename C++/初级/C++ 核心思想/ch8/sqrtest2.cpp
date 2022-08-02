#include <iostream>
#include <cmath>

using namespace std;

/**
   Tests whether two floating-point numbers are 
   approximately equal.
   @param x a floating-point number
   @param y another floating-point number
   @return true if x and y are approximately equal
*/
bool approx_equal(double x, double y)
{  
   const double EPSILON = 1E-14;
   if (x == 0) return fabs(y) <= EPSILON;
   if (y == 0) return fabs(x) <= EPSILON;
   return fabs(x - y) / max(fabs(x), fabs(y)) <= EPSILON;
}

/* Function to be tested */

/**
   Computes the square root using Heron's formula
   @param a an integer >= 0
   @return the square root of a
*/
double squareroot(double a)
{  
   if (a == 0) return 0;

   double xnew = a;
   double xold;

   do
   {  
      xold = xnew;
      xnew = (xold + a / xold) / 2;
   }
   while (!approx_equal(xnew, xold));

   return xnew;
}

/* Test harness */

int main()
{  
   double x;
   for (x = 0; x <= 10; x = x + 0.5)
   {  
      double y = squareroot(x);
      cout << "squareroot of " << x << " = " << y << "\n";
   }

   return 0;
}
