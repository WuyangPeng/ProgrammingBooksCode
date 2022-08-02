//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

/** Listing C1-6.
 @file ToyBox.cpp */

#include "ToyBox.h"

template<class ItemType>
ToyBox<ItemType>::ToyBox()
{
   PlainBox<ItemType>();
   boxColor = BLACK;
}  // end default constructor

template<class ItemType>
ToyBox<ItemType>::ToyBox(const Color& theColor)
{
   PlainBox<ItemType>();
   boxColor = theColor;
}  // end constructor

template<class ItemType>
ToyBox<ItemType>::ToyBox(const ItemType& theItem,
                         const Color& theColor)
{
   PlainBox<ItemType>();
   PlainBox<ItemType>::setItem(theItem);
   boxColor = theColor;
}  // end constructor

template<class ItemType>
Color ToyBox<ItemType>::getColor() const
{
   return boxColor;
}  // end getColor
