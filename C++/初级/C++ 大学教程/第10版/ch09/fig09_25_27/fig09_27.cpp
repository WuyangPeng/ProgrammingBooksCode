// Fig. 9.27: fig09_27.cpp
// Cascading member-function calls with the this pointer.
#include <iostream>
#include "Time.h" // Time class definition
using namespace std;

int main() {
   Time t; // create Time object

   t.setHour(18).setMinute(30).setSecond(22); // cascaded function calls

   // output time in universal and standard formats
   cout << "Universal time: " << t.toUniversalString()
      << "\nStandard time: " << t.toStandardString();

   // cascaded function calls        
   cout << "\n\nNew standard time: "
      << t.setTime(20, 20, 20).toStandardString() << endl;
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
