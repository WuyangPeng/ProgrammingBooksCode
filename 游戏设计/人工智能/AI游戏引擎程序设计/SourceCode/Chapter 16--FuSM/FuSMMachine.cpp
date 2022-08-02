#include "FuSMMachine.h"


//---------------------------------------------------------
FuSMMachine::FuSMMachine(int type,Control* parent):
FuSMState(type,parent)
{
}

//---------------------------------------------------------
void FuSMMachine::UpdateMachine(float dt)
{
    //don't do anything if you have no states
    if(m_states.size() == 0)
        return;
    
    //check for activations, and then update
    m_activatedStates.clear();
    std::vector<FuSMState*> nonActiveStates;
    for(int i =0;i<m_states.size();i++)
    {
        if(m_states[i]->CalculateActivation() > 0)
            m_activatedStates.push_back(m_states[i]);
        else
            nonActiveStates.push_back(m_states[i]);
    }

    //Exit all non active states for cleanup
    if(nonActiveStates.size() != 0)
    {
        for(int i =0;i<nonActiveStates.size();i++)
            nonActiveStates[i]->Exit(); 
    }
    
    //Update all activated states
    if(m_activatedStates.size() != 0)
    {
        for(int i =0;i<m_activatedStates.size();i++)
            m_activatedStates[i]->Update(dt);   
    }
}

//---------------------------------------------------------
void FuSMMachine::AddState(FuSMState* state)
{
	m_states.push_back(state);
}

//---------------------------------------------------------
bool FuSMMachine::IsActive(FuSMState *state)
{
    if(m_activatedStates.size() != 0)
    {
        for(int i =0;i<m_activatedStates.size();i++)
            if(m_activatedStates[i] == state)
				return true;   
    }
	return false;
}

//---------------------------------------------------------
void FuSMMachine::Reset()
{
	//exit and init all the states
	for(int i =0;i<m_states.size();i++)
    {
        m_states[i]->Exit();
        m_states[i]->Init();
    }
}