#include "StateAttack.h"
#include "Ship.h"
#include "FSMAIControl.h"
#include "utility.h"


//---------------------------------------------------------
void StateAttack::Update(float dt)
{
    //turn towards closest asteroid's future position, and then fire
    FSMAIControl* parent = (FSMAIControl*)m_parent;
    GameObj* asteroid = parent->m_nearestAsteroid;
    Ship*    ship     = parent->m_ship;
    
    if(!asteroid)
        return;
    
    Point3f futureAstPosition = asteroid->m_position;
    Point3f deltaPos = futureAstPosition - ship->m_position;
    float dist  = deltaPos.Length();
    float time = dist/BULLET_SPEED;
    futureAstPosition += time*asteroid->m_velocity;
    Point3f deltaFPos = futureAstPosition - ship->m_position;
    deltaFPos.Normalize();

    float newDir     = CALCDIR(deltaFPos);
    float angDelta   = CLAMPDIR180(ship->GetClosestGunAngle(newDir) - newDir);
    float dangerAdjAngle = ((1.0f - parent->m_nearestAsteroidDist/ APPROACH_DIST)*5.0f) + 1.0f;

    if(angDelta >dangerAdjAngle)
        ship->TurnRight();
    else if(angDelta < -dangerAdjAngle)
        ship->TurnLeft();
    else
    {
        ship->StopTurn();
        ship->Shoot();
    }
    
    parent->m_target->m_position = futureAstPosition;
    parent->m_targetDir = newDir;
    parent->m_debugTxt = "Attack";
}

//---------------------------------------------------------
int StateAttack::CheckTransitions()
{
    FSMAIControl* parent = (FSMAIControl*)m_parent;
    if(parent->m_willCollide)
        return FSM_STATE_EVADE;

    if(parent->m_powerupNear && parent->m_nearestAsteroidDist > 
       parent->m_nearestPowerupDist && parent->m_ship->GetShotLevel() < MAX_SHOT_LEVEL)
        return FSM_STATE_GETPOWERUP;
    
    if(!parent->m_nearestAsteroid || parent->m_nearestAsteroidDist > APPROACH_DIST)
        return FSM_STATE_IDLE;

    return FSM_STATE_ATTACK;    
}

//---------------------------------------------------------
void StateAttack::Exit()
{
    if(((FSMAIControl*)m_parent)->m_ship)
        ((FSMAIControl*)m_parent)->m_ship->StopTurn();
}