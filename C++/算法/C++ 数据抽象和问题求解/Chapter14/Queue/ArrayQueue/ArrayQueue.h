//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

/** ADT queue: Circular array-based implementation.
 Listing 14-4.
 @file ArrayQueue.h */

#ifndef _ARRAY_QUEUE
#define _ARRAY_QUEUE

#include "QueueInterface.h"
#include "PrecondViolatedExcep.h"

const int MAX_QUEUE = 50;

template<class ItemType>
class ArrayQueue : public QueueInterface<ItemType>
{
private:
   ItemType items[MAX_QUEUE]; // Array of queue items
   int front;                 // Index to front of queue
   int back;                  // Index to back of queue
   int count;                 // Number of items currently in the queue
   
public:
   ArrayQueue();
   // Copy constructor and destructor supplied by compiler
   bool isEmpty() const;
   bool enqueue(const ItemType& newEntry);
   bool dequeue();
   
   /** @throw PrecondViolatedExcep if queue is empty. */
   ItemType peekFront() const throw(PrecondViolatedExcep);
}; // end ArrayQueue
#include "ArrayQueue.cpp"
#endif