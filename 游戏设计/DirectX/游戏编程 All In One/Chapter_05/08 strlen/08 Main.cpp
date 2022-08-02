 /* '08 Main.cpp' */

 /* Input output stream header file */
#include <iostream>

 /* Start */
main (void)
{
  /* Declare a string and a pointer to a char */
 char Test [255];
 char * String;

  /* Get a string from the user */
 std::cout << "Type any string: ";
 std::cin >> Test;

  /* Use length of string to allocate the new string */
 String = new char [strlen (Test) + 1];
 strcpy (String, Test);

  /* Output both strings */
 std::cout << "Test string: " << Test << std::endl;
 std::cout << "Input string: " << String << std::endl;
 std::cout << "String length: " << strlen (Test) << std::endl;

 delete [] String;

 return 0;
}