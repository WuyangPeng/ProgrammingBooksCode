// Exercise 4.5: Calculate.cpp
// Calculate the sum of the integers from 1 to 10 
#include <iostream>
using namespace std;

int main() {
   unsigned int sum{0};
   unsigned int x{1};

   while (x <= 10) { // while x is less than or equal to 10
      sum += x; // add x to sum
      ++x; // increment x
   } 

   cout << "The sum is: " << sum << endl;
} 



/**************************************************************************
 * (C) Copyright 1992-2017 by Deitel & Associates, Inc. and               *
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
 *************************************************************************/
