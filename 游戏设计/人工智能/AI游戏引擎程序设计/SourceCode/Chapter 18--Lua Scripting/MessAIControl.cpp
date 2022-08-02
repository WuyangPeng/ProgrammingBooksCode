#include "MessAIControl.h"
#include "MessMachine.h"
#include "GameSession.h"
//#include "TestSession.h"
#include "utility.h"

#include "MStateApproach.h"
#include "MStateAttack.h"
#include "MStateEvade.h"
#include "MStateGetPowerup.h"
#include "MStateIdle.h"
#include "MessagePump.h"
#include "Target.h"

#include "luaPlusCD.h"
extern "C"
{
#include "lualib.h"
}

//---------------------------------------------------------
MessAIControl::MessAIControl(Ship* ship):
AIControl(ship)
{
    g_MessagePump.AddMessageToSystem(MESSAGE_WONT_COLLIDE);
    g_MessagePump.AddMessageToSystem(MESSAGE_WILL_COLLIDE);
    g_MessagePump.AddMessageToSystem(MESSAGE_NO_ASTEROIDS);
    g_MessagePump.AddMessageToSystem(MESSAGE_NO_POWERUPS);
    g_MessagePump.AddMessageToSystem(MESSAGE_ASTEROID_NEAR);
    g_MessagePump.AddMessageToSystem(MESSAGE_ASTEROID_FAR);
    g_MessagePump.AddMessageToSystem(MESSAGE_POWERUP_NEAR);
    g_MessagePump.AddMessageToSystem(MESSAGE_POWERUP_FAR);
    g_MessagePump.AddMessageToSystem(MESSAGE_SHIP_TOTAL_STOP);
    g_MessagePump.AddMessageToSystem(MESSAGE_CHANGE_STATE);
    
    //construct the state machine and add the necessary states
    m_machine = new MessMachine(MFSM_MACH_MAINSHIP,this);
    m_machine->AddState(new MStateApproach(this));
    m_machine->AddState(new MStateAttack(this));
    m_machine->AddState(new MStateEvade(this));
    m_machine->AddState(new MStateGetPowerup(this));
    MStateIdle* idle = new MStateIdle(this);
    m_machine->AddState(idle);
    m_machine->SetDefaultState(idle);
    m_machine->Reset();
    
    m_messReceiver = new MessageReceiver;
    
    //default values
    m_safetyRadius      = SAFETYRADUIS;
    m_powerupScanDist   = POWERUP_SCAN_DIST;
    m_maxSpeed          = MAI_MAX_SPEED_TRY;
    m_appDist           = MAPPROACH_DIST;  
    m_attDist           = MATTACK_DIST;
    m_powerupSeek       = true;
 
    m_luaState          = lua_open();
    lua_baselibopen(m_luaState);
    lua_settop(m_luaState,0);//clear the stack
    
    //bind const values to lua variables
    lua_pushnumber(m_luaState,MAX_SHOT_LEVEL);
    lua_setglobal(m_luaState,"gvMaxShotPower");
    lua_pushnumber(m_luaState,MFSM_STATE_APPROACH);
    lua_setglobal(m_luaState,"gsSTATEAPPROACH");
    lua_pushnumber(m_luaState,MFSM_STATE_ATTACK);
    lua_setglobal(m_luaState,"gsSTATEATTACK");
    lua_pushnumber(m_luaState,MFSM_STATE_EVADE);
    lua_setglobal(m_luaState,"gsSTATEEVADE");
    lua_pushnumber(m_luaState,MFSM_STATE_GETPOWERUP);
    lua_setglobal(m_luaState,"gsSTATEGETPOWERUP");
    lua_pushnumber(m_luaState,MFSM_STATE_IDLE);
    lua_setglobal(m_luaState,"gsSTATEIDLE");
    
    //bind state change function for lua to use
    lua_pushstring(m_luaState,"ChangeState");
    lua_pushdirectclosure(m_luaState,*this,&MessAIControl::SetMachineGoalState,0);
    lua_settable(m_luaState,LUA_GLOBALSINDEX);
    
}

//---------------------------------------------------------
MessAIControl::~MessAIControl()
{
    lua_close(m_luaState);
    if(m_target)
        delete m_target;
    delete m_messReceiver;
    //take down state machine
}

//---------------------------------------------------------
void MessAIControl::SetMachineGoalState(int state)
{
    m_machine->SetGoalID(state);
}

//---------------------------------------------------------
void MessAIControl::Init()
{
    m_willCollide  = false;
    m_powerupNear  = false;
    m_nearestAsteroid = NULL;
    m_nearestPowerup  = NULL;
    
    if(!m_target)
    {
        m_target = new Target;
        m_target->m_size = 1;
        Game.PostGameObj(m_target);
    }
}

//---------------------------------------------------------
void MessAIControl::Update(float dt)
{
    if(!m_ship)
    {
        m_machine->Reset();
        return;
    }

    UpdatePerceptions(dt);

    //update exposed lua variables
    lua_pushnumber(m_luaState,m_nearestPowerupDist);
    lua_setglobal(m_luaState,"gvDistPowerup");
    
    lua_pushnumber(m_luaState,m_nearestAsteroidDist);
    lua_setglobal(m_luaState,"gvDistAsteroid");
    
    lua_pushboolean(m_luaState,m_willCollide);
    lua_setglobal(m_luaState,"gvWillCollide");
    
    lua_pushboolean(m_luaState,m_isPowerup);
    lua_setglobal(m_luaState,"gvIsPowerup");
    
    lua_pushboolean(m_luaState,m_isAsteroid);
    lua_setglobal(m_luaState,"gvIsAsteroid");
    
    lua_pushnumber(m_luaState,m_ship->GetShotLevel());
    lua_setglobal(m_luaState,"gvShotPower");
    
    int numAsteroids = Game.GetNumGameObj(GameObj::OBJ_ASTEROID);
    lua_pushnumber(m_luaState,numAsteroids);
    lua_setglobal(m_luaState,"gvNumAsteroids");
    
    lua_pushboolean(m_luaState,m_ship->IsInvincible());
    lua_setglobal(m_luaState,"gvShipInvincible");
    
    //run lua script, which handles state transitions
    lua_dofile(m_luaState,"script1.lua");

    m_machine->UpdateMachine(dt);
}

//---------------------------------------------------------
void MessAIControl::UpdatePerceptions(float dt)
{
    float safeDist = m_safetyRadius;
    if(m_willCollide)
        safeDist *= 2*Game.m_timeScale;
    
    //store closest asteroid and powerup
    m_isPowerup = m_isAsteroid = false;
    m_nearestAsteroid = Game.GetClosestGameObj(m_ship,GameObj::OBJ_ASTEROID);
    m_nearestPowerup  = Game.GetClosestGameObj(m_ship,GameObj::OBJ_POWERUP);
    
    //reset distance to a large bogus number
    m_nearestAsteroidDist = 100000.0f;
    m_nearestPowerupDist  = 100000.0f;
    
    //asteroid collision determination
    m_willCollide = false;
    if(m_nearestAsteroid)
    {
        m_isAsteroid = true;
        float speed = m_ship->m_velocity.Length();
        m_nearestAsteroidDist = m_nearestAsteroid->m_position.Distance(m_ship->m_position);
        float dotVel;
        Point3f normDelta = m_nearestAsteroid->m_position - m_ship->m_position;
        normDelta.Normalize();
        float astSpeed = m_nearestAsteroid->m_velocity.Length();
        if(speed > astSpeed)
            dotVel  = DOT(m_ship->UnitVectorVelocity(),normDelta);
        else 
        {
            speed = astSpeed;
            dotVel = DOT(m_nearestAsteroid->UnitVectorVelocity(),-normDelta);
        }
        float spdAdj = LERP(speed/m_maxSpeed,0.0f,50.0f)*dotVel;
        float adjSafetyRadius = safeDist+spdAdj+m_nearestAsteroid->m_size;
        
        //if you're too close, and I'm heading somewhat towards you,
        //flag a collision
        if(m_nearestAsteroidDist <= adjSafetyRadius && dotVel > 0.4f)
            m_willCollide = true;
    }
    
    //powerup near determination
    if(m_nearestPowerup)
    {
        m_nearestPowerupDist = m_nearestPowerup->m_position.Distance(m_ship->m_position);
        m_isPowerup = true;
    }
}


