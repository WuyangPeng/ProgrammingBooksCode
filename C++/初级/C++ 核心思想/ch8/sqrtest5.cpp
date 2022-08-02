#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>

using namespace std;

/**
   Sets the seed of the random number generator.
*/
void rand_seed()
{  
   int seed = static_cast<int>(time(0));
   srand(seed);
}

/** 
   Compute a random floating point number in a range
   @param a the bottom of the range
   @param b the top of the range
   @return a random floating point number x, 
   a <= x and x <= b
*/
double rand_double(double a, double b)
{  
   return a + (b - a) * rand() * (1.0 / RAND_MAX);
}

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
   rand_seed();
   int i;
   for (i = 1; i <= 100; i++)
   {  
      double x = rand_double(0, 1E6);
      double y = squareroot(x);
      if (!approx_equal(y, pow(x, 0.5))) 
         cout << "Test failed. ";
      else 
         cout << "Test passed. ";
      cout << "squareroot of " << x << " = " << y << "\n";
   }

   return 0;
}
