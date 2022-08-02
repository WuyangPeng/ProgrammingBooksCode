 /* '02 Main.cpp' */
#include <iostream>

 /* Start of program */
main (void)
{
  /* Variable declarations */
 const float   FeetPerMeter = 3.28084f;
 float   Length1;
 float   Length2;
 float   Length3;
  /* Get the from the user */
 std::cout << "Enter the first length in meters: ";
 std::cin >> Length1;
 std::cout << "Enter the second length in meters: ";
 std::cin >> Length2;
 std::cout << "Enter the third length in meters: ";
 std::cin >> Length3;
  /* Show the information */
 std::cout << "First length in feet is: " << Length1 * FeetPerMeter 
		         << std::endl;
 std::cout << "Second length in feet is: " << Length2 * FeetPerMeter
		         << std::endl;
 std::cout << "Third length in feet is: " << Length3 * FeetPerMeter 
		         << std::endl;

 return 0;
}
