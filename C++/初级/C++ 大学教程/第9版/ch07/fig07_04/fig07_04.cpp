// Fig. 7.4: fig07_04.cpp
// Initializing an array in a declaration.
#include <iostream>
#include <iomanip>
#include <array>
using namespace std;

int main()
{
   // use list initializer to initialize array n
   array< int, 5 > n = { 32, 27, 64, 18, 95 };
   
   cout << "Element" << setw( 13 ) << "Value" << endl;

   // output each array element's value
   for ( size_t i = 0; i < n.size(); ++i )
      cout << setw( 7 ) << i << setw( 13 ) << n[ i ] << endl;
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
