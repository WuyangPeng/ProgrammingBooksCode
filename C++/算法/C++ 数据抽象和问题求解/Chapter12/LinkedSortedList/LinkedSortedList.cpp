//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

// PARITALLY COMPLETE.


/** Implementation file for the class LinkedSortedList.
 @file LinkedSortedList.cpp */

#include "LinkedSortedList.h"  // Header file
#include <cassert>
  
template<class ItemType>
LinkedSortedList<ItemType>::LinkedSortedList(const LinkedSortedList<ItemType>& aList)
{
	headPtr = copyChain(aList.headPtr);
}  // end copy constructor

template<class ItemType>
void LinkedSortedList<ItemType>::insertSorted(const ItemType& newEntry)
{
   Node<ItemType>* newNodePtr = new Node<ItemType>(newEntry);
   Node<ItemType>* prevPtr = getNodeBefore(newEntry);
   
   if (isEmpty() || (prevPtr == nullptr)) // Add at beginning
   {
      newNodePtr->setNext(headPtr);
      headPtr = newNodePtr;
   }
   else // Add after node before
   {
      Node<ItemType>* aftPtr = prevPtr->getNext();
      newNodePtr->setNext(aftPtr);
      prevPtr->setNext(newNodePtr);
   } // end if
   
   itemCount++;
} // end insertSorted

// Private Methods:

template<class ItemType>
Node<ItemType>* LinkedSortedList<ItemType>::copyChain(const Node<ItemType>* origChainPtr)
{
   Node<ItemType>* copiedChainPtr;
	if (origChainPtr == nullptr)
	{
      copiedChainPtr = nullptr;
   }
   else
   {
		// Build new chain from given one
		copiedChainPtr = new Node<ItemType>(origChainPtr->getItem());
		copiedChainPtr->setNext(copyChain(origChainPtr->getNext()));
	}  // end if
   
	return copiedChainPtr;
}  // end copyChain

template<class ItemType>
Node<ItemType>* LinkedSortedList<ItemType>::getNodeBefore(const ItemType& anEntry) const
{
   Node<ItemType>* curPtr = headPtr;
   Node<ItemType>* prevPtr = nullptr;
   
   while ( (curPtr != nullptr) && (anEntry > curPtr->getItem()) )
   {
      prevPtr = curPtr;
      curPtr = curPtr->getNext();
   } // end while
   
   return prevPtr;
} // end getNodeBefore

