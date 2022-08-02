#ifndef MRGENTREENODEINT_H
#define MRGENTREENODEINT_H

#include "mrListNodeGenTreeInt.h"
#include "mrDatatypes.h"
#include <iostream.h>

// a general tree-node class using integers.
class mrGenTreeNodeInt
{
public:
    mrInt m_iValue;
    mrListNodeGenTreeInt* m_kFirstChild;
    mrListNodeGenTreeInt* m_kCurrent;

    mrGenTreeNodeInt( mrInt value );
    ~mrGenTreeNodeInt();
    void Start();
    void MoveForward();
    mrGenTreeNodeInt* GetChild();
    mrBool32 IsChildValid();
    void RemoveCurrentChild();
    void AppendChild( mrGenTreeNodeInt* child );
    void PreOrder();
    void PostOrder();
};


// default constructor:
mrGenTreeNodeInt::mrGenTreeNodeInt( mrInt value )
{
    m_iValue = value;
    m_kFirstChild = 0;
    m_kCurrent = 0;
}

mrGenTreeNodeInt::~mrGenTreeNodeInt()
{
    Start();
    while( IsChildValid() )
    {
        delete GetChild();
        RemoveCurrentChild();
    }
}
 
// Move the child pointer to the first child
void mrGenTreeNodeInt::Start()
{
    m_kCurrent = m_kFirstChild;
}

// Move the current child pointer to the next child.
void mrGenTreeNodeInt::MoveForward()
{
    if( 0 != m_kCurrent )
        m_kCurrent = m_kCurrent->m_kNext;
}

// return a pointer to the current child node
mrGenTreeNodeInt* mrGenTreeNodeInt::GetChild()
{
    return m_kCurrent->m_kNode;
}

// determine whether the current child is valid or not
mrBool32 mrGenTreeNodeInt::IsChildValid()
{
    if( 0 != m_kCurrent )
        return mrTrue;
    return mrFalse;
}

// remove the current node
void mrGenTreeNodeInt::RemoveCurrentChild() 
{
    mrListNodeGenTreeInt* previous;
    if( 0 == m_kCurrent )
        return;
    if( m_kFirstChild == m_kCurrent ) 
    {
        m_kCurrent = m_kFirstChild->m_kNext;
        delete m_kFirstChild;
        m_kFirstChild = m_kCurrent;
    }
    else 
    {
        previous = m_kFirstChild;
        while( previous->m_kNext != m_kCurrent )
            previous = previous->m_kNext;
        m_kCurrent = m_kCurrent->m_kNext;
        delete previous->m_kNext;
        previous->m_kNext = m_kCurrent;
    }
}

// append a child node to the end of the list
void mrGenTreeNodeInt::AppendChild( mrGenTreeNodeInt* child ) 
{
    mrListNodeGenTreeInt* node = new mrListNodeGenTreeInt;
    node->m_kNext = 0;
    node->m_kNode = child;
    mrListNodeGenTreeInt* temp = m_kFirstChild;
    if( 0 != temp ) 
    {
        while( 0 != temp->m_kNext )
        temp = temp->m_kNext;
        temp->m_kNext = node;
    }
    else 
    {
        m_kFirstChild = node;
    }
}


void mrGenTreeNodeInt::PreOrder()
{
    cout << m_iValue << ", ";
    for( Start(); IsChildValid(); MoveForward() )
        GetChild()->PreOrder();
}

void mrGenTreeNodeInt::PostOrder()
{
    for( Start(); IsChildValid(); MoveForward() )
        GetChild()->PostOrder();
    cout << m_iValue << ", ";
}


#endif