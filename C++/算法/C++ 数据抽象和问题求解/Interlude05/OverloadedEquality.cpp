//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

// Interlude 5, pp 416 - 417.

template <class ItemType>
bool LinkedList<ItemType>::operator==(const LinkedList<ItemType>& rightHandSide) const
{
   bool isEqual = true; // Assume equal
   
   // First check number of items is the same
   if (itemCount != rightHandSide.getLength())
      isEqual = false;
   else
   {  // Then compare items
      Node<ItemType>* leftSidePtr = headPtr;
      Node<ItemType>* rightSidePtr = rightHandSide.headPtr;
      
      while ((leftSidePtr != nullptr) && (rightSidePtr != nullptr) && isEqual)
      {
         ItemType leftItem = leftSidePtr->getItem();
         ItemType rightItem = rightSidePtr->getItem();
         isEqual = (leftItem == rightItem);
         
         leftSidePtr = leftSidePtr->getNext();
         rightSidePtr = rightSidePtr->getNext();
      }  // end whiile
   }  // end if
   
   return isEqual;
}  // end operator==