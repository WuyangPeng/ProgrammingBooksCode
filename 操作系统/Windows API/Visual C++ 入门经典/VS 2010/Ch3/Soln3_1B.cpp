// Soln3_1B.cpp

/* Here the check for val being zero is at the end of the loop.
   You read val in the loop and add the value to total. If value 
   read into val was zero the loop ends.
*/

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int main()
{
   int val, total = 0;
   cout << "Enter numbers, one per line. Enter 0 to end:\n";

   do
   {
      cin >> val;
      total += val;
   } while (val != 0);

   cout << "\nThank you. The total was " << total;
   cout << endl;
   return 0;
}
