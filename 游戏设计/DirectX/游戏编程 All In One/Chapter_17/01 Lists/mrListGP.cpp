#include "mrListGP.h"


mrListGP::mrListGP()
{
    m_iCount = 0;
    m_kHead = 0;
    m_kCurrent = 0;
}


// Move the iterator to the beginning of the list
void mrListGP::StartIterator()
{
    m_kCurrent = m_kHead;
}

// Move the iterator forward to the next item.
void mrListGP::MoveForward()
{
    // if the current node is not null, then make the
    // current pointer point to the next node.
    if( 0 != m_kCurrent )
        m_kCurrent = m_kCurrent->m_kNext;
}

// return a pointer to the item in the current node 
mrGamePlayer& mrListGP::GetCurrentItem()
{
    return m_kCurrent->m_kPlayer;
}

// determine whether the iterator is valid or not
mrBool32 mrListGP::IsIteratorValid()
{
    if( 0 != m_kCurrent )
        return mrTrue;
    return mrFalse;
}

// insert a GamePlayer into the list after the current node.
void mrListGP::InsertItem( mrGamePlayer player )
{
    mrListNodeGP* node;
    if( IsIteratorValid() ) 
    {
        node = new mrListNodeGP;
        node->m_kPlayer = player;
        node->m_kNext = m_kCurrent->m_kNext;
        m_kCurrent->m_kNext = node;
        m_iCount++;
    }
    else 
    {
        AppendItem( player);
    }
}

// insert a GamePlayer into the list at the end of the list.
void mrListGP::AppendItem( mrGamePlayer player ) 
{
    mrListNodeGP* node = new mrListNodeGP;
    node->m_kNext = 0;
    node->m_kPlayer = player;
    mrListNodeGP* temp = m_kHead;
    if( 0 != temp ) 
    {
        while( 0 != temp->m_kNext )
        temp = temp->m_kNext;
        temp->m_kNext = node;
    }
    else 
    {
        m_kHead = node;
    }
    m_iCount++;
}

// Remove the current gameplayer.
void mrListGP::RemoveCurrentItem() 
{
    mrListNodeGP* previous;
    if( 0 == m_kCurrent )
        return;
    if( m_kHead == m_kCurrent ) 
    {
        m_kCurrent = m_kHead->m_kNext;
        delete m_kHead;
        m_kHead = m_kCurrent;
    }
    else 
    {
        previous = m_kHead;
        while( previous->m_kNext != m_kCurrent )
            previous = previous->m_kNext;
        m_kCurrent = m_kCurrent->m_kNext;
        delete previous->m_kNext;
        previous->m_kNext = m_kCurrent;
    }
    m_iCount--;
}
