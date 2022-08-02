// Fig. 14.2: Stack.h
// Stack class template.
#ifndef STACK_H
#define STACK_H

template< typename T >
class Stack 
{
public:
   Stack( int = 10 ); // default constructor (stack size 10)

   // destructor
   ~Stack() 
   { 
      delete [] stackPtr; // deallocate internal space for stack
   } // end ~Stack destructor

   bool push( const T& ); // push an element onto the stack
   bool pop( T& ); // pop an element off the stack

   // determine whether Stack is empty
   bool isEmpty() const 
   { 
      return top == -1; 
   } // end function isEmpty

   // determine whether Stack is full
   bool isFull() const 
   { 
      return top == size - 1; 
   } // end function isFull

private:
   int size; // # of elements in the stack
   int top; // location of the top element (-1 means empty)
   T *stackPtr; // pointer to internal representation of the stack
}; // end class template Stack

// constructor template
template< typename T >
Stack< T >::Stack( int s )
   : size( s > 0 ? s : 10 ), // validate size
     top( -1 ), // Stack initially empty
     stackPtr( new T[ size ] ) // allocate memory for elements
{
   // empty body
} // end Stack constructor template

// push element onto stack;
// if successful, return true; otherwise, return false
template< typename T >
bool Stack< T >::push( const T &pushValue )
{
   if ( !isFull() ) 
   {
      stackPtr[ ++top ] = pushValue; // place item on Stack
      return true; // push successful
   } // end if

   return false; // push unsuccessful
} // end function template push

// pop element off stack;
// if successful, return true; otherwise, return false
template< typename T > 
bool Stack< T >::pop( T &popValue )
{
   if ( !isEmpty() ) 
   {
      popValue = stackPtr[ top-- ]; // remove item from Stack
      return true; // pop successful
   } // end if

   return false; // pop unsuccessful
} // end function template pop

#endif

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
