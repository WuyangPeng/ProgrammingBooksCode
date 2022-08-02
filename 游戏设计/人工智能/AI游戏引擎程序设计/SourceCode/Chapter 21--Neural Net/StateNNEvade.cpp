#include "StateNNEvade.h"
#include "Ship.h"
#include "NNAIControl.h"
#include "utility.h"


//---------------------------------------------------------
void StateNNEvade::Update(float dt)
{
    NNAIControl* parent = (NNAIControl*)m_parent;
    Ship* ship = parent->m_ship;
    
    if(parent->m_shouldThrust)//thrust
        ship->ThrustOn();
    else
        ship->ThrustOff();

    if(parent->m_shouldTurnRight)
        ship->TurnRight();
    else if(parent->m_shouldTurnLeft)
        ship->TurnLeft();
    else
        ship->StopTurn();

    parent->m_debugTxt = "Evade";
}

//---------------------------------------------------------
int StateNNEvade::CheckTransitions()
{
    NNAIControl* parent = (NNAIControl*)m_parent;

    if(!parent->m_willCollide)
        return FSM_STATE_IDLE;

    return FSM_STATE_EVADE;
}

//---------------------------------------------------------
void StateNNEvade::Exit()
{
    if(((NNAIControl*)m_parent)->m_ship)
    {
        ((NNAIControl*)m_parent)->m_ship->ThrustOff();
        ((NNAIControl*)m_parent)->m_ship->StopTurn();
    }
}

