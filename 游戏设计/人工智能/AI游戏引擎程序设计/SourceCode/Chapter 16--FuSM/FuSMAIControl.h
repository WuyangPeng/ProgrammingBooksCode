#ifndef __FUSMAICONTROL
#define __FUSMAICONTROL

#include "AIControl.h"

class Ship;
class FuSMMachine;
class GameObj;

#define FU_POWERUP_SCAN_DIST 250.0f
#define FU_APPROACH_DIST     120.0f
#define FU_ATTACK_DIST       240.0f

class FuSMAIControl: public AIControl
{
public:
    //constructor/functions
    FuSMAIControl(Ship* ship = NULL);
    void Update(float dt);
    void UpdatePerceptions(float dt);
    void Init();
    
    //perception data 
    //(public so that states can share it)
    GameObj*    m_nearestAsteroid;
    GameObj*    m_nearestPowerup;
    float       m_nearestAsteroidDist;
    float       m_nearestPowerupDist;
    bool        m_willCollide;
    float       m_safetyRadius;
    
private:
    //data
    FuSMMachine* m_machine;
};
#endif