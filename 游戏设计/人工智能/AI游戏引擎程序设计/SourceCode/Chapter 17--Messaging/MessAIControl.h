#ifndef __MESSAICONTROL
#define __MESSAICONTROL

#include "AIControl.h"
#include "Callback.h"
#include "MessagePump.h"

using namespace std;

class Ship;
class MessMachine;
class Message;
class GameObj;

#define SAFETYRADUIS        15.0f
#define POWERUP_SCAN_DIST  180.0f
#define MAI_MAX_SPEED_TRY   80.0f
#define MAPPROACH_DIST     240.0f
#define MATTACK_DIST       220.0f


//main class declaration
class MessAIControl: public AIControl
{
public:
    //constructor/functions
    MessAIControl(Ship* ship = NULL);
    ~MessAIControl();
    void Update(float dt);
    void UpdatePerceptions(float dt);
    void Init();
    void SetMachineGoalState(int state);
    int  GetMessageID()                {return m_messReceiver->m_ID;}
    
    //perception data 
    //(public so that states can share it)
    GameObj*    m_nearestAsteroid;
    GameObj*    m_nearestPowerup;
    bool        m_isAsteroid;
    bool        m_isPowerup;
    float       m_nearestAsteroidDist;
    float       m_nearestPowerupDist;
    bool        m_willCollide;
    bool        m_powerupNear;

    //scripted data
    float       m_safetyRadius;
    float       m_powerupScanDist;
    float       m_maxSpeed;
    float       m_appDist;
    float       m_attDist;
    bool        m_powerupSeek;
    
    
private:
    //data
    MessMachine* m_machine;
    MessageReceiver* m_messReceiver;

};
#endif