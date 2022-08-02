// Soln2_1.cpp
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int main()
{
   int number;                             // Local integer variable

   cout << "Enter a number: ";             // Prompt for input
   cin >> number;                          // Read a number from the standard input stream

   // Output the number to the standard output stream
   cout << "Thank you. Your number was "
        << number;
   cout << endl;                           // Write a newline to the standard output stream

   return 0;
}
