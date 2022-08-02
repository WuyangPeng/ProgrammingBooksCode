// Fig. F.7: figF_07.cpp
// Using goto.
#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
   int count = 1;

   start: // label 
      // goto end when count exceeds 10
      if ( count > 10 )
         goto end;

      cout << setw( 2 ) << left << count;
      ++count;

      // goto start on line 17
      goto start;             

   end: // label
      cout << endl;
}  // end main

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
