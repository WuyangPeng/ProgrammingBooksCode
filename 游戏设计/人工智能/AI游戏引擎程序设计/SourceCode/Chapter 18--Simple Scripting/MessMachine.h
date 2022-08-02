#ifndef __MESSMACHINE
#define __MESSMACHINE

#include "MessState.h"
#pragma warning(disable: 4786)
#include <vector>

//callbacks for handling messages
class ChangeStateCallback : public Callback   
{       
    void function(void* parent, Message* msg);
};

class MessMachine: public MessState
{
public:
	//constructor/functions
	MessMachine(int type = MFSM_MACH_NONE,Control* parent = NULL);
	virtual void UpdateMachine(float dt);
	virtual void AddState(MessState* state);
	virtual void SetDefaultState(MessState* state) {m_defaultState = state;}
	virtual void SetGoalID(int goal) {m_goalID = goal;}
	virtual bool TransitionState(int goal);
	virtual void Reset();
	
	//data
	int m_type;
protected:
	std::vector<MessState*> m_states;
	MessState* m_currentState;
	MessState* m_defaultState;
	MessState* m_goalState;
	int		   m_goalID;
    ChangeStateCallback m_changeStateCallback;
};
#endif