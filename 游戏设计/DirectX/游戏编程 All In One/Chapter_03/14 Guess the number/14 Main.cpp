 /* '134 Main.cpp' */

 /* Input output stream header*/
#include <iostream>
 /* Standard library header*/
#include <stdlib.h>

main ()
{
 short Number;
 short Guess = 0;

  /* Get random number and add one to prevent it from being zero */
 Number = rand () % 100;
 Number++;

  /* Until player finds the number continue to loop */
 while (Guess != Number)
 {
  std::cout << "Enter a number between 1 and 100: "; 
  std::cin >> Guess;

   /* If guess is higher, give hint */
  if (Guess < Number)
  {
   std::cout << "You are guessing low.";
   std::cout << std::endl;
  }
   /* If guess is lower, give hint */
  if (Guess > Number)
  {
   std::cout << "You are guessing high.";
   std::cout << std::endl;
  }
 }

  /* Show win message */
 std::cout << "You got it bud, the winning number is: " << Number;
 std::cout << std::endl;

 return 0;
}
