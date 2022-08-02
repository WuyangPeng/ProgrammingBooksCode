 /* '10 Main.cpp' */

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
 std::cout << "Second string: ";
 std::cin >> SecondString;

  /* Compare the two strings */
 if ( false == strcmp (FirstString, SecondString) )
 {
  std::cout << "Strings match!" << std::endl;
 }
 else
 {
  std::cout << "Strings don't match!" << std::endl;
 }

 return 0;
}