#include "mrDatatypes.h"

class mrBinaryTreeNodeInt
{
public:
    mrInt m_iValue;
    mrBinaryTreeNodeInt* m_kLeft;
    mrBinaryTreeNodeInt* m_kRight;
    mrBinaryTreeNodeInt( int value = 0 );
};

mrBinaryTreeNodeInt::mrBinaryTreeNodeInt( int value )
{
    m_iValue = value;
    m_kLeft = 0;
    m_kRight = 0;
}
