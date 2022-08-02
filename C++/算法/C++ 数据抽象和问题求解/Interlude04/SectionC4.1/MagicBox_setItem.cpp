//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

template<class ItemType>
void MagicBox<ItemType>::setItem(const ItemType& theItem)
{
   if (!firstItemStored)
   {
      PlainBox<ItemType>::setItem(theItem);
      firstItemStored = true; // Box now has magic
   }  // end if
}  // end setItem