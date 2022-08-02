 /* '06 Main.cpp' */

 /* Input output stream header*/
#include <iostream>

long Exponential (unsigned long Number, short Exponent);

main (void)
{
 long ExponentialValue;

 ExponentialValue = Exponential (4, 5);

 std::cout << ExponentialValue << std::endl;

 return 0;
}

long Exponential (unsigned long Number, short Exponent)
{
 static long OriginalNumber = Number;
  
  /* Performs the exponential operatorion */
 Number *= OriginalNumber;
  /* Verify that the exponent is valid */
 if (Exponent > 2)
 {
  return Exponential (Number, Exponent-1);
 }

 return Number;
}
