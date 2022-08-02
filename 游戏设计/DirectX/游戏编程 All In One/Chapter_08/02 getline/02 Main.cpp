 /* '02 Main.cpp' */

 /* Input Output stream header file */
#include <iostream>

 /* Start */
main (void)
{
 char TypedString [256];

 std::cout << "Type any text: ";

  /* Get a string from the user */
 std::cin.getline (TypedString, 256);

 std::cout << "You typed: " << TypedString;

 return 0;
}