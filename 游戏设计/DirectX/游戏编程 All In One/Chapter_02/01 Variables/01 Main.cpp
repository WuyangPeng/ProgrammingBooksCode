 /* '01 Main.cpp' */
#include <iostream>

 /* Start of program */
main (void)
{
  /* Variable declarations*/
 unsigned char   Age; 
 long            StartEnergy;
 char            CharacterType;
  /* Get the Information */
 std::cout << "What is your character's age: ";
 std::cin >> Age;
 std::cout << "How much start energy: ";
 std::cin >> StartEnergy;
 std::cout << "What is the character type: ";
 std::cin >> CharacterType;

  /* Show the Information */
 std::cout << "You character is " << Age << " years old." << std::endl;
 std::cout << "Has " << StartEnergy << " of starting energy." << std::endl;
 std::cout << "And its type is " << CharacterType << "." << std::endl;
 return 0;
}
