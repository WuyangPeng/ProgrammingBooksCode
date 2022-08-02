// Fig. 23.15: fig23_15.cpp
// Example of lambda expressions in C++0x.
#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
   const int size = 4; // size of array values
   int values[ size ] = { 1, 2, 3, 4 }; // initialize values

   // output each element multiplied by two
   for_each( values, values + size,
      []( int i ) { cout << i * 2 << endl; } );

   int sum = 0; // initialize sum to zero

   // add each element to sum
   for_each( values, values + size,
      [ &sum ]( int i ) { sum += i; } );

   cout << "sum is " << sum << endl; // output sum
} // end main


/**************************************************************************
 * (C) Copyright 1992-2010 by Deitel & Associates, Inc. and               *
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
