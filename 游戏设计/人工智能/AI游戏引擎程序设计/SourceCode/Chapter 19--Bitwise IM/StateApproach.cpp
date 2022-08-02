#include "StateApproach.h"
#include "Ship.h"
#include "FSMAIControl.h"
#include "utility.h"


//---------------------------------------------------------
void StateApproach::Update(float dt)
{
    //turn and then thrust towards closest asteroid
    FSMAIControl* parent = (FSMAIControl*)m_parent;
    GameObj* asteroid = parent->m_nearestAsteroid;
    Ship*    ship     = parent->m_ship;
    Point3f deltaPos = asteroid->m_position - ship->m_position;
    deltaPos.Normalize();
    
    //add braking vec if you're going too fast
    float speed = ship->m_velocity.Length();
    if(speed > parent->m_maxSpeed)
        deltaPos += -ship->UnitVectorVelocity();
    
    //DOT out my velocity
    Point3f shpUnitVel = ship->UnitVectorVelocity();
    float dotVel = DOT(shpUnitVel,deltaPos);
    float proj = 1-dotVel;
    deltaPos -= proj*shpUnitVel;
    deltaPos.Normalize();
    
    //find new direction, and head to it
    float newDir = CALCDIR(deltaPos);
    float angDelta = CLAMPDIR180(ship->m_angle - newDir);
    if(fabsf(angDelta) <3 || (fabsf(angDelta)> 177 && ship->GetShotLevel()!=0))
    {
        //thrust
        ship->StopTurn();
        if(speed < parent->m_maxSpeed || parent->m_nearestAsteroidDist > 40)
            fabsf(angDelta)<3? ship->ThrustOn() : ship->ThrustReverse();
        else
            ship->ThrustOff();
    }
    else if(fabsf(angDelta)<=90 || ship->GetShotLevel()==0)
    {
        //turn when facing forwards
        if(angDelta >0)
            ship->TurnRight();
        else
            ship->TurnLeft();
    }
    else
    {
        //turn when facing rear
        if(angDelta<0)
            ship->TurnRight();
        else
            ship->TurnLeft();
    }
    
    parent->m_target->m_position = asteroid->m_position;
    parent->m_targetDir = newDir;
    parent->m_debugTxt = "Approach";
}

//---------------------------------------------------------
int StateApproach::CheckTransitions()
{
    FSMAIControl* parent = (FSMAIControl*)m_parent;
    if(parent->m_willCollide)
        return FSM_STATE_EVADE;

    if(parent->m_powerupNear && parent->m_nearestAsteroidDist > 
	   parent->m_nearestPowerupDist && parent->m_ship->GetShotLevel() < MAX_SHOT_LEVEL)
        return FSM_STATE_GETPOWERUP;

    if(!parent->m_nearestAsteroid || parent->m_nearestAsteroidDist < APPROACH_DIST)
        return FSM_STATE_IDLE;

    return FSM_STATE_APPROACH;  
}

//---------------------------------------------------------
void StateApproach::Exit()
{
    if(((FSMAIControl*)m_parent)->m_ship)
    {
        ((FSMAIControl*)m_parent)->m_ship->ThrustOff();
        ((FSMAIControl*)m_parent)->m_ship->StopTurn();
    }
}