//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

/** ADT sorted list using ADT list.
 Listing 12-5.
 @file SortedListAsA.h */

#ifndef _SORTED_LIST_AS_A
#define _SORTED_LIST_AS_A

#include "SortedListInterface.h"
#include "LinkedList.h"
#include "Node.h"
#include "PrecondViolatedExcep.h"

template<class ItemType>
class SortedListAsA : public SortedListInterface<ItemType>, private LinkedList<ItemType>
{
public:
   SortedListAsA();
   SortedListAsA(const SortedListAsA<ItemType>& sList);
   virtual ~SortedListAsA();

   void insertSorted(const ItemType& newEntry);
   bool removeSorted(const ItemType& anEntry);
   int getPosition(const ItemType& newEntry) const;
   
   // The following methods are inherited and have the same 
   // specifications as given in ListInterface:
   bool isEmpty() const;
   int getLength() const;
   bool remove(int position);
   void clear();
   ItemType getEntry(int position) const throw(PrecondViolatedExcep);   
}; // end SortedListAsA

#include "SortedListAsA.cpp"
#endif 
