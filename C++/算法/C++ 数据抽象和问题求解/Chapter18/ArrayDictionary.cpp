//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

/** @file  ArrayDictionary */

// PARTIALLY COMPLETE

template <class KeyType, class ItemType>
bool ArrayDictionary<KeyType, ItemType>::add(const KeyType& searchKey, const ItemType& newItem)
{
   bool ableToInsert = (itemCount < maxItems);
   if (ableToInsert)
   {
      // Make room for new entry by shifting all entries at
      // positions >= newPosition toward the end of the array
      // (no shift if newPosition == itemCount + 1). Performing
      // a binary search doesn’t help here, because we need to
      // shift the entries while looking for the insertion location.
      int index = itemCount;
      
      // Short-circuit evaluation is important
      while ( (index > 0) && (searchKey < items[index - 1].getKey()) )
      {
         items[index] = items[index - 1];
         index--;
      }  // end while
      
      // Insert new entry
      items[index] = Entry<KeyType, ItemType>(newItem, searchKey);
      itemCount++; // Increase count of entries
   }  // end if
   
   return ableToInsert;
}  // end add

