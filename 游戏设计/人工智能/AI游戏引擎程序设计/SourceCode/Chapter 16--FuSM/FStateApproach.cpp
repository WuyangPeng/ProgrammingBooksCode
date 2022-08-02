#include "FStateApproach.h"
#include "Ship.h"
#include "FuSMAIControl.h"
#include "utility.h"


//---------------------------------------------------------
void FStateApproach::Update(float dt)
{
    //turn and then thrust towards closest asteroid
    FuSMAIControl* parent = (FuSMAIControl*)m_parent;
    GameObj* asteroid = parent->m_nearestAsteroid;
    Ship*    ship     = parent->m_ship;
    Point3f deltaPos = asteroid->m_position - ship->m_position;
    
    //move there
    ship->AGThrustAccumulate(deltaPos*m_activationLevel);
    
    parent->m_target->m_position = asteroid->m_position;
    parent->m_debugTxt = "Approach";
}

//---------------------------------------------------------
float FStateApproach::CalculateActivation()
{
    FuSMAIControl* parent = (FuSMAIControl*)m_parent;
    if(!parent->m_nearestAsteroid)
        m_activationLevel = 0.0f;
    else
        m_activationLevel = (parent->m_nearestAsteroidDist-FU_APPROACH_DIST)/FU_APPROACH_DIST;
    CheckBounds();
    return m_activationLevel;
}

//---------------------------------------------------------
void FStateApproach::Exit()
{
    if(((FuSMAIControl*)m_parent)->m_ship)
        ((FuSMAIControl*)m_parent)->m_ship->StopAGThrust();
}