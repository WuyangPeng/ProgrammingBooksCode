// Fig. 9.13: Date.h
// Date class declaration. Member functions are defined in Date.cpp.

// prevent multiple inclusions of header 
#ifndef DATE_H
#define DATE_H

// class Date definition
class Date 
{
public:
   explicit Date( int = 1, int = 1, int = 2000 ); // default constructor
   void print();
private:
   unsigned int month;
   unsigned int day;
   unsigned int year;
}; // end class Date

#endif

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
