 /* '01 Main.cpp' */

 /* Input output stream header*/
#include <iostream>

 // Function prototype */
double Square (double Value);

main ()
{
 double Number, SquaredNumber;
  
 Number = 5;
  
  /* Call the function */
 SquaredNumber = Square (Number);

 std::cout << SquaredNumber << std::endl;

 return 0;
}

 /* Function definition */
double Square (double Value)
{
  /* Function code */
 double SquareReturn;

 SquareReturn = Value * Value;

 return SquareReturn;
}
