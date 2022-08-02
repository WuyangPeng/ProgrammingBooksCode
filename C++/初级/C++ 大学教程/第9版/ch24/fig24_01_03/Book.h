// Fig. 24.1: Book.h
// Declaration of class Book.
#ifndef BOOK_H
#define BOOK_H

#include <string>
using namespace std;

class Book
{
public:
   explicit Book( const string &bookTitle ); // constructor
   ~Book(); // destructor
   string title; // title of the Book
};
#endif // BOOK_H

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
