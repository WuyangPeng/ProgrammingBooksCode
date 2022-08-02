//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

/** @file TreeDictionary.cpp */

#include "TreeDictionary.h"


template <class KeyType, class ItemType>
bool TreeDictionary<KeyType, ItemType>::add(const KeyType& searchKey,
                                            const ItemType& newItem)
{
   return itemTree.add(Entry<KeyType, ItemType>(newItem, searchKey));
} // end add

template <class KeyType, class ItemType>
bool TreeDictionary<KeyType, ItemType>::remove(const const KeyType& itemKey)
{
   return itemTree.remove(Entry<KeyType, ItemType>(ItemType(), itemKey));
}  // end remove   

