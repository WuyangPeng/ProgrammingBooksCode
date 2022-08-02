//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

// Interlude 5, pp 418 - 419.

template <class ItemType>
LinkedList<ItemType>& LinkedList<ItemType>::operator=(const LinkedList<ItemType>& rightHandSide)
{
   // Check for assignment to self
   if (this != &rightHandSide)
   {
      this->clear();                          // Deallocate left-hand side
      headPtr = copyListNodes(rightHandSide); // Copy list nodes
      itemCount = rightHandSide.itemCount;    // Copy size of list
   }  // end if
   
   return *this;
} // end operator=
