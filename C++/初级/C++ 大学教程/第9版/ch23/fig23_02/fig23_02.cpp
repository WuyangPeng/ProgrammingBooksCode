// Fig. 23.2: fig23_02.cpp
// Demonstrating storage-class specifier mutable.
#include <iostream>
using namespace std;

// class TestMutable definition
class TestMutable
{
public:
   TestMutable( int v = 0 )
   {
      value = v;
   } // end TestMutable constructor

   int getValue() const
   {
      return value++; // increments value
   } // end function getValue
private:
   mutable int value; // mutable member
}; // end class TestMutable

int main()
{
   const TestMutable test( 99 );

   cout << "Initial value: " << test.getValue();
   cout << "\nModified value: " << test.getValue() << endl;
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
