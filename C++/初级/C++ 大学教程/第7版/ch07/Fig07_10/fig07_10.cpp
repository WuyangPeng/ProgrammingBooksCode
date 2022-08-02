// Fig. 7.10: fig07_10.cpp
// Roll a six-sided die 6,000,000 times.
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
using namespace std;

int main()
{
   const int arraySize = 7; // ignore element zero
   int frequency[ arraySize ] = {}; // initialize elements to 0

   srand( time( 0 ) ); // seed random number generator

   // roll die 6,000,000 times; use die value as frequency index
   for ( int roll = 1; roll <= 6000000; roll++ )       
      frequency[ 1 + rand() % 6 ]++;

   cout << "Face" << setw( 13 ) << "Frequency" << endl;

   // output each array element's value
   for ( int face = 1; face < arraySize; face++ )  
      cout << setw( 4 ) << face << setw( 13 ) << frequency[ face ] 
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
