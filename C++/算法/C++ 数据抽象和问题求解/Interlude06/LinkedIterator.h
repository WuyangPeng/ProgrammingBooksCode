//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

/** ADT list: Link-based implementation.
    Listing C6-1.
    @file LinkedIterator.h */

#ifndef _LINKED_ITERATOR
#define _LINKED_ITERATOR

#include <iterator>
#include "Node.h"

using namespace std;

template<class ItemType>
class LinkedList;

template <class ItemType>
class LinkedIterator : public iterator<input_iterator_tag, int>
{
private:
   // ADT associated with iterator
   const LinkedList<ItemType>* containerPtr;
   
   // Current location in collection
   Node<ItemType>* currentItemPtr;
   
public:
   LinkedIterator(const LinkedList<ItemType>* someList,
                  Node<ItemType>* nodePtr);
   
   /** Dereferencing operator overload.
    @return The item at the position referenced by iterator. */
   const ItemType operator*();
   
   /** Prefix increment operator overload.
    @return  The iterator referencing the next position in the list. */
   LinkedIterator<ItemType> operator++();
   
   /** Equality operator overload.
    @param LinkedList  The iterator for comparison.
    @return  True if this iterator references the same list and
       the same position as rightHandSide, false otherwise. */    
    bool operator==(const LinkedIterator<ItemType>& rightHandSide) const;
   
    /** Inequality operator overload.
     @param LinkedList  The iterator for comparison.
     @return  True if this iterator does not reference the same
        list and the same position as rightHandSide, false otherwise. */
   bool operator!=(const LinkedIterator<ItemType>& rightHandSide) const;
}; // end LinkedIterator

#include "LinkedIterator.cpp"
#endif