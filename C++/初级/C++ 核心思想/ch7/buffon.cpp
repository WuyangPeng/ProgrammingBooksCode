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
   Converts an angle from degree to radian.
   @param alpha the angle in degrees
   @return the angle in radian
*/
double deg2rad(double alpha)
{  
   const double PI = 3.141592653589793;
   return alpha * PI / 180;
}

int main()
{  
   int NTRIES = 10000;
   int hits = 0;
   rand_seed();
   for (int i = 1; i <= NTRIES; i++)
   {  
      double ylow = rand_double(0, 2);
      double angle = rand_double(0, 180);
      double yhigh = ylow + sin(deg2rad(angle));
      if (yhigh >= 2) hits++;                      
   }
   cout << "Tries / Hits = " 
      << NTRIES * (1.0 / hits) << "\n";
   return 0;
}
