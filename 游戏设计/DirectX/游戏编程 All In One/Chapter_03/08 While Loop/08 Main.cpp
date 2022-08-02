 /* '08 Main.cpp' */

 /* Input output stream header*/
#include <iostream>
 /* Math header*/
#include <math.h>

main ()
{
 short Number = 1;

 while (Number <= 20)
 {
  std::cout << "The square root of " << Number << " is: ";
  std::cout << sqrt (Number) << std::endl;
  Number ++;
 }

 return 0;
}
