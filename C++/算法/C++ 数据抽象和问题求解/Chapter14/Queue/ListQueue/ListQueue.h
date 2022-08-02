//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

/** ADT queue: ADT list implementation.
 Listing 14-1.
 @file ListQueue.h */

#ifndef _LIST_QUEUE
#define _LIST_QUEUE

#include "QueueInterface.h"
#include "LinkedList.h"
#include "PrecondViolatedExcep.h"

template<class ItemType>
class ListQueue : public QueueInterface<ItemType>
{
private:
   LinkedList<ItemType>* listPtr; // Pointer to list of queue items
   
public:
   ListQueue();
   ListQueue(const ListQueue& aQueue);
   ~ListQueue();
   bool isEmpty() const;
   bool enqueue(const ItemType& newEntry);
   bool dequeue();
   
   /** @throw  PrecondViolatedExcep if queue is empty. */
   ItemType peekFront() const throw(PrecondViolatedExcep);
}; // end ListQueue

#include "ListQueue.cpp"
#endif