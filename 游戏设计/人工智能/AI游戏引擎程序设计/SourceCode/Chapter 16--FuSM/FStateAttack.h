#ifndef __FSTATEATTACK
#define __FSTATEATTACK

#include "FuSMState.h"

class FStateAttack : public FuSMState
{
public:
    //constructor/functions
    FStateAttack(Control* parent):FuSMState(FUSM_STATE_ATTACK,parent){}
    void Update(float dt);
    float CalculateActivation();
    
};
#endif