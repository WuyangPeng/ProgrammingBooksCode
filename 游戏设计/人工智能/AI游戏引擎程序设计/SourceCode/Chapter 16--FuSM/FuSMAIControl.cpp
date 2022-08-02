#include "FuSMAIControl.h"
#include "FuSMMachine.h"
#include "GameSession.h"
//#include "TestSession.h"
#include "utility.h"

#include "FStateApproach.h"
#include "FStateAttack.h"
#include "FStateEvade.h"
#include "FStateGetPowerup.h"

#include "Target.h"


//---------------------------------------------------------
FuSMAIControl::FuSMAIControl(Ship* ship):
AIControl(ship)
{
    //construct the state machine and add the necessary states
    m_machine = new FuSMMachine(FUSM_MACH_SAUCER,this);
    m_machine->AddState(new FStateApproach(this));
    m_machine->AddState(new FStateAttack(this));
    m_machine->AddState(new FStateEvade(this));
    m_machine->AddState(new FStateGetPowerup(this));
    m_machine->Reset();
}

//---------------------------------------------------------
void FuSMAIControl::Init()
{
    m_willCollide  = false;
    m_nearestAsteroid = NULL;
    m_nearestPowerup  = NULL;
    m_safetyRadius    = 15.0f;

    if(!m_target)
    {
        m_target = new Target;
        m_target->m_size = 1;
        Game.PostGameObj(m_target);
    }
}

//---------------------------------------------------------
void FuSMAIControl::Update(float dt)
{
    if(!m_ship)
    {
        m_machine->Reset();
        return;
    }
    
    UpdatePerceptions(dt);
    m_machine->UpdateMachine(dt);
}

//---------------------------------------------------------
void FuSMAIControl::UpdatePerceptions(float dt)
{
    if(m_willCollide)
        m_safetyRadius = 30.0f;
    else
        m_safetyRadius = 15.0f;
    
    //store closest asteroid and powerup
    m_nearestAsteroid = NULL;
    m_nearestPowerup  = NULL;
    m_nearestAsteroid = Game.GetClosestGameObj(m_ship,GameObj::OBJ_ASTEROID);
    if(m_ship->GetShotLevel() < MAX_SHOT_LEVEL)
        m_nearestPowerup  = Game.GetClosestGameObj(m_ship,GameObj::OBJ_POWERUP);
    
    //asteroid collision determination
    m_willCollide = false;
    if(m_nearestAsteroid)
    {
        m_nearestAsteroidDist = m_nearestAsteroid->m_position.Distance(m_ship->m_position);
        float adjSafetyRadius = m_safetyRadius+m_nearestAsteroid->m_size;
        
        //if you're too close,
        //flag a collision
        if(m_nearestAsteroidDist <= adjSafetyRadius )
            m_willCollide = true;
    }

    //powerup near determination
    if(m_nearestPowerup)
        m_nearestPowerupDist = m_nearestPowerup->m_position.Distance(m_ship->m_position); 
}


