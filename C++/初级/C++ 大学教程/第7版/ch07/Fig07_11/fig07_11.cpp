// Fig. 7.11: fig07_11.cpp
// Poll analysis program.
#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
   // define array sizes
   const int responseSize = 40; // size of array responses
   const int frequencySize = 11; // size of array frequency

   // place survey responses in array responses
   const int responses[ responseSize ] = { 1, 2, 6, 4, 8, 5, 9, 7, 8,
      10, 1, 6, 3, 8, 6, 10, 3, 8, 2, 7, 6, 5, 7, 6, 8, 6, 7,
      5, 6, 6, 5, 6, 7, 5, 6, 4, 8, 6, 8, 10 };

   // initialize frequency counters to 0
   int frequency[ frequencySize ] = {};

   // for each answer, select responses element and use that value 
   // as frequency subscript to determine element to increment
   for ( int answer = 0; answer < responseSize; answer++ )
      frequency[ responses[ answer ] ]++;

   cout << "Rating" << setw( 17 ) << "Frequency" << endl;

   // output each array element's value
   for ( int rating = 1; rating < frequencySize; rating++ )
      cout << setw( 6 ) << rating << setw( 17 ) << frequency[ rating ] 
         << endl;
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
