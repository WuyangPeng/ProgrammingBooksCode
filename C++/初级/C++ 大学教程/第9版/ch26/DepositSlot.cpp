// DepositSlot.cpp
// Member-function definition for class DepositSlot.
#include "DepositSlot.h" // DepositSlot class definiton

// indicates whether envelope was received (always returns true, 
// because this is only a software simulation of a real deposit slot)
bool DepositSlot::isEnvelopeReceived() const
{
   return true; // deposit envelope was received
} // end function isEnvelopeReceived


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
