//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

// Listing 18-4.

/** A binary search tree implementation of the ADT dictionary
    that organizes its data items in sorted search-key order.
    Search keys in the dictionary are unique.
 @file TreeDictionary.h */
 
#ifndef _TREE_DICTIONARY
#define _TREE_DICTIONARY

#include "DictionaryInterface.h"
#include "BinarySearchTree.h"
#include "Entry.h"
#include "NotFoundException.h"

template <class KeyType, class ItemType>
class TreeDictionary : public DictionaryInterface<KeyType, ItemType>
{
private:
   // Binary search tree of dictionary entries
   BinarySearchTree<Entry<KeyType, ItemType> > itemTree;
   
   void traversalHelper(Entry<KeyType, ItemType>& theEntry);
   
public:
   TreeDictionary();
   TreeDictionary(const TreeDictionary<KeyType, ItemType>& dict);
   virtual ~TreeDictionary();
   
   // The declarations of the public methods appear here and are the
   // same as given in Listing 18-3 for the class ArrayDictionary.
 
   bool isEmpty() const;
   int getNumberOfItems() const;
   bool add(const KeyType& searchKey, const ItemType& newItem);
   bool remove(const KeyType& searchKey);
   void clear();
   ItemType getItem(const KeyType& searchKey) const throw (NotFoundException);
   bool contains(const KeyType& searchKey) const;
   
   /** Traverses the items in this dictionary in sorted search-key order
    and calls a given client function once for each item. */
   void traverse(void visit(ItemType&)) const;
}; // end TreeDictionary

#include "TreeDictionary.cpp"
#endif