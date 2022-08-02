// Fig. 22.19: Fig22_19.cpp
// Testing Standard Library class multiset
#include <iostream>
#include <set> // multiset class-template definition
#include <algorithm> // copy algorithm
#include <iterator> // ostream_iterator
using namespace std;

// define short name for multiset type used in this program
typedef multiset< int, less< int > > Ims;

int main()
{
   const int SIZE = 10;
   int a[ SIZE ] = { 7, 22, 9, 1, 18, 30, 100, 22, 85, 13 };
   Ims intMultiset; // Ims is typedef for "integer multiset"
   ostream_iterator< int > output( cout, " " );

   cout << "There are currently " << intMultiset.count( 15 )
      << " values of 15 in the multiset\n";
   
   intMultiset.insert( 15 ); // insert 15 in intMultiset
   intMultiset.insert( 15 ); // insert 15 in intMultiset
   cout << "After inserts, there are " << intMultiset.count( 15 )
      << " values of 15 in the multiset\n\n";

   // iterator that cannot be used to change element values
   Ims::const_iterator result;  

   // find 15 in intMultiset; find returns iterator
   result = intMultiset.find( 15 );  

   if ( result != intMultiset.end() ) // if iterator not at end
      cout << "Found value 15\n"; // found search value 15
   
   // find 20 in intMultiset; find returns iterator
   result = intMultiset.find( 20 );

   if ( result == intMultiset.end() ) // will be true hence
      cout << "Did not find value 20\n"; // did not find 20

   // insert elements of array a into intMultiset
   intMultiset.insert( a, a + SIZE ); 
   cout << "\nAfter insert, intMultiset contains:\n";
   copy( intMultiset.begin(), intMultiset.end(), output );

   // determine lower and upper bound of 22 in intMultiset
   cout << "\n\nLower bound of 22: " 
      << *( intMultiset.lower_bound( 22 ) );
   cout << "\nUpper bound of 22: " << *( intMultiset.upper_bound( 22 ) );

   // p represents pair of const_iterators 
   pair< Ims::const_iterator, Ims::const_iterator > p;

   // use equal_range to determine lower and upper bound 
   // of 22 in intMultiset
   p = intMultiset.equal_range( 22 );

   cout << "\n\nequal_range of 22:" << "\n   Lower bound: " 
      << *( p.first ) << "\n   Upper bound: " << *( p.second );
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
