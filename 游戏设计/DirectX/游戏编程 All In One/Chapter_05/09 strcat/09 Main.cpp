 /* '09 Main.cpp' */

 /* Input output stream header file */
#include <iostream>

 /* Start */
main (void)
{
  /* Declare three strings */
 char FirstString [255];
 char SecondString [255];
 char FinalString [255];

  /* Get two strings from the user */
 std::cout << "First string: ";
 std::cin >> FirstString;
 std::cout << "Second string: ";
 std::cin >> SecondString;

  /* Concatenate two strings */
 strcpy (FinalString, FirstString);
 strcat (FinalString, SecondString);

  /* Output final strings */
 std::cout << "Final string: " << FinalString << std::endl;

 return 0;
}