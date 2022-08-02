#ifndef __STATEAPPROACH
#define __STATEAPPROACH

#include "FSMState.h"

class StateApproach : public FSMState
{
public:
    //constructor/functions
    StateApproach(Control* parent):FSMState(FSM_STATE_APPROACH,parent){}
    void Update(float dt);
    int CheckTransitions();
    void Exit();
};
#endif