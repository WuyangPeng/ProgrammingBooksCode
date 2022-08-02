#ifndef __FUSMMACHINE
#define __FUSMMACHINE

#include "FuSMState.h"
#pragma warning(disable: 4786)
#include <vector>


class FuSMMachine: public FuSMState
{
public:
    //constructor/functions
    FuSMMachine(int type = FUSM_MACH_NONE,Control* parent = NULL);
    virtual void UpdateMachine(float dt);
    virtual void AddState(FuSMState* state);
	virtual bool IsActive(FuSMState *state);
    virtual void Reset();
    
    //data
    int m_type;
protected:
    std::vector<FuSMState*> m_states;
    std::vector<FuSMState*> m_activatedStates;
};
#endif