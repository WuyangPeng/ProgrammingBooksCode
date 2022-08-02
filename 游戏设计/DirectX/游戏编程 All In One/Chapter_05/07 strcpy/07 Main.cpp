 /* '07 Main.cpp' */

 /* Input output stream header file */
#include <iostream>

 /* Start */
main (void)
{
  /* Declare a string */
 char String [255];
 char Test [255];

  /* Get a string from the user and copy it to String */
 std::cout << "Type any string: ";
 std::cin >> Test;

 strcpy (String, Test);

  /* Output both strings */
 std::cout << "Test string: " << Test << std::endl;
 std::cout << "Input string: " << String << std::endl;

 return 0;
}