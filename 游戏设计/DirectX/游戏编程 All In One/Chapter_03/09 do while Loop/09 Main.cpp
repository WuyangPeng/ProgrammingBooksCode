 /* '09 Main.cpp' */

 /* Input output stream header*/
#include <iostream>

main ()
{
 short Action = 0;

 do 
 {
  std::cout << "1 - Do exactly nothing.";
  std::cout << std::endl;
  std::cout << "2 - Try to do nothing.";
  std::cout << std::endl;
  std::cout << "3 - Exit.";
  std::cout << std::endl;
  std::cin >> Action;
 }
 while (Action != 3);

 return 0;
}
