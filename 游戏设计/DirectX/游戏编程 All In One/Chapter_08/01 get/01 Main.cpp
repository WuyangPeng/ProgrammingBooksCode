 /* '01 Main.cpp' */

 /* Input Output stream header file */
#include <iostream>

 /* Start */
main (void)
{
 int TypedLetter;

 std::cout << "Press q to quit...";

  /* Wait until user pressed 'q' or 'Q' */
 TypedLetter = std::cin.get ();
 while ((TypedLetter != 'q') || (TypedLetter != 'Q'))
 {
  TypedLetter = std::cin.get ();
 }

 return 0;
}