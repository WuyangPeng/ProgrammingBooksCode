// Fig. 13.17: Fig13_17.cpp 
// Stream manipulator uppercase.
#include <iostream>
using namespace std;

int main() {
   cout << "Printing uppercase letters in scientific\n"
      << "notation exponents and hexadecimal values:\n";

   // use std::uppercase to display uppercase letters; use std::hex and 
   // std::showbase to display hexadecimal value and its base
   cout << uppercase << 4.345e10 << "\n"
      << hex << showbase << 123456789 << endl;
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
