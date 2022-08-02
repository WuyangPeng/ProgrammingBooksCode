// Fig. 9.16: fig09_16.cpp
// const objects and const member functions.
#include "Time.h" // include Time class definition

int main()
{
   Time wakeUp( 6, 45, 0 ); // non-constant object
   const Time noon( 12, 0, 0 ); // constant object

                          // OBJECT      MEMBER FUNCTION
   wakeUp.setHour( 18 );  // non-const   non-const
   
   noon.setHour( 12 );    // const       non-const
   
   wakeUp.getHour();      // non-const   const
   
   noon.getMinute();      // const       const
   noon.printUniversal(); // const       const
   
   noon.printStandard();  // const       non-const
} // end main

/**************************************************************************
 * (C) Copyright 1992-2012 by Deitel & Associates, Inc. and               *
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
