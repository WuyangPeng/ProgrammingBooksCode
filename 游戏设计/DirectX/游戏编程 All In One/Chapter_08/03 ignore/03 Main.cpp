 /* '02 Main.cpp' */

 /* Input Output stream header file */
#include <iostream>

 /* Start */
main (void)
{
 int TypedLetter;

  /* Ignore first two letters */
 std::cin.ignore (2);
 TypedLetter = std::cin.get ();

 std::cout << TypedLetter;

 return 0;
}