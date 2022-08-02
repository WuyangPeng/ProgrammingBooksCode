// Fig. 3.5: AccountTest.cpp
// Using the Account constructor to initialize the name data
// member at the time each Account object is created.
#include <iostream>
#include "Account.h"

using namespace std;

int main() { 
   // create two Account objects
   Account account1{"Jane Green"};
   Account account2{"John Blue"}; 

   // display initial value of name for each Account
   cout << "account1 name is: " << account1.getName() << endl;
   cout << "account2 name is: " << account2.getName() << endl;
} 

/**************************************************************************
 * (C) Copyright 1992-2017 by Deitel & Associates, Inc. and               *
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
