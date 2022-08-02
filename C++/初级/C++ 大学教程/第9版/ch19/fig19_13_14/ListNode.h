// Fig. 19.4: ListNode.h
// Template ListNode class definition.
#ifndef LISTNODE_H
#define LISTNODE_H

// forward declaration of class List required to announce that class 
// List exists so it can be used in the friend declaration at line 13
template< typename NODETYPE > class List;                            

template< typename NODETYPE >
class ListNode 
{
   friend class List< NODETYPE >; // make List a friend

public:
   explicit ListNode( const NODETYPE &info ) // constructor
      : data( info ), nextPtr( nullptr ) 
   { 
      // empty body
   } // end ListNode constructor

   NODETYPE getData() const // return data in node
   { 
      return data; 
   } // end function getData
private:
   NODETYPE data; // data
   ListNode< NODETYPE > *nextPtr; // next node in list
}; // end class ListNode

#endif

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
