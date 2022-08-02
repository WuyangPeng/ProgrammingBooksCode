#ifndef __STATEIDLE
#define __STATEIDLE

#include "FSMState.h"

class StateIdle : public FSMState
{
public:
    //constructor/functions
    StateIdle(Control* parent):FSMState(FSM_STATE_IDLE,parent){}
    void Update(float dt);
    int CheckTransitions();

};
#endif