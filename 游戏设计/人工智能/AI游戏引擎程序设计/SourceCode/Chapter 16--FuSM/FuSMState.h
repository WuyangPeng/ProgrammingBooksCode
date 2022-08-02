#ifndef __FUSMSTATE
#define __FUSMSTATE

#include "FuSM.h"
#include <stdlib.h>

class Control;

class FuSMState
{
public:
    //constructor/functions
    FuSMState(int type = FUSM_STATE_NONE,Control* parent = NULL){m_type = type;m_parent = parent;m_activationLevel = 0.0f;}
    virtual void Update(float dt)   {}
    virtual void Enter()            {}
    virtual void Exit()             {}
    virtual void Init()             {m_activationLevel = 0.0f;}
    virtual float CalculateActivation() {return m_activationLevel;}

    virtual CheckLowerBound(float lbound = 0.0f) {if(m_activationLevel < lbound) m_activationLevel = lbound;}
    virtual CheckUpperBound(float ubound = 1.0f) {if(m_activationLevel > ubound) m_activationLevel = ubound;}
    virtual CheckBounds(float lb = 0.0f,float ub = 1.0f) {CheckLowerBound(lb);CheckUpperBound(ub);}

    //data
    Control*   m_parent;
    int        m_type;
    float      m_activationLevel;
};
#endif