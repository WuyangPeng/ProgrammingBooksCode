// Fig. 22.21: Fig22_21.cpp
// Standard Library class multimap test program.
#include <iostream>
#include <map> // multimap class-template definition
using namespace std;

// define short name for multimap type used in this program
typedef multimap< int, double, less< int > > Mmid;

int main()
{
   Mmid pairs; // declare the multimap pairs

   cout << "There are currently " << pairs.count( 15 )
      << " pairs with key 15 in the multimap\n";

   // insert two value_type objects in pairs
   pairs.insert( Mmid::value_type( 15, 2.7 ) );
   pairs.insert( Mmid::value_type( 15, 99.3 ) );
   
   cout << "After inserts, there are " << pairs.count( 15 )
      << " pairs with key 15\n\n";
   
   // insert five value_type objects in pairs
   pairs.insert( Mmid::value_type( 30, 111.11 ) );
   pairs.insert( Mmid::value_type( 10, 22.22 ) );
   pairs.insert( Mmid::value_type( 25, 33.333 ) );
   pairs.insert( Mmid::value_type( 20, 9.345 ) );
   pairs.insert( Mmid::value_type( 5, 77.54 ) );
   
   cout << "Multimap pairs contains:\nKey\tValue\n";
   
   // use const_iterator to walk through elements of pairs
   for ( Mmid::const_iterator iter = pairs.begin();
      iter != pairs.end(); ++iter )
      cout << iter->first << '\t' << iter->second << '\n';

   cout << endl;
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
