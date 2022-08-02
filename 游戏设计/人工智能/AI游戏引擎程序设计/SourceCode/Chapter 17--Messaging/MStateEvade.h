#ifndef __MSTATEEVADE
#define __MSTATEEVADE

#include "MessState.h"
#include "MCallbacks.h"

class MStateEvade : public MessState
{
public:
    //constructor/functions
    MStateEvade(Control* parent):MessState(MFSM_STATE_EVADE,parent){}
    void Update(float dt);
    void Enter();
    void Exit();
    
    //callbacks for handling messages
    IdleCallback       m_idleCallback;
};
#endif