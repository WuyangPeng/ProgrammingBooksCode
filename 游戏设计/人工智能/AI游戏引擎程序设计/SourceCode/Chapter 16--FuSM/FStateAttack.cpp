#include "FStateAttack.h"
#include "Ship.h"
#include "FuSMAIControl.h"
#include "utility.h"


//---------------------------------------------------------
void FStateAttack::Update(float dt)
{
    //turn towards closest asteroid's future position, and then fire
    FuSMAIControl* parent = (FuSMAIControl*)m_parent;
    GameObj* asteroid = parent->m_nearestAsteroid;
    Ship*    ship     = parent->m_ship;
    
    Point3f futureAstPosition = asteroid->m_position;
    Point3f deltaPos = futureAstPosition - ship->m_position;
    float dist  = deltaPos.Length();
    float time = dist/BULLET_SPEED;
    futureAstPosition += time*asteroid->m_velocity;
    Point3f deltaFPos = futureAstPosition - ship->m_position;

    float newDir = CALCDIR(deltaFPos);
    ship->Shoot(newDir);
    
    parent->m_target->m_position = futureAstPosition;
    parent->m_debugTxt = "Attack";
}

//---------------------------------------------------------
float FStateAttack::CalculateActivation()
{
    FuSMAIControl* parent = (FuSMAIControl*)m_parent;
    if(!parent->m_nearestAsteroid)
        m_activationLevel = 0.0f;
    else
        m_activationLevel = parent->m_nearestAsteroid && parent->m_nearestAsteroidDist < FU_ATTACK_DIST;    
    CheckBounds();
    return m_activationLevel;
}
