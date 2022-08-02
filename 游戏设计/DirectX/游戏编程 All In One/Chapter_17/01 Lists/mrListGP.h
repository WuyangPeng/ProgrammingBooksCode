#ifndef MRLISTGP_H
#define MRLISTGP_H

#include "mrListNodeGP.h"

class mrListGP
{
public:

    // constructor, initialises object.
    mrListGP();

    // makes the iterator point to the first node
    // in the list.
    void StartIterator();

    // moves the iterator forward to the next item
    // in the list.
    void MoveForward();

    // retrieves a reference to the item in the
    // current node.
    mrGamePlayer& GetCurrentItem();

    // determines if the iterator is valid.
    mrBool32 IsIteratorValid();

    // inserts an item after the current node.
    void InsertItem( mrGamePlayer player );

    // removes the current item.
    void RemoveCurrentItem();

    // appends a new gameplayer to the end of the list.
    void AppendItem( mrGamePlayer player );

    // returns the count of the list.
    mrInt GetCount();


private:
    // A pointer to the head of the list, the first node.
    mrListNodeGP* m_kHead;

    // a pointer to the current node in the list.
    mrListNodeGP* m_kCurrent;

    // the current item count of the list.
    mrInt m_iCount;
};


#endif