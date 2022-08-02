#ifndef __MSTATEIDLE
#define __MSTATEIDLE

#include "MessState.h"
#include "MCallbacks.h"

class Control;

class MStateIdle : public MessState
{
public:
    //constructor/functions
    MStateIdle(Control* control):MessState(MFSM_STATE_IDLE,control){}
    void Enter();
    void Exit();
    void Update(float dt);

    EvadeCallback      m_evadeCallback;
    ApproachCallback   m_approachCallback;
    AttackCallback     m_attackCallback;
    GetPowerupCallback m_getPowerupCallback;

};
#endif