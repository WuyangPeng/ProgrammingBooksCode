 /* '10 Main.cpp' */

 /* Input output stream header*/
#include <iostream>

main (void)
{
 short Number;

 for (Number = 1; Number <= 20; Number ++)
 {
  std::cout << "The square of " << Number << " is: ";
  std::cout << Number * Number << std::endl;
 }

 return 0;
}
