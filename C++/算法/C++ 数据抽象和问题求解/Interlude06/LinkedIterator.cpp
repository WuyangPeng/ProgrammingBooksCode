//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

/** Listing C6-2.
 @file LinkedIterator.cpp */

#include "LinkedIterator.h"

template <class ItemType>
LinkedIterator<ItemType>::
LinkedIterator(const LinkedList<ItemType>* someList,
               Node<ItemType>* nodePtr):
               containerPtr(someList), currentItemPtr(nodePtr)
{
}  // end constructor

template <class ItemType>
const ItemType LinkedIterator<ItemType>::operator*()
{
   return currentItemPtr->getItem();
}  // end operator*

template <class ItemType>
LinkedIterator<ItemType> LinkedIterator<ItemType>::operator++()
{
   currentItemPtr = currentItemPtr->getNext();
   return *this;
}  // end prefix operator++

template <class ItemType>
bool LinkedIterator<ItemType>::operator==(const
                                          LinkedIterator<ItemType>& rightHandSide) const
{
   return ((containerPtr == rightHandSide.containerPtr) &&
           (currentItemPtr == rightHandSide.currentItemPtr));
}  // end operator==

template <class ItemType>
bool LinkedIterator<ItemType>::operator!=(const
                                          LinkedIterator<ItemType>& rightHandSide) const
{
   return ((containerPtr != rightHandSide.containerPtr) ||
           (currentItemPtr != rightHandSide.currentItemPtr));
}  // end operator!=