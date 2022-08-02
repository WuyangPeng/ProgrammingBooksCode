//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

// Section 19.4.

/** A class of nodes for a link-based red-black tree.
 @file RedBlackNode.h */
 
// PARTIALLY COMPLETE

enum Color {RED, BLACK};

template<class ItemType>
class RedBlackNode : public BinaryNode<ItemType>
{
private:
   Color leftColor, rightColor;
   
public:
   // Get and set methods for leftColor and rightColor
   // . . .
   
}; // end RedBlackNode
