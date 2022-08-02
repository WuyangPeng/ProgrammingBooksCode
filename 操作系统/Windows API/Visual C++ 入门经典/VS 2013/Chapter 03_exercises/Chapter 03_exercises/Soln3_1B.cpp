// Soln3_1B.cpp

/* Here the check for val being zero is at the end of the loop.
   You read val in the loop and add the value to total. If value 
   read into val was zero the loop ends.
*/

#include <iostream>

int main()
{
  int val{}, total{};
   std::cout << "Enter numbers, one per line. Enter 0 to end:\n";

   do
   {
      std::cin >> val;
      total += val;
   } while (val != 0);

   std::cout << "\nThank you. The total was " << total << std::endl;

   return 0;
}
