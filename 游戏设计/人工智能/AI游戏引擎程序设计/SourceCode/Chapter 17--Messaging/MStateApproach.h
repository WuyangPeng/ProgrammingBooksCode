#ifndef __MSTATEAPPROACH
#define __MSTATEAPPROACH

#include "MessState.h"
#include "MCallbacks.h"

class MStateApproach : public MessState
{
public:
    //constructor/functions
    MStateApproach(Control* parent):MessState(MFSM_STATE_APPROACH,parent){}
    void Update(float dt);
    void Enter();
    void Exit();

    //callbacks for handling messages
    EvadeCallback      m_evadeCallback;
    IdleCallback       m_idleCallback;
    GetPowerupCallback m_getPowerupCallback;
};
#endif