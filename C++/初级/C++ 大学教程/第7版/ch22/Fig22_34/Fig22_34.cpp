// Fig. 22.34: Fig22_34.cpp
// Standard Library algorithms inplace_merge,
// reverse_copy and unique_copy.
#include <iostream>
#include <algorithm> // algorithm definitions
#include <vector> // vector class-template definition
#include <iterator> // back_inserter definition
using namespace std;

int main()
{
   const int SIZE = 10;
   int a1[ SIZE ] = { 1, 3, 5, 7, 9, 1, 3, 5, 7, 9 };
   vector< int > v1( a1, a1 + SIZE ); // copy of a
   ostream_iterator< int > output( cout, " " );

   cout << "Vector v1 contains: ";
   copy( v1.begin(), v1.end(), output );

   // merge first half of v1 with second half of v1 such that 
   // v1 contains sorted set of elements after merge
   inplace_merge( v1.begin(), v1.begin() + 5, v1.end() );

   cout << "\nAfter inplace_merge, v1 contains: ";
   copy( v1.begin(), v1.end(), output );
   
   vector< int > results1;

   // copy only unique elements of v1 into results1
   unique_copy( v1.begin(), v1.end(), back_inserter( results1 ) );
   cout << "\nAfter unique_copy results1 contains: ";
   copy( results1.begin(), results1.end(), output );
   
   vector< int > results2;
   
   // copy elements of v1 into results2 in reverse order
   reverse_copy( v1.begin(), v1.end(), back_inserter( results2 ) );
   cout << "\nAfter reverse_copy, results2 contains: ";
   copy( results2.begin(), results2.end(), output );
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
