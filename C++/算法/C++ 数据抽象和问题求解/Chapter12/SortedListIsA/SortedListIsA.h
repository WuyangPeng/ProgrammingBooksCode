//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

/** ADT sorted list using ADT list.
 Listing 12-4.
 @file SortedListIsA.h */

#ifndef _SORTED_LIST_IS_A
#define _SORTED_LIST_IS_A

#include "LinkedList.h"
#include "Node.h"
#include "PrecondViolatedExcep.h"

template<class ItemType>
class SortedListIsA : public LinkedList<ItemType>
{
public:
   SortedListIsA();
   SortedListIsA(const SortedListIsA<ItemType>& sList);
   virtual ~SortedListIsA();

   void insertSorted(const ItemType& newEntry);
   bool removeSorted(const ItemType& anEntry);
   int getPosition(const ItemType& anEntry) const;
   
   // The inherited methods remove, clear, getEntry, isEmpty, and
   // getLength have the same specifications as given in ListInterface.
/*
   bool remove(int position);
   void clear();
   ItemType getEntry(int position) const throw(PrecondViolatedExcep);
   bool isEmpty() const;
   int getLength() const;
*/
   // The following methods must be overridden to disable their
   // effect on a sorted list:
   bool insert(int newPosition, const ItemType& newEntry);
	void setEntry(int position, const ItemType& newEntry) throw(PrecondViolatedExcep);
}; // end SortedListIsA

#include "SortedListIsA.cpp"
#endif 
