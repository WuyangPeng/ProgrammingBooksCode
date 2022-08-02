//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

/** @file  HashedDictionary.cpp */

// Separate chaining resolves collisions

// PARTIALLY COMPLETE

template <class KeyType, class ItemType>
bool HashedDictionary<KeyType, ItemType>::add(const KeyType& searchKey, const ItemType& newItem)
{
   // Create entry to add to dictionary
   HashedEntry<KeyType, ItemType>* entryToAddPtr =
                  new HashedEntry<KeyType, ItemType>(newItem, searchKey);
   
   // Compute the hashed index into the array
   int itemHashIndex = getHashIndex(searchKey);
   
   // Add the entry to the chain at itemHashIndex
   if (hashTable[itemHashIndex] == nullptr)
   {
      hashTable[itemHashIndex] = entryToAddPtr;
   }
   else
   {
      entryToAddPtr->setNext(hashTable[itemHashIndex]);
      hashTable[itemHashIndex] = entryToAddPtr;
   } // end if
   
   return true;
} // end add

template <class KeyType, class ItemType>
bool HashedDictionary<KeyType, ItemType>::remove(const KeyType& searchKey)
{
   bool itemFound = false;
   
   // Compute the hashed index into the array
   int itemHashIndex = getHashIndex(searchKey);
   if (hashTable[itemHashIndex] != nullptr)
   {
      // Special case - first node has target
      if (searchKey == hashTable[itemHashIndex]->getKey())
      {
         HashedEntry<KeyType, ItemType>* entryToRemovePtr =
         hashTable[itemHashIndex];
         hashTable[itemHashIndex] = hashTable[itemHashIndex]->getNext();
         delete entryToRemovePtr;
         entryToRemovePtr = nullptr; // For safety
         itemFound = true;
      }
      else // Search the rest of the chain
      {
         HashedEntry<KeyType, ItemType>* prevPtr = hashTable[itemHashIndex];
         HashedEntry<KeyType, ItemType>* curPtr = prevPtr->getNext();
         while ((curPtr != nullptr) && !itemFound )
         {
            // Found item in chain so remove that node
            if (searchKey == curPtr->getKey())
            {
               prevPtr->setNext(curPtr->getNext());
               delete curPtr;
               curPtr = nullptr; // For safety
               itemFound = true;
            }
            else // Look at next entry in chain
            {
               prevPtr = curPtr;
               curPtr = curPtr->getNext();
            } // end if
         } // end while
      } // end if
   } // end if
   
   return itemFound;
} // end remove

