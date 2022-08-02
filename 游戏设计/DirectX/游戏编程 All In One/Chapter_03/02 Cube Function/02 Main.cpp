 /* '02 Main.cpp' */

 /* Input output stream header*/
#include <iostream>

double Cube (double Value);

main ()
{
 double Number, CubeNumber;

 std::cout << "Enter a number: ";
 std::cin >> Number;
  
  /* Number is the function argument */
 CubeNumber = Cube (Number);

 std::cout << CubeNumber << std::endl;

 return 0;
}

 /* Value is the function parameter */
double Cube (double Value)
{ 
 double CubeReturn;

 CubeReturn = Value * Value * Value;

 return CubeReturn;
}
