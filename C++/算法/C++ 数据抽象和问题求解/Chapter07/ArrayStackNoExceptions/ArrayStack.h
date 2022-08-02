//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

/** ADT stack: Array-based implementation.
 Listing 7-1
 @file ArrayStack.h */

#ifndef _ARRAY_STACK
#define _ARRAY_STACK

#include "StackInterface.h"

const int MAX_STACK = 5;

template<class ItemType>
class ArrayStack : public StackInterface<ItemType>
{
private:	
	ItemType items[MAX_STACK]; // Array of stack items
	int      top;              // Index to top of stack
	
public:
	 ArrayStack();             // Default constructor
	 bool isEmpty() const;
	 bool push(const ItemType& newEntry);
	 bool pop();
	 ItemType peek() const;	
}; // end ArrayStack

#include "ArrayStack.cpp"
#endif
