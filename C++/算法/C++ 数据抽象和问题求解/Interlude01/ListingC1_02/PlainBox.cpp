//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

/** Listing C1-2
    @file PlainBox.cpp */
    
#include "PlainBox.h"

PlainBox::PlainBox()
{
} // end default constructor

PlainBox::PlainBox(const ItemType& theItem)
{
   item = theItem;
} // end constructor

void PlainBox::setItem(const ItemType& theItem)
{
   item = theItem;
} // end setItem

ItemType PlainBox::getItem() const
{
   return item;
} // end getItem