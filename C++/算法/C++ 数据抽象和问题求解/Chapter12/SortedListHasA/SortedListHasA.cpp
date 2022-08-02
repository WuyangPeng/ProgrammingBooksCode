//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

// PARITALLY COMPLETE.

/** Implementation file for the class SortedListHasA.
 @file SortedListHasA.cpp */

#include "SortedListHasA.h"  // Header file
#include "LinkedList.h"
#include <cassert>
#include <cmath>
  
template<class ItemType>
SortedListHasA<ItemType>::SortedListHasA()
{
   listPtr = new LinkedList<ItemType>();
}  // end default constructor

template<class ItemType>
SortedListHasA<ItemType>::SortedListHasA(const SortedListHasA<ItemType>& sList) 
{
	// First, create our own list
	listPtr = new LinkedList<ItemType>();
	
	// Then add items to it using public methods
	for(int position = 1; position <= sList.getLength(); position++)
	{
		listPtr->insert(position, sList.getEntry(position));
	}  // end for
}  // end copy constructor

template<class ItemType>
SortedListHasA<ItemType>::~SortedListHasA()
{
   clear();
}  // end destructor

template<class ItemType>
void SortedListHasA<ItemType>::insertSorted(const ItemType& newEntry)
{
   int newPosition = fabs(getPosition(newEntry));
   listPtr->insert(newPosition, newEntry);
}  // end insertSorted


//=====================
// List operations:

template<class ItemType>
bool SortedListHasA<ItemType>::remove(int position)
{
   return listPtr->remove(position);
}  // end remove

