#ifndef __STATEGETPOWERUP
#define __STATEGETPOWERUP

#include "FSMState.h"

class StateGetPowerup : public FSMState
{
public:
    //constructor/functions
    StateGetPowerup(Control* parent):FSMState(FSM_STATE_GETPOWERUP,parent){}
    void Update(float dt);
    int CheckTransitions();
    void Exit();
};
#endif