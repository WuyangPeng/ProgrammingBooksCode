// Fig. 13.11: Fig13_11.cpp 
// Controlling the printing of trailing zeros and  
// decimal points in floating-point values.
#include <iostream>
using namespace std;

int main() {
   // display double values with default stream format
   cout << "Before using showpoint"
      << "\n9.9900 prints as: " << 9.9900
      << "\n9.9000 prints as: " << 9.9000
      << "\n9.0000 prints as: " << 9.0000;

   // display double value after showpoint
   cout << showpoint
      << "\n\nAfter using showpoint"
      << "\n9.9900 prints as: " << 9.9900
      << "\n9.9000 prints as: " << 9.9000
      << "\n9.0000 prints as: " << 9.0000 << endl;
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
 **************************************************************************/
