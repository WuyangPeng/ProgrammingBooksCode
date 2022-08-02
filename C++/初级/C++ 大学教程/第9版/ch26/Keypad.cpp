// Keypad.cpp
// Member-function definition for class Keypad (the ATM's keypad).
#include <iostream>
#include "Keypad.h" // Keypad class definition
using namespace std;

// return an integer value entered by user
int Keypad::getInput() const
{
   int input; // variable to store the input
   cin >> input; // we assume that user enters an integer
   return input; // return the value entered by user
} // end function getInput


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
