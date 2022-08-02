// Soln3_1A.cpp
/* Note that val is not initialized in the code and so will contain a spurious value 
   at the beginning. That's why you read the first value for val before the loop.
   If you initialize val to 1 then you can do all the input inside the loop:

   int val {1}, total {};
   std::cout << "Enter numbers, one per line. Enter 0 to end:\n";

   while (val != 0)
   {
     std::cin >> val;
     total += val;
   }

   Now you read val in the loop before adding the value to total.
   It is better to initialize your variables when you define them.
*/

#include <iostream>

int main()
{
  int val, total{};
   std::cout << "Enter numbers, one per line. Enter 0 to end:\n";
   std::cin >> val;

   while (val != 0)
   {
     total += val;
     std::cin >> val;
   }

   std::cout << "\nThank you. The total was " << total << std::endl;

   return 0;
}
