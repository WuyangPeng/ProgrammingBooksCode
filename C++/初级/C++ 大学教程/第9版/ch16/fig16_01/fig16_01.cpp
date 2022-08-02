// Fig. 16.1: fig16_01.cpp
// Algorithms fill, fill_n, generate and generate_n.
#include <iostream>
#include <algorithm> // algorithm definitions
#include <array> // array class-template definition
#include <iterator> // ostream_iterator
using namespace std;

char nextLetter(); // prototype of generator function 

int main()
{
   array< char, 10 > chars;
   ostream_iterator< char > output( cout, " " );
   fill( chars.begin(), chars.end(), '5' ); // fill chars with 5s 

   cout << "chars after filling with 5s:\n";
   copy( chars.cbegin(), chars.cend(), output );

   // fill first five elements of chars with As
   fill_n( chars.begin(), 5, 'A' );

   cout << "\n\nchars after filling five elements with As:\n";
   copy( chars.cbegin(), chars.cend(), output );

   // generate values for all elements of chars with nextLetter
   generate( chars.begin(), chars.end(), nextLetter );

   cout << "\n\nchars after generating letters A-J:\n";
   copy( chars.cbegin(), chars.cend(), output );

   // generate values for first five elements of chars with nextLetter
   generate_n( chars.begin(), 5, nextLetter );   

   cout << "\n\nchars after generating K-O for the"
      << " first five elements:\n";
   copy( chars.cbegin(), chars.cend(), output );
   cout << endl;
} // end main

// generator function returns next letter (starts with A)
char nextLetter()
{
   static char letter = 'A';
   return letter++;
} // end function nextLetter

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
