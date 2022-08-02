#ifndef __FSMSTATE
#define __FSMSTATE

#include "FSM.h"
#include <stdlib.h>

class Control;

class FSMState
{
public:
	//constructor/functions
	FSMState(int type = FSM_STATE_NONE,Control* parent = NULL){m_type = type;m_parent = parent;}
    virtual void Enter()            {}
	virtual void Exit()             {}
	virtual void Update(float dt)   {}
	virtual void Init()             {}
	virtual int  CheckTransitions() {return FSM_STATE_NONE;}

	//data
	Control*   m_parent;
	int        m_type;
};
#endif