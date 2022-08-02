// Soln5_3.cpp
/*
  Defining _USE_MATH_DEFINE  before you include the cmath header
  makes math constants available from the cmath header.
  These include  M_PI which is pi, M_2_PI which is 2pi, and M_PI_2 which is pi/2
*/

#define _USE_MATH_DEFINES                      
#include <iostream>
#include <iomanip>
#include <cmath>

const double DEG_TO_RAD(M_PI/180.0);

double sind(double d)
{
  return std::sin(d*DEG_TO_RAD);
}

double cosd(double d)
{
  return std::cos(d*DEG_TO_RAD);
}

double tand(double d)
{
  return std::tan(d*DEG_TO_RAD);
}

int main()
{
  std::cout << "cos(60) = " << std::fixed << std::setprecision(2) << cosd(30.0) << std::endl;
  std::cout << "cos(90) = " << std::fixed << std::setprecision(2) << cosd(90.0) << std::endl;
  std::cout << "sin(30) = " << std::fixed << std::setprecision(2) << sind(30.0) << std::endl;
  std::cout << "sin(90) = " << std::fixed << std::setprecision(2) << sind(90.0) << std::endl;
  std::cout << "tan(30) = " << std::fixed << std::setprecision(2) << tand(30.0) << std::endl;
  std::cout << "tan(45) = " << std::fixed << std::setprecision(2) << tand(45.0) << std::endl;
}
