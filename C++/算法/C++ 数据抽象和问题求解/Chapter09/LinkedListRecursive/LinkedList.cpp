// The copy constructor and the method setEntry are left as exercises.
// ===================================================================

//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

/** Implementation file for the class LinkedList.
 @file LinkedList.cpp */

#include "LinkedList.h"  // Header file
#include <cassert>
  
template<class ItemType>
LinkedList<ItemType>::LinkedList() : headPtr(nullptr), itemCount(0)
{
}  // end default constructor

template<class ItemType>
LinkedList<ItemType>::~LinkedList()
{
   clear();
}  // end destructor

template<class ItemType>
bool LinkedList<ItemType>::isEmpty() const
{
   return itemCount == 0;
}  // end isEmpty

template<class ItemType>
int LinkedList<ItemType>::getLength() const
{
   return itemCount;
}  // end getLength

template<class ItemType>
bool LinkedList<ItemType>::insert(int newPosition, const ItemType& newEntry)
{
   bool ableToInsert = (newPosition >= 1) && (newPosition <= itemCount + 1);
   if (ableToInsert)
   {
      // Create a new node containing the new entry
      Node<ItemType>* newNodePtr = new Node<ItemType>(newEntry);
      headPtr = insertNode(newPosition, newNodePtr, headPtr);
   }  // end if
   
   return ableToInsert;
}  // end insert

template<class ItemType>
bool LinkedList<ItemType>::remove(int position)
{
   bool ableToRemove = (position >= 1) && (position <= itemCount);
   if (ableToRemove)
   {
      Node<ItemType>* curPtr = nullptr;
      if (position == 1)
      {
         // Remove the first node in the chain
         curPtr = headPtr; // Save pointer to node
         headPtr = headPtr->getNext();
      }
      else
      {
         // Find node that is before the one to delete
         Node<ItemType>* prevPtr = getNodeAt(position - 1);
         
         // Point to node to delete
         curPtr = prevPtr->getNext();
         
         // Disconnect indicated node from chain by connecting the
         // prior node with the one after
         prevPtr->setNext(curPtr->getNext());
      }  // end if
      
      // Return node to system
      curPtr->setNext(nullptr);
      delete curPtr;
      curPtr = nullptr;
      
      itemCount--;  // Decrease count of entries
   }  // end if
   
   return ableToRemove;
}  // end remove

template<class ItemType>
void LinkedList<ItemType>::clear()
{
   while (!isEmpty())
      remove(1);
}  // end clear

template<class ItemType>
ItemType LinkedList<ItemType>::getEntry(int position) const throw(PrecondViolatedExcep)
{
   // Enforce precondition
   bool ableToGet = (position >= 1) && (position <= itemCount);
   if (ableToGet)
   {
      Node<ItemType>* nodePtr = getNodeAt(position);
      return nodePtr->getItem();
   }
   else
   {
      string message = "getEntry() called with an empty list or "; 
      message  = message + "invalid position.";
      throw(PrecondViolatedExcep(message)); 
   }  // end if
}  // end getEntry

template<class ItemType>
Node<ItemType>* LinkedList<ItemType>::getNodeAt(int position) const
{
   // Debugging check of precondition
   assert( (position >= 1) && (position <= itemCount) );
   
   // Count from the beginning of the chain
   Node<ItemType>* curPtr = headPtr;
   for (int skip = 1; skip < position; skip++)
      curPtr = curPtr->getNext();
      
   return curPtr;
}  // end getNodeAt

// RECURSIVE
template<class ItemType>
Node<ItemType>* LinkedList<ItemType>::insertNode(int position, Node<ItemType>* newNodePtr,
                                                 Node<ItemType>* subChainPtr)
{
   if (position == 1)
   {
      // Insert new node at beginning of subchain
      newNodePtr->setNext(subChainPtr);
      subChainPtr = newNodePtr;
      itemCount++;  // Increase count of entries
   }
   else
   {
      Node<ItemType>* afterPtr = insertNode(position - 1, newNodePtr, subChainPtr->getNext());
      subChainPtr->setNext(afterPtr);
   }  // end if
   
   return subChainPtr;
}  // end insertNode

//  End of implementation file.
