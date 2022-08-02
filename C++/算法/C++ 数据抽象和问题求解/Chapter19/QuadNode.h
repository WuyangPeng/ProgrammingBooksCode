//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

// Section 19.3.

// PARTIALLY COMPLETE

/** A class of nodes for a link-based 2-3-4 tree.
 @file QuadNode.h */
 
template<class ItemType>
class QuadNode
{   
private:
   ItemType smallItem, middleItem, largeItem; // Data portion
   QuadNode<ItemType>* leftChildPtr;          // Left-child pointer
   QuadNode<ItemType>* leftMidChildPtr;       // Middle-left-child pointer
   QuadNode<ItemType>* rightMidChildPtr;      // Middle-right-child pointer
   QuadNode<ItemType>* rightChildPtr;         // Right-child pointer
   
   // Constructors, accessor methods, and mutator methods are here.

}; // end QuadNode

