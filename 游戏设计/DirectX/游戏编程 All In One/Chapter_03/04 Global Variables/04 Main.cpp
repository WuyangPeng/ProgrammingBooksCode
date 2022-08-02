 /* '04 Main.cpp' */

 /* Input output stream header*/
#include <iostream>

short NumberOfPlayers;
long Energy;

main ()
{
 std::cout << "Before the variables are used" << std::endl;
 std::cout << "Number of players: " << NumberOfPlayers << std::endl;
 std::cout << "Energy: " << Energy << std::endl;
 std::cout << std::endl;
  
 NumberOfPlayers = 10;
 Energy = 438534;
  
 std::cout << "After the variables are used" << std::endl;
 std::cout << "Number of players: " << NumberOfPlayers << std::endl;
 std::cout << "Energy: " << Energy << std::endl;

 return 0;
}
