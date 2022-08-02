// Fig. 7.8: fig07_08.cpp
// Compute the sum of the elements of an array.
#include <iostream>
#include <array>
using namespace std;

int main()
{
   const size_t arraySize = 4; // specifies size of array
   array< int, arraySize > a = { 10, 20, 30, 40 };
   int total = 0;

   // sum contents of array a
   for ( size_t i = 0; i < a.size(); ++i )
      total += a[ i ];
   
   cout << "Total of array elements: " << total << endl;
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
