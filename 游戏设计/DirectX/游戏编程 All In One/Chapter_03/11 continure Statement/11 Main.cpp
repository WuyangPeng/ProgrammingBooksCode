 /* '11 Main.cpp' */

 /* Input output stream header*/
#include <iostream>
 /* Math header*/
#include <math.h>

double DegreeToRadian (double Angle);

main ()
{
 short Angle;

 for (Angle = 0; Angle < 180; Angle += 10)
 {
  if (Angle == 90)
  {
   std::cout << "The tangent of 90 is invalid."  << std::endl;
   continue;
  }
  std::cout << "The tangent of " << Angle << " is: ";
  std::cout << tan( DegreeToRadian(Angle) ) << std::endl;
 }

 return 0;
}

double DegreeToRadian (double Angle)
{
 double Radian;

 Radian = (Angle * 180) / 3.14159;

 return Radian;
}
