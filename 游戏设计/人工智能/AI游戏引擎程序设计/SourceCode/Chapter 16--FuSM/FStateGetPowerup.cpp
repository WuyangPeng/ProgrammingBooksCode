#include "FStateGetPowerup.h"
#include "Ship.h"
#include "FuSMAIControl.h"
#include "utility.h"


//---------------------------------------------------------
void FStateGetPowerup::Update(float dt)
{
    FuSMAIControl* parent = (FuSMAIControl*)m_parent;
    GameObj* powerup = parent->m_nearestPowerup;
    Ship*    ship     = parent->m_ship;
    
    Point3f deltaPos = powerup->m_position - ship->m_position;
    
    ship->AGThrustAccumulate(deltaPos*m_activationLevel);
    ship->TractorBeamOn(-deltaPos);
    
    parent->m_target->m_position = powerup->m_position;
    parent->m_debugTxt = "GetPowerup";
}

//---------------------------------------------------------
float FStateGetPowerup::CalculateActivation()
{
    FuSMAIControl* parent = (FuSMAIControl*)m_parent;
    if(!parent->m_nearestPowerup)
        m_activationLevel = 0.0f;
    else
        m_activationLevel = 1.0f - (parent->m_nearestPowerupDist-parent->m_nearestPowerup->m_size)/FU_POWERUP_SCAN_DIST;
    CheckBounds();
    return m_activationLevel;
}

//---------------------------------------------------------
void FStateGetPowerup::Exit()
{
    if(((FuSMAIControl*)m_parent)->m_ship)
    {
        ((FuSMAIControl*)m_parent)->m_ship->StopAGThrust();
        ((FuSMAIControl*)m_parent)->m_ship->StopTractorBeam();
    }
}