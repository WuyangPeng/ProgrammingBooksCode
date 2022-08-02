// Fig. 21.3: fig21_03.cpp
// Demonstrating string member function substr.
#include <iostream>
#include <string>
using namespace std;

int main()
{
   string string1( "The airplane landed on time." );

   // retrieve substring "plane" which
   // begins at subscript 7 and consists of 5 characters
   cout << string1.substr( 7, 5 ) << endl;
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

