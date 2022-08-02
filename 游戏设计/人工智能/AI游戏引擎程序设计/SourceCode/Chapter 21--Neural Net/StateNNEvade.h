#pragma once

#include "FSMState.h"

class StateNNEvade : public FSMState
{
public:
    //constructor/functions
    StateNNEvade(Control* parent):FSMState(FSM_STATE_EVADE,parent){}
    void Update(float dt);
    int CheckTransitions();
    void Exit();
};
