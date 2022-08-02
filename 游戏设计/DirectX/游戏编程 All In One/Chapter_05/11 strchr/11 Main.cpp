 /* '11 Main.cpp' */

 /* Input output stream header file */
#include <iostream>

 /* Start */
main (void)
{
  /* Declare a string */
 char String [255];
 char Character;

  /* Get a strings and a character from the user */
 std::cout << "String: ";
 std::cin >> String;
 std::cout << "Character: ";
 std::cin >> Character;

  /* Check to see if character exists on the strings */
 if ( 0 == strchr (String, Character) )
 {
  std::cout << "Character isn't part of the string!" << std::endl;
 }
 else
 {
  std::cout << "Character is part of the string!" << std::endl;
 }

 return 0;
}