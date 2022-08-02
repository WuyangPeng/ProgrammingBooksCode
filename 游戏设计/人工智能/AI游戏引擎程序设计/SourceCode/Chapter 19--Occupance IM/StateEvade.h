#pragma once

#include "FSMState.h"

class StateEvade : public FSMState
{
public:
    //constructor/functions
    StateEvade(Control* parent):FSMState(FSM_STATE_EVADE,parent){}
    void Update(float dt);
    int CheckTransitions();
    void Exit();

};
