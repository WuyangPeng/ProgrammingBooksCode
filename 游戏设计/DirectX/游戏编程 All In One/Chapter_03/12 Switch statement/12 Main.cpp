 /* '12 Main.cpp' */

 /* Input output stream header*/
#include <iostream>

void ShowHelp (void);

main ()
{
 short Action;
  /* Ask the user what he wants to do */
 std::cout << "What do you want to do: ";

 std::cin >> Action;

  /* Check to see what the player wanted to do */
 switch (Action)
 {
 case 1:
  std::cout << "You have chosen to run away.";
  std::cout << std::endl;
  break;

 case 2:
  std::cout << "You have chosen to fight.";
  std::cout << std::endl;
  break;

 case 3:
  std::cout << "You did wrong, you die!";
  std::cout << std::endl;
  break;

 default:
  ShowHelp ();
  break;
 }

 return 0;
}

void ShowHelp (void)
{
  /* Show the help commands */
 std::cout << std::endl;
 std::cout << "1 - Run";
 std::cout << std::endl;
 std::cout << "2 - Fight";
 std::cout << std::endl;
 std::cout << "3 - Surprise action";
 std::cout << std::endl;
 std::cout << "4 - Shows this help screen";
 std::cout << std::endl;
}
