// Fig. 14.12: fig14_12.cpp
// Writing to a random-access file.
#include <iostream>
#include <fstream> 
#include <cstdlib> // exit function prototype
#include "ClientData.h" // ClientData class definition
using namespace std;

int main()
{
   int accountNumber;
   string lastName;
   string firstName;
   double balance;

   fstream outCredit( "credit.dat", ios::in | ios::out | ios::binary );

   // exit program if fstream cannot open file
   if ( !outCredit ) 
   {
      cerr << "File could not be opened." << endl;
      exit( EXIT_FAILURE );
   } // end if

   cout << "Enter account number (1 to 100, 0 to end input)\n? ";

   // require user to specify account number
   ClientData client;
   cin >> accountNumber;

   // user enters information, which is copied into file
   while ( accountNumber > 0 && accountNumber <= 100 ) 
   {
      // user enters last name, first name and balance
      cout << "Enter lastname, firstname, balance\n? ";
      cin >> lastName;
      cin >> firstName;
      cin >> balance;

      // set record accountNumber, lastName, firstName and balance values
      client.setAccountNumber( accountNumber );
      client.setLastName( lastName );
      client.setFirstName( firstName );
      client.setBalance( balance );

      // seek position in file of user-specified record
      outCredit.seekp( ( client.getAccountNumber() - 1 ) * 
         sizeof( ClientData ) );

      // write user-specified information in file
      outCredit.write( reinterpret_cast< const char * >( &client ),
         sizeof( ClientData ) );

      // enable user to enter another account
      cout << "Enter account number\n? ";
      cin >> accountNumber;
   } // end while
} // end main

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
