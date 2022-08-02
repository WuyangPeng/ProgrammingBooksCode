// BalanceInquiry.cpp
// Member-function definitions for class BalanceInquiry.
#include "BalanceInquiry.h" // BalanceInquiry class definition
#include "Screen.h" // Screen class definition
#include "BankDatabase.h" // BankDatabase class definition

// BalanceInquiry constructor initializes base-class data members
BalanceInquiry:: BalanceInquiry( int userAccountNumber, Screen &atmScreen, 
   BankDatabase &atmBankDatabase )
   : Transaction( userAccountNumber, atmScreen, atmBankDatabase )
{
   // empty body
} // end BalanceInquiry constructor

// performs transaction; overrides Transaction's pure virtual function
void BalanceInquiry::execute()
{
   // get references to bank database and screen
   BankDatabase &bankDatabase = getBankDatabase();
   Screen &screen = getScreen();

   // get the available balance for the current user's Account
   double availableBalance = 
      bankDatabase.getAvailableBalance( getAccountNumber() );

   // get the total balance for the current user's Account
   double totalBalance = 
      bankDatabase.getTotalBalance( getAccountNumber() );
   
   // display the balance information on the screen
   screen.displayMessageLine( "\nBalance Information:" );
   screen.displayMessage( " - Available balance: " ); 
   screen.displayDollarAmount( availableBalance );
   screen.displayMessage( "\n - Total balance:     " );
   screen.displayDollarAmount( totalBalance );
   screen.displayMessageLine( "" );
} // end function execute


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
