// Additions to the header file:

// Fills the vector bagContents with the data in the nodes of
// the linked chain to which curPtr points.
void fillVector(vector<ItemType>& bagContents, Node<ItemType>* curPtr) const;

// Locates a given entry within this bag.
// Returns either a pointer to the node containing a given entry or
// the null pointer if the entry is not in the bag.
Node<ItemType>* getPointerTo(const ItemType& target,
                             Node<ItemType>* curPtr) const;


// Additions to the implementation file:


template<class ItemType>
void LinkedBag<ItemType>::fillVector(vector<ItemType>& bagContents,
                                     Node<ItemType>* curPtr) const
{
   if (curPtr != nullptr)
   {
      bagContents.push_back(curPtr->getItem());
      fillVector(bagContents, curPtr->getNext());
   } // end if
}  // end fillVector

// Returns either a pointer to the node containing a given entry or
// the null pointer if the entry is not in the bag.
template<class ItemType>
Node<ItemType>* LinkedBag<ItemType>::getPointerTo(const ItemType& target,
                                                  Node<ItemType>* curPtr) const
{
   Node<ItemType>* result = nullptr;
   if (curPtr != nullptr)
   {
      if (target== curPtr->getItem())
         result = curPtr;
      else
         result = getPointerTo(target, curPtr->getNext());
   } // end if
   
   return result;
}  // end getPointerTo