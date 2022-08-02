//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

/** A class of nodes for an array-based binary tree.
 Listing 16-1.
 @file TreeNode.h */

#ifndef _TREE_NODE
#define _TREE_NODE

template<class ItemType>
class TreeNode
{
   
private:
   ItemType item;        // Data portion
   int      leftChild;   // Index to left child
   int      rightChild;  // Index to right child

public:
   TreeNode();
   TreeNode(const ItemType& nodeItem, int left, int right);
   
   // Declarations of the methods setItem, getItem, setLeft, getLeft,
   // setRight, and getRight are here.
}; // end TreeNode

#include "TreeNode.cpp"

#endif 
