// Fig. 24.11: Fig24_11.cpp
// Driver for multiple-inheritance example.
#include <iostream>
#include "Base1.h"
#include "Base2.h"
#include "Derived.h"
using namespace std;

int main()
{
   Base1 base1( 10 ), *base1Ptr = 0; // create Base1 object
   Base2 base2( 'Z' ), *base2Ptr = 0; // create Base2 object
   Derived derived( 7, 'A', 3.5 ); // create Derived object

   // print data members of base-class objects
   cout << "Object base1 contains integer " << base1.getData()
      << "\nObject base2 contains character " << base2.getData()
      << "\nObject derived contains:\n" << derived << "\n\n";

   // print data members of derived-class object
   // scope resolution operator resolves getData ambiguity
   cout << "Data members of Derived can be accessed individually:"
      << "\n    Integer: " << derived.Base1::getData()
      << "\n  Character: " << derived.Base2::getData()
      << "\nReal number: " << derived.getReal() << "\n\n";
   cout << "Derived can be treated as an object of either base class:\n";

   // treat Derived as a Base1 object
   base1Ptr = &derived;
   cout << "base1Ptr->getData() yields " << base1Ptr->getData() << '\n';

   // treat Derived as a Base2 object
   base2Ptr = &derived;
   cout << "base2Ptr->getData() yields " << base2Ptr->getData() << endl;
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
