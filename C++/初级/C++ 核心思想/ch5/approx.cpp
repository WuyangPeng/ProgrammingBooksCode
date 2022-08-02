#include <iostream>
#include <algorithm>

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

int main()
{  
   double x;
   cout << "Enter a number: ";
   cin >> x;

   double y;
   cout << "Enter another number: ";
   cin >> y;

   if (approx_equal(x, y))
      cout << "The numbers are approximately equal.\n";
   else
      cout << "The numbers are different.\n";

   return 0;
}
