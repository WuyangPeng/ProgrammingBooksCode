//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

// Listing 19-1.

/** A class of nodes for a link-based 2-3 tree.
 @file TriNode.h */
 
#ifndef _TRI_NODE
#define _TRI_NODE

template<class ItemType>
class TriNode
{
private:
   ItemType smallItem, largeItem;    // Data portion
   TriNode<ItemType>* leftChildPtr;  // Left-child pointer
   TriNode<ItemType>* midChildPtr;   // Middle-child pointer
   TriNode<ItemType>* rightChildPtr; // Right-child pointer
   
public:
   TriNode();
   TriNode(const ItemType& anItem);
   TriNode(const ItemType& anItem, TriNode<ItemType>* leftPtr,
           TriNode<ItemType>* midPtr, TriNode<ItemType>* rightPtr);
   
   bool isLeaf() const;
   bool isTwoNode() const;
   bool isThreeNode() const;
   
   ItemType getSmallItem() const;
   ItemType getLargeItem() const;
   
   void setSmallItem(const ItemType& anItem);
   void setLargeItem(const ItemType& anItem);
   
   TriNode<ItemType>* getLeftChildPtr() const;
   TriNode<ItemType>* getMidChildPtr() const;
   TriNode<ItemType>* getRightChildPtr() const;
   
   void setLeftChildPtr(TriNode<ItemType>* leftPtr);
   void setMidChildPtr(TriNode<ItemType>* midPtr);
   void setRightChildPtr(TriNode<ItemType>* rightPtr);
}; // end TriNode
#include "TriNode.cpp"
#endif