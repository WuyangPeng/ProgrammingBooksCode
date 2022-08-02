// Fig. 19.16: Queue.h
// Template Queue class definition derived from class List.
#ifndef QUEUE_H
#define QUEUE_H

#include "List.h" // List class definition

template< typename QUEUETYPE >
class Queue: private List< QUEUETYPE > 
{
public:
   // enqueue calls List member function insertAtBack
   void enqueue( const QUEUETYPE &data ) 
   { 
      insertAtBack( data ); 
   } // end function enqueue

   // dequeue calls List member function removeFromFront
   bool dequeue( QUEUETYPE &data ) 
   { 
      return removeFromFront( data ); 
   } // end function dequeue

   // isQueueEmpty calls List member function isEmpty
   bool isQueueEmpty() const 
   {
      return this->isEmpty();
   } // end function isQueueEmpty

   // printQueue calls List member function print
   void printQueue() const 
   { 
      this->print();
   } // end function printQueue
}; // end class Queue

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
