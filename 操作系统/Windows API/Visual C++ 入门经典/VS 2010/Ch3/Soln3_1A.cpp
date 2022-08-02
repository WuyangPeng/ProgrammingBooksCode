// Soln3_1A.cpp
/* Note that val is not initialized in the code and so will contain a spurious value 
   at the beginning. That's why you read the first value for val before the loop.
   If you initialize val to 1 then you can do all the input inside the loop:

      int val = 1, total = 0;
   cout << "Enter numbers, one per line. Enter 0 to end:\n";

   while (val != 0)
   {
     cin >> val;
     total += val;
   }

   Now you read val in the loop before adding the value to total.
*/

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int main()
{
   int val, total = 0;
   cout << "Enter numbers, one per line. Enter 0 to end:\n";
   cin >> val;

   while (val != 0)
   {
     total += val;
     cin >> val;
   }

   cout << "\nThank you. The total was " << total;
   cout << endl;
   return 0;
}
