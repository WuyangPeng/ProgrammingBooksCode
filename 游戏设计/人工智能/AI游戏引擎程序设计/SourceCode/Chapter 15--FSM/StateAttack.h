#ifndef __STATEATTACK
#define __STATEATTACK

#include "FSMState.h"

class StateAttack : public FSMState
{
public:
    //constructor/functions
    StateAttack(Control* parent):FSMState(FSM_STATE_ATTACK,parent){}
    void Update(float dt);
    int CheckTransitions();
    void Exit();
    
};
#endif