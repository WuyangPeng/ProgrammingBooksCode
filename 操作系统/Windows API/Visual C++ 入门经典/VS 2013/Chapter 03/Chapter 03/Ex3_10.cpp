// Ex3_10.cpp
// Using an indefinite for loop to compute an average
#include <iostream>
        
using std::cin;
using std::cout;
using std::endl;
        
int main()
{
  double value {};                  // Value entered stored here
  double sum {};                    // Total of values accumulated here
  int i {};                         // Count of number of values
  char indicator { 'n' };           // Continue or not?
        
   for(;;)                          // Indefinite loop
   {
      cout << endl
           << "Enter a value: ";
      cin >> value;                 // Read a value
      ++i;                          // Increment count
      sum += value;                 // Add current input to total
        
      cout << endl
           << "Do you want to enter another value (enter y or n)? ";
      cin >> indicator;             // Read indicator
      if (('n' == indicator) || ('N' == indicator))
         break;                     // Exit from loop
   }
        
   cout << endl
        << "The average of the " << i
        << " values you entered is " << sum/i << "."
        << endl;
   return 0;
}
