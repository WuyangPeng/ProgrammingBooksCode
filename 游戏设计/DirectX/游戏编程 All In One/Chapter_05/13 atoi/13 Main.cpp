 /* '13 Main.cpp' */

 /* Input output stream header file */
#include <iostream>

 /* Start */
main (void)
{
  /* Declare a string and an int */
 char String [255];
 int Number;

  /* Get a string from the user */
 std::cout << "Enter a string: ";
 std::cin >> String;

  /* Convert string to integer */
 Number = atoi (String);

  /* To prove it is an int, calculate square of number */
 std::cout << "Square of Number is " << Number * Number << std::endl;

 return 0;
}