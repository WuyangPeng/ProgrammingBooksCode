// Exercise 4.8 Solution: ex04_08.cpp
// Raise x to the y power. 
#include <iostream>
using namespace std;

int main()
{
   unsigned int i = 1; // initialize i to begin counting from 1
   unsigned int power = 1; // initialize power

   cout << "Enter base as an integer: ";  // prompt for base
   unsigned int x; // base 
   cin >> x; // input base

   cout << "Enter exponent as an integer: "; // prompt for exponent
   unsigned int y; // exponent
   cin >> y; // input exponent

   // count from 1 to y and multiply power by x each time
   while ( i <= y ) 
   {
      power *= x;
      ++i;
   } // end while

   cout << power << endl; // display result
} // end main



/**************************************************************************
 * (C) Copyright 1992-2014 by Deitel & Associates, Inc. and               *
 * Pearson Education, Inc. All Rights Reserved.                           *
 *                                                                        *
 * DISCLAIMER: The authors and publisher of this book have used their     *
 * best efforts in preparing the book. These efforts include the          *
 * development, research, and testing of the theories and programs        *
 * to determine their effectiveness. The authors and publisher make       *
 * no warranty of any kind, expressed or implied, with regard to these    *
 * programs or to the documentation contained in these books. The authors *
 * and publisher shall not be liable in any event for incidental or       *
 * consequential damages in connection with, or arising out of, the       *
 * furnishing, performance, or use of these programs.                     *
 **************************************************************************/
