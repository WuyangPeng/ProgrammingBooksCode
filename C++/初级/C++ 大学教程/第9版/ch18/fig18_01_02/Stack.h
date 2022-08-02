// Fig. 18.1: Stack.h
// Stack class template.
#ifndef STACK_H
#define STACK_H
#include <deque>

template< typename T >
class Stack 
{
public:
   // return the top element of the Stack
   T& top()
   {
      return stack.front();
   } // end function template top

   // push an element onto the Stack
   void push( const T &pushValue ) 
   {
      stack.push_front( pushValue );
   } // end function template push

   // pop an element from the stack
   void pop()
   {
      stack.pop_front();
   } // end function template pop

   // determine whether Stack is empty
   bool isEmpty() const 
   { 
      return stack.empty(); 
   } // end function template isEmpty

   // return size of Stack
   size_t size() const
   {
      return stack.size();
   } // end function template size

private:
   std::deque< T > stack; // internal representation of the Stack
}; // end class template Stack

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
