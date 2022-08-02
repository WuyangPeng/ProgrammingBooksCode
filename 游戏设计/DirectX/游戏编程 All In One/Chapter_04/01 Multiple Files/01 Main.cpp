 /* 01 Main.cpp */

 /* Include header file */
#include "Header.h"

 /* Input output stream header*/
#include <iostream>

main ()
{
 double Number;
 double SquaredNumber, CubedNumber;

 Number = 5;

  /* Call the function */
 SquaredNumber = Square (Number);
 CubedNumber = Cube (Number);

 std::cout << "Square of 5 = " << SquaredNumber << std::endl;
 std::cout << "Cube of 5 = " << CubedNumber << std::endl;

 return 0;
}
