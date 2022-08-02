#include "FStateEvade.h"
#include "Ship.h"
#include "FuSMAIControl.h"
#include "utility.h"


//---------------------------------------------------------
void FStateEvade::Update(float dt)
{
    //evade by going away from the closest asteroid
    FuSMAIControl* parent = (FuSMAIControl*)m_parent;
    GameObj* asteroid = parent->m_nearestAsteroid;
    Ship*    ship     = parent->m_ship;
    Point3f vecBrake = ship->m_position - asteroid->m_position;
    
    ship->AGThrustAccumulate(vecBrake*m_activationLevel);
    
    parent->m_target->m_position = parent->m_nearestAsteroid->m_position;
    parent->m_debugTxt = "Evade";
}

//---------------------------------------------------------
float FStateEvade::CalculateActivation()
{
    FuSMAIControl* parent = (FuSMAIControl*)m_parent;
    if(!parent->m_nearestAsteroid)
        m_activationLevel = 0.0f;
    else
        m_activationLevel = 1.0f - (parent->m_nearestAsteroidDist-parent->m_nearestAsteroid->m_size)/parent->m_safetyRadius;
    CheckBounds();
    return m_activationLevel;
}

//---------------------------------------------------------
void FStateEvade::Exit()
{
    if(((FuSMAIControl*)m_parent)->m_ship)
        ((FuSMAIControl*)m_parent)->m_ship->StopAGThrust();
}