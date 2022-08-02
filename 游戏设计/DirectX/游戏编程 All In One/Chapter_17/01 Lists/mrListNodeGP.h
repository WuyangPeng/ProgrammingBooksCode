#ifndef MRLISTNODEGP_H
#define MRLISTNODEGP_H

#include "mrGamePlayer.h"

class mrListNodeGP
{
public:
    // The GamePlayer stored In the node
    mrGamePlayer m_kPlayer; 
    
    // A pointer to the next node in the list
    mrListNodeGP* m_kNext;
};


#endif