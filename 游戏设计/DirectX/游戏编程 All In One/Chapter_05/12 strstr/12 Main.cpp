 /* '12 Main.cpp' */

 /* Input output stream header file */
#include <iostream>

 /* Start */
main (void)
{
  /* Declare two strings */
 char FirstString [255];
 char SecondString [255];

  /* Get two strings from the user */
 std::cout << "First string: ";
 std::cin >> FirstString;
 std::cout << "Search string: ";
 std::cin >> SecondString;

  /* Check for second string occurrence */
 if ( false == strstr (FirstString, SecondString) )
 {
  std::cout << "Second string isn't part of the string!" << std::endl;
 }
 else
 {
  std::cout << "Second string is part of the string!" << std::endl;
 }

 return 0;
}