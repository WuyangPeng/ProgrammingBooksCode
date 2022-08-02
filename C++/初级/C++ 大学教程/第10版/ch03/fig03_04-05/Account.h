// Fig. 3.4: Account.h
// Account class with a constructor that initializes the account name.
#include <string>

class Account {
public:
   // constructor initializes data member name with parameter accountName
   explicit Account(std::string accountName) 
     : name{accountName} { // member initializer
	  // empty body
   }                                            

   // function to set the account name
   void setName(std::string accountName) {
      name = accountName;
   } 

   // function to retrieve the account name
   std::string getName() const {
      return name; 
   } 
private:
   std::string name; // account name data member
}; // end class Account

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
