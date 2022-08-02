// Fig. H.2: Account.cpp
// Member-function definitions for class Account.
#include <iostream>
#include "Account.h" // include definition of class Account
using namespace std;

// Account constructor initializes data member balance
Account::Account(int initialBalance) {
   // if initialBalance is greater than 0, set this value as the
   // balance of the Account; otherwise, balance remains 0
   if (initialBalance > 0) {
      balance = initialBalance;
   }

   // if initialBalance is negative, print error message
   if (initialBalance < 0) {
      cout << "Error: Initial balance cannot be negative.\n" << endl;
   }
} 

// deposit (add) an amount to the account balance
void Account::deposit(int amount) {
   balance = balance + amount; // add amount to balance
}

// withdraw (subtract) an amount from the account balance
void Account::withdraw(int amount) {
   if (amount <= balance) { // withdrawal amount OK
      balance = balance - amount;
   }
   else { // withdraw amount exceeds balance
      cout << "Withdrawal amount exceeded balance.\n" << endl;
   }
} 

// return the account balance
int Account::getBalance() {
   return balance; // gives the value of balance to the calling function
} 

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
