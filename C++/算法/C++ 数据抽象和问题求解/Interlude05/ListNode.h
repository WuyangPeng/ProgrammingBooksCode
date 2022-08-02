//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

// Interlude 5, pp 422.

template<class ItemType>
class ListNode           // A node on the list
{
private:
   ItemType item;        // A data item on the list
   Node<ItemType> *next; // Pointer to next node
   Node();
   Node(const ItemType& nodeItem, Node<ItemType>* nextNode);
   
   // Friend class - can access private parts
   friend class LinkedList<ItemType>;
}; // end ListNode