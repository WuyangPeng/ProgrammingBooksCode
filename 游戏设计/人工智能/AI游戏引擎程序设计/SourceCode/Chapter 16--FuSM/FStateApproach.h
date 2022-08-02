#ifndef __FSTATEAPPROACH
#define __FSTATEAPPROACH

#include "FuSMState.h"

class FStateApproach : public FuSMState
{
public:
    //constructor/functions
    FStateApproach(Control* parent):FuSMState(FUSM_STATE_APPROACH,parent){}
    void Update(float dt);
    float CalculateActivation();
    void Exit();
};
#endif