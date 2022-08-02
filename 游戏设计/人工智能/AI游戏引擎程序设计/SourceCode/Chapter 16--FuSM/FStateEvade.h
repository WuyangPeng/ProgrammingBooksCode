#ifndef __FSTATEEVADE
#define __FSTATEEVADE

#include "FuSMState.h"

class FStateEvade : public FuSMState
{
public:
    //constructor/functions
    FStateEvade(Control* parent):FuSMState(FUSM_STATE_EVADE,parent){}
    void Update(float dt);
    float CalculateActivation();
    void Exit();

};
#endif