// Fig. 23.2: fig23_02.cpp
// Demonstrating regular expressions.
#include <iostream>
#include <string>
#include <boost/regex.hpp>
using namespace std;

int main()
{
   // create a regular expression
   boost::regex expression( "J.*\\d[0-35-9]-\\d\\d-\\d\\d" );

   // create a string to be tested
   string string1 = "Jane's Birthday is 05-12-75\n"
      "Dave's Birthday is 11-04-68\n"
      "John's Birthday is 04-28-73\n"
      "Joe's Birthday is 12-17-77";

   // create a boost::smatch object to hold the search results
   boost::smatch match;

   // match regular expression to string and print out all matches
   while ( boost::regex_search( string1, match, expression,
      boost::match_not_dot_newline ) )
   {
      cout << match << endl; // print the matching string
      
      // remove the matched substring from the string
      string1 = match.suffix();
   } // end while
} // end of function main

/**************************************************************************
 * (C) Copyright 1992-2010 by Deitel & Associates, Inc. and               *
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
