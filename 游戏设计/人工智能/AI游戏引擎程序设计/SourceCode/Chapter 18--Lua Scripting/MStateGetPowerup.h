#ifndef __MSTATEGETPOWERUP
#define __MSTATEGETPOWERUP

#include "MessState.h"
#include "MCallbacks.h"

class MStateGetPowerup : public MessState
{
public:
    //constructor/functions
    MStateGetPowerup(Control* parent):MessState(MFSM_STATE_GETPOWERUP,parent){}
    void Update(float dt);
    void Enter();
    void Exit();

    //callbacks for handling messages
    EvadeCallback      m_evadeCallback;
    IdleCallback       m_idleCallback;
};
#endif