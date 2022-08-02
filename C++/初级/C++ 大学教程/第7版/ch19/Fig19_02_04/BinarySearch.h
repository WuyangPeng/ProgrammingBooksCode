// Fig 19.2: BinarySearch.h
// Class that contains a vector of random integers and a function 
// that uses binary search to find an integer.
#include <vector>
using namespace std;

class BinarySearch
{
public:
   BinarySearch( int ); // constructor initializes vector
   int binarySearch( int ) const; // perform a binary search on vector
   void displayElements() const; // display vector elements
private:
   int size; // vector size
   vector< int > data; // vector of ints
   void displaySubElements( int, int ) const; // display range of values
}; // end class BinarySearch


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
 *************************************************************************/
