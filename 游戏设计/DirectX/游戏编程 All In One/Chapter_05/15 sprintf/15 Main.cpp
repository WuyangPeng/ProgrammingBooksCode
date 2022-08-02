 /* '15 Main.cpp' */

 /* Input output stream header file */
#include <iostream>

 /* Start */
main (void)
{
  /* Declare a string */
 char FinalString [255];

  /* Declare user's information variables */
 char Name [255];
 int Age;
 float Height;
 float Weight;

  /* Get all information from the user */
 std::cout << "What your first name : ";
 std::cin >> Name;
 std::cout << "What is your age : ";
 std::cin >> Age;
 std::cout << "What is your height : ";
 std::cin >> Height;
 std::cout << "What is your weight : ";
 std::cin >> Weight;

  /* Convert information to a single string */
 sprintf (FinalString, "Your first name is %s. You are %d years old\
and you height %f and weight %f.", Name, Age, Height, Weight);

  /* Output final string */
 std::cout << FinalString << std::endl;

 return 0;
}