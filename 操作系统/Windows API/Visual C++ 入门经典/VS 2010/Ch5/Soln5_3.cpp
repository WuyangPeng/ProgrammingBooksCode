// Soln5_3.cpp
#include <iostream>
#include <cmath>
using std::cout;
using std::endl;
using std::sin;
using std::cos;
using std::tan;

const double DEG_TO_RAD = 57.2957795;

double sind(double d)
{
   return sin(d/DEG_TO_RAD);
}

double cosd(double d)
{
   return cos(d/DEG_TO_RAD);
}

double tand(double d)
{
   return tan(d/DEG_TO_RAD);
}

int main()
{
   cout << "cos(30) = " << cosd(30.0) << endl;
   cout << "sin(30) = " << sind(30.0) << endl;
   cout << "tan(30) = " << tand(30.0) << endl;

   return 0;
}
