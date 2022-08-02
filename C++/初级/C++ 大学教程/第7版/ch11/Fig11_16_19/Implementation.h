// Fig. 11.16: Implementation.h
// Implementation class definition.

class Implementation 
{
public:
   // constructor
   Implementation( int v )  
      : value( v ) // initialize value with v
   { 
      // empty body
   } // end constructor Implementation

   // set value to v
   void setValue( int v )   
   { 
      value = v; // should validate v
   } // end function setValue

   // return value 
   int getValue() const      
   { 
      return value; 
   } // end function getValue
private:
   int value; // data that we would like to hide from the client
}; // end class Implementation

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
