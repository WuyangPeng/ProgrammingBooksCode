#include "mrBinaryTreeNodeInt.h"

class mrBSTInt
{
private:
 mrBinaryTreeNodeInt* m_kRoot;
 mrInt m_iCount;
 mrBinaryTreeNodeInt* Remove01( mrBinaryTreeNodeInt* parent, mrBool32 isLeft );
 mrBinaryTreeNodeInt* Remove2( mrBinaryTreeNodeInt* parent, mrBool32 isLeft );
public:
 mrBSTInt();
 mrBool32 Insert( mrInt value );
 mrBool32 Search( mrInt value );
 mrBool32 Remove( mrInt value );
};


mrBSTInt::mrBSTInt()
{
 m_kRoot = 0;
 m_iCount = 1;
}

mrBool32 mrBSTInt::Search( mrInt value )
{
 mrBinaryTreeNodeInt* node = m_kRoot;
 while( 0 != node )
 {
  if( value == node->m_iValue )
      return mrTrue;
  if( value < node->m_iValue )
      node = node->m_kLeft;
  else
      node = node->m_kRight;
 }
 return mrFalse;
}


mrBool32 mrBSTInt::Insert( mrInt value )
{
 mrBinaryTreeNodeInt* node = m_kRoot;
 if( 0 == m_kRoot )
  m_kRoot = new mrBinaryTreeNodeInt( value );
 else
 {
  while( 0 != node )
  {
   if( value == node->m_iValue )
    return mrFalse;
   else if( value < node->m_iValue )
   {
    if( 0 == node->m_kLeft )
    {
     node->m_kLeft = new mrBinaryTreeNodeInt( value );
     node = 0;
    }
    else
     node = node->m_kLeft;
   }
   else
   {
    if( 0 == node->m_kRight )
    {
     node->m_kRight = new mrBinaryTreeNodeInt( value );
     node = 0;
    }
    else
     node = node->m_kRight;
   }
  }
 }
 m_iCount++;
 return mrTrue;
}


mrBool32 mrBSTInt::Remove( mrInt value )
{
 mrBinaryTreeNodeInt* parent = 0;
 mrBinaryTreeNodeInt* node = m_kRoot;
 mrBool32 done = mrFalse;
 mrBool32 isLeft = mrFalse;
 while( !done )
 {
  if( 0 == node )
   return mrFalse;
  if( value == node->m_iValue )
   done = mrTrue;
  else
  {
   parent = node;
   if( value < node->m_iValue )
    node = node->m_kLeft;
   else
    node = node->m_kRight;
  }
 }
 if( 0 != parent )
 {
  if( parent->m_kLeft == node )
   isLeft = mrTrue;
 }
 if( 0 != node->m_kLeft && 0 != node->m_kRight )
  Remove2( parent, isLeft );
 else
  Remove01( parent, isLeft );
 node->m_kLeft = 0;
 node->m_kRight = 0;
 delete node;
 m_iCount--;
 return mrTrue;
}


mrBinaryTreeNodeInt* mrBSTInt::Remove01( mrBinaryTreeNodeInt* parent, mrBool32 isLeft )
{
 mrBinaryTreeNodeInt* node = 0;
 mrBinaryTreeNodeInt* child = 0;
 if( 0 == parent )
  node = m_kRoot;
 else
 {
  if( isLeft )
   node = parent->m_kLeft;
  else
   node = parent->m_kRight;
 }
 if( 0 != node->m_kLeft )
  child = node->m_kLeft;
 else
  child = node->m_kRight;
 if( 0 == parent )
 {
   m_kRoot = child;
 }
 else
 {
  if( isLeft )
   parent->m_kLeft = child;
  else
   parent->m_kRight = child;
 }
 return node;
}



mrBinaryTreeNodeInt* mrBSTInt::Remove2( mrBinaryTreeNodeInt* parent, mrBool32 isLeft )
{
 mrBinaryTreeNodeInt* largest = 0;
 mrBinaryTreeNodeInt* largestparent = 0;
 mrBinaryTreeNodeInt* node = 0;
 if( 0 == parent )
  node = m_kRoot;
 else
 {
  if( isLeft )
   node = parent->m_kLeft;
  else
   node = parent->m_kRight;
 }
 if( 0 == node->m_kLeft->m_kRight )
  largest = Remove01( node, mrTrue );
 else
 {
  largestparent = node;
  largest = node->m_kLeft;
  while( 0 != largest->m_kRight )
  {
   largestparent = largest;
   largest = largest->m_kRight;
  }
  Remove01( largestparent, mrFalse );
 }
 largest->m_kLeft = node->m_kLeft;
 largest->m_kRight = node->m_kRight;
 if( 0 == parent )
 {
  m_kRoot = largest;
 }
 else
 {
  if( isLeft )
   parent->m_kLeft = largest;
  else
   parent->m_kRight = largest;
 }
 return node;
}