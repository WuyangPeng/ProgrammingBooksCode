//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

/** @file StackInterface.h */

#ifndef _STACK_INTERFACE
#define _STACK_INTERFACE

template<class ItemType>
class StackInterface
{
public:
   /** Sees whether this stack is empty.
    @return True if the stack is empty, or false if not. */
   virtual bool isEmpty() const = 0;
   
   /** Adds a new entry to the top of this stack.
    @post If the operation was successful, newEntry is at the top of the stack.
    @param newEntry The object to be added as a new entry.
    @return True if the addition is successful or false if not. */
   virtual bool push(const ItemType& newEntry) = 0;
   
   /** Removes the top of this stack.
    @post If the operation was successful, the top of the stack
    has been removed.
    @return True if the removal is successful or false if not. */
   virtual bool pop() = 0;
   
   /** Returns the top of this stack.
    @pre The stack is not empty.
    @post The top of the stack has been returned, and
    the stack is unchanged.
    @return The top of the stack. */
   virtual ItemType peek() const = 0;
}; // end StackInterface
#endif