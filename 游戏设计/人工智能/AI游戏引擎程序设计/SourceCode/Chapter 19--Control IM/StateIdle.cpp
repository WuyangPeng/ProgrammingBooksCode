#include "StateIdle.h"
#include "Ship.h"
#include "FSMAIControl.h"
#include "utility.h"


//---------------------------------------------------------
void StateIdle::Update(float dt)
{
    //Do nothing
    FSMAIControl* parent = (FSMAIControl*)m_parent;
    parent->m_debugTxt = "Idle";
}

//---------------------------------------------------------
int StateIdle::CheckTransitions()
{
    FSMAIControl* parent = (FSMAIControl*)m_parent;

    if(parent->m_willCollide)
        return FSM_STATE_EVADE;

    if(parent->m_nearestAsteroid)
    {
        if(parent->m_nearestAsteroidDist > APPROACH_DIST)
            return FSM_STATE_APPROACH;
        else
            return FSM_STATE_ATTACK;
    }

    if(parent->m_nearestPowerup && 
	   parent->m_ship->GetShotLevel() < MAX_SHOT_LEVEL)
        return FSM_STATE_GETPOWERUP;

    return FSM_STATE_IDLE;
}