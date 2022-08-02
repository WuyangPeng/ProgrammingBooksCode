// Fig. 22.29: Fig22_29.cpp
// Standard Library functions replace, replace_if,
// replace_copy and replace_copy_if.
#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator> // ostream_iterator
using namespace std;

bool greater9( int ); // predicate function prototype

int main()
{ 
   const int SIZE = 10;
   int a[ SIZE ] = { 10, 2, 10, 4, 16, 6, 14, 8, 12, 10 };
   ostream_iterator< int > output( cout, " " );

   vector< int > v1( a, a + SIZE ); // copy of a
   cout << "Vector v1 before replacing all 10s:\n   ";
   copy( v1.begin(), v1.end(), output );

   // replace all 10s in v1 with 100
   replace( v1.begin(), v1.end(), 10, 100 );
   cout << "\nVector v1 after replacing 10s with 100s:\n   ";
   copy( v1.begin(), v1.end(), output );

   vector< int > v2( a, a + SIZE ); // copy of a
   vector< int > c1( SIZE ); // instantiate vector c1
   cout << "\n\nVector v2 before replacing all 10s and copying:\n   ";
   copy( v2.begin(), v2.end(), output );

   // copy from v2 to c1, replacing 10s with 100s
   replace_copy( v2.begin(), v2.end(), c1.begin(), 10, 100 );
   cout << "\nVector c1 after replacing all 10s in v2:\n   ";
   copy( c1.begin(), c1.end(), output );

   vector< int > v3( a, a + SIZE ); // copy of a
   cout << "\n\nVector v3 before replacing values greater than 9:\n   ";
   copy( v3.begin(), v3.end(), output );

   // replace values greater than 9 in v3 with 100
   replace_if( v3.begin(), v3.end(), greater9, 100 );
   cout << "\nVector v3 after replacing all values greater"
      << "\nthan 9 with 100s:\n   ";
   copy( v3.begin(), v3.end(), output );

   vector< int > v4( a, a + SIZE ); // copy of a
   vector< int > c2( SIZE ); // instantiate vector c2
   cout << "\n\nVector v4 before replacing all values greater "
        << "than 9 and copying:\n   ";
   copy( v4.begin(), v4.end(), output );

   // copy v4 to c2, replacing elements greater than 9 with 100
   replace_copy_if( v4.begin(), v4.end(), c2.begin(), greater9, 100 );
   cout << "\nVector c2 after replacing all values greater "
      << "than 9 in v4:\n   ";
   copy( c2.begin(), c2.end(), output );
   cout << endl;
} // end main

// determine whether argument is greater than 9
bool greater9( int x )
{
   return x > 9;
} // end function greater9

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
