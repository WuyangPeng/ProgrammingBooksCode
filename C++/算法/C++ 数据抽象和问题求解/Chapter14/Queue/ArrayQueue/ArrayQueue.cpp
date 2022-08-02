//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

/** ADT queue: Circular array-based implementation.
 Listing 14-5.
 @file ArrayQueue.cpp */

#include "ArrayQueue.h"  // Header file

template<class ItemType>
ArrayQueue<ItemType>::ArrayQueue() : front(0), back(MAX_QUEUE - 1), count(0)
{
} // end default constructor

template<class ItemType>
bool ArrayQueue<ItemType>::isEmpty() const
{
   return count == 0;
} // end isEmpty

template<class ItemType>
bool ArrayQueue<ItemType>::enqueue(const ItemType& newEntry)
{
   bool result = false;
   if (count < MAX_QUEUE)
   {
      // Queue has room for another item
      back = (back + 1) % MAX_QUEUE;
      items[back] = newEntry;
      count++;
      result = true;
   } // end if
   
   return result;
} // end enqueue

template<class ItemType>
bool ArrayQueue<ItemType>::dequeue()
{
   bool result = false;
   if (!isEmpty())
   {
      front = (front + 1) % MAX_QUEUE;
      count--;
      result = true;
   } // end if
   
   return result;
} // end dequeue

template<class ItemType>
ItemType ArrayQueue<ItemType>::peekFront() const throw(PrecondViolatedExcep)
{
   // Enforce precondition
   if (isEmpty())
      throw PrecondViolatedExcep("peekFront() called with empty queue");
   
   // Queue is not empty; return front
   return items[front];
} // end peekFront
// End of implementation file.
