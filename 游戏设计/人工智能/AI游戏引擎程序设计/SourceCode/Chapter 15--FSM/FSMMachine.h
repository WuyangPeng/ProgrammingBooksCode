#ifndef __FSMMACHINE
#define __FSMMACHINE

#include "FSMState.h"
#pragma warning(disable: 4786)
#include <vector>


class FSMMachine: public FSMState
{
public:
    //constructor/functions
    FSMMachine(int type = FSM_MACH_NONE,Control* parent = NULL);
    virtual void UpdateMachine(float dt);
    virtual void AddState(FSMState* state);
    virtual void SetDefaultState(FSMState* state) {m_defaultState = state;}
    virtual void SetGoalID(int goal) {m_goalID = goal;}
    virtual bool TransitionState(int goal);
    virtual void Reset();
    
    //data
    int m_type;
protected:
    std::vector<FSMState*> m_states;
    FSMState* m_currentState;
    FSMState* m_defaultState;
    FSMState* m_goalState;
    int		  m_goalID;
};
#endif