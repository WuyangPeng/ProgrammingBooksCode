#include "MessMachine.h"
#include "MessagePump.h"

//---------------------------------------------------------
void ChangeStateCallback::function(void* parent, Message* msg)
{
    int newState = ((DataMessage<int>*)msg)->m_dataStorage;
    ((MessMachine*)parent)->SetGoalID(newState);
}

//---------------------------------------------------------
MessMachine::MessMachine(int type,Control* parent):
MessState(type,parent)
{
	m_currentState = NULL;
	m_defaultState = NULL;
	m_goalState    = NULL;

    g_MessagePump.RegisterForMessage(MESSAGE_CHANGE_STATE,this,GetMessageID(),m_changeStateCallback);
}

//---------------------------------------------------------
void MessMachine::UpdateMachine(float dt)
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
void MessMachine::AddState(MessState* state)
{
	m_states.push_back(state);
}

//---------------------------------------------------------
bool MessMachine::TransitionState(int goal)
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
void MessMachine::Reset()
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