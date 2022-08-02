#ifndef __MSTATEATTACK
#define __MSTATEATTACK

#include "MessState.h"
#include "MCallbacks.h"

class MStateAttack : public MessState
{
public:
    //constructor/functions
    MStateAttack(Control* parent):MessState(MFSM_STATE_ATTACK,parent){}
    void Update(float dt);
    void Enter();
    void Exit();

    //callbacks for handling messages
    EvadeCallback      m_evadeCallback;
    IdleCallback       m_idleCallback;
    GetPowerupCallback m_getPowerupCallback;
};
#endif