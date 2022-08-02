#include "FSMMachine.h"


//---------------------------------------------------------
FSMMachine::FSMMachine(int type,Control* parent):
FSMState(type,parent)
{
	m_currentState = NULL;
	m_defaultState = NULL;
	m_goalState    = NULL;
}

//---------------------------------------------------------
void FSMMachine::UpdateMachine(float dt)
{
	//don't do anything if you have no states
	if(m_states.size() == 0 )
		return;

	//don't do anything if there's no current 
	//state, and no default state
	if(!m_currentState)
		m_currentState = m_defaultState;
	if(!m_currentState)
		return;

	//check for transitions, and then update
	int oldStateID = m_currentState->m_type;
	m_goalID = m_currentState->CheckTransitions();
	
	//switch if there was a transition
	if(m_goalID != oldStateID)
	{
		if(TransitionState(m_goalID))
		{
			m_currentState->Exit();
			m_currentState = m_goalState;
			m_currentState->Enter();
		}
	}
	m_currentState->Update(dt);	
	
}

//---------------------------------------------------------
void FSMMachine::AddState(FSMState* state)
{
	m_states.push_back(state);
}

//---------------------------------------------------------
bool FSMMachine::TransitionState(int goal)
{
	//don't do anything if you have no states
	if(m_states.size() == 0 )
		return false;
	
	//determine if we have state of type 'goal'
	//in the list, and switch to it, otherwise, quit out
	for(int i =0;i<m_states.size();i++)
	{
		if(m_states[i]->m_type == goal)
		{
			m_goalState = m_states[i];
			return true;
		}
	}
	return false;
}

//---------------------------------------------------------
void FSMMachine::Reset()
{
	Exit();
	if(m_currentState)
		m_currentState->Exit();
	m_currentState = m_defaultState;

	//init all the states
	for(int i =0;i<m_states.size();i++)
		m_states[i]->Init();

    //and now enter the m_defaultState, if any
    if(m_currentState)
        m_currentState->Enter();
    
}