//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

template <class KeyType, class ItemType>
bool Entry<KeyType, ItemType>::operator==(const Entry<KeyType, ItemType>& rightHandItem) const
{
   return (searchKey == rightHandItem.getKey());
}  // end operator==

