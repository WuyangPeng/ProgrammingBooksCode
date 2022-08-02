// Soln3_1C.cpp
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int main()
{
   int val, total = 0;
   cout << "Enter numbers, one per line. Enter 0 to end:\n";
   cin >> val;

   // We don't need the initialization or increment expressions
   for (; val!=0 ;)
   {
      total += val;
      cin >> val;
   }

   cout << "\nThank you. The total was " << total;
   cout << endl;

   return 0;
}
