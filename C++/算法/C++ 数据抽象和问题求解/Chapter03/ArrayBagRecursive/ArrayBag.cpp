//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

/** Implementation file for the class ArrayBag: Recursive version.
 @file ArrayBag.cpp */

#include "ArrayBag.h"
#include <cstddef>

template<class ItemType>
ArrayBag<ItemType>::ArrayBag(): itemCount(0), maxItems(DEFAULT_CAPACITY)
{
}  // end default constructor

template<class ItemType>
int ArrayBag<ItemType>::getCurrentSize() const
{
	return itemCount;
}  // end getCurrentSize

template<class ItemType>
bool ArrayBag<ItemType>::isEmpty() const
{
	return itemCount == 0;
}  // end isEmpty

template<class ItemType>
bool ArrayBag<ItemType>::add(const ItemType& newEntry)
{
	bool hasRoomToAdd = (itemCount < maxItems);
	if (hasRoomToAdd)
	{
		items[itemCount] = newEntry;
		itemCount++;
	}  // end if
   
	return hasRoomToAdd;
}  // end add

template<class ItemType>
bool ArrayBag<ItemType>::remove(const ItemType& anEntry)
{
   int locatedIndex = getIndexOf(anEntry, 0);
	bool canRemoveItem = !isEmpty() && (locatedIndex > -1);
	if (canRemoveItem)
	{
		itemCount--;
		items[locatedIndex] = items[itemCount];
	}  // end if
   
	return canRemoveItem;
}  // end remove

template<class ItemType>
void ArrayBag<ItemType>::clear()
{
	itemCount = 0;
}  // end clear

template<class ItemType>
bool ArrayBag<ItemType>::contains(const ItemType& anEntry) const
{
	return getIndexOf(anEntry, 0) > -1;
}  // end contains

template<class ItemType>
int ArrayBag<ItemType>::getFrequencyOf(const ItemType& anEntry) const
{
	return countFrequency(anEntry, 0);
}  // end getFrequencyOf

template<class ItemType>
vector<ItemType> ArrayBag<ItemType>::toVector() const
{
	vector<ItemType> bagContents;
	for (int i = 0; i < itemCount; i++)
		bagContents.push_back(items[i]);
   
   return bagContents;
}  // end toVector

// private
template<class ItemType>
int ArrayBag<ItemType>::countFrequency(const ItemType& anEntry, int searchIndex) const
{
   int frequency = 0;
   if (searchIndex < itemCount)
   {
      if (items[searchIndex] == anEntry)
      {
         frequency = 1 + countFrequency(anEntry, searchIndex + 1);
      }
      else
      {
         frequency = countFrequency(anEntry, searchIndex + 1);
      }  // end if
   }  // end if

   return frequency;
}  // end countFrequency

// private
template<class ItemType>
int ArrayBag<ItemType>::getIndexOf(const ItemType& target, int searchIndex) const
{
   int result = -1;
   if (searchIndex < itemCount)
   {
      if (items[searchIndex] == target)
      {
         result = searchIndex;
      } 
      else
      {
         result = getIndexOf(target, searchIndex + 1);
      }  // end if
   }  // end if
   
   return result;
}  // end getIndexOf
