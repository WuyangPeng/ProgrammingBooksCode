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

#include "Tokens.h"
#include "Parser.h"

//---------------------------------------------------------
void PowerupDistCallback::function(void* parent, Message* msg)
{
    float powDist = ((DataMessage<float>*)msg)->m_dataStorage;
    ((MessAIControl*)parent)->m_powerupScanDist = powDist;
}
//---------------------------------------------------------
void PowerupSeekCallback::function(void* parent, Message* msg)
{
    bool seekPow = ((DataMessage<bool>*)msg)->m_dataStorage;
    ((MessAIControl*)parent)->m_powerupSeek = seekPow;
}
//---------------------------------------------------------
void AppDistCallback::function(void* parent, Message* msg)
{
    float appDist = ((DataMessage<float>*)msg)->m_dataStorage;
    ((MessAIControl*)parent)->m_appDist = appDist;
}
//---------------------------------------------------------
void AttDistCallback::function(void* parent, Message* msg)
{
    float attDist = ((DataMessage<float>*)msg)->m_dataStorage;
    ((MessAIControl*)parent)->m_attDist = attDist;
}
//---------------------------------------------------------
void SafeRadiusCallback::function(void* parent, Message* msg)
{
    float safeRad = ((DataMessage<float>*)msg)->m_dataStorage;
    ((MessAIControl*)parent)->m_safetyRadius = safeRad;
}
//---------------------------------------------------------
void MaxSpeedCallback::function(void* parent, Message* msg)
{
    float mxSpeed= ((DataMessage<float>*)msg)->m_dataStorage;
    ((MessAIControl*)parent)->m_maxSpeed = mxSpeed;
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
    
    //script parsing messages
    g_MessagePump.AddMessageToSystem(MESSAGE_TOKEN_PSCAN);
    g_MessagePump.AddMessageToSystem(MESSAGE_TOKEN_MAXSPEED);
    g_MessagePump.AddMessageToSystem(MESSAGE_TOKEN_APDIST);
    g_MessagePump.AddMessageToSystem(MESSAGE_TOKEN_ATDIST);
    g_MessagePump.AddMessageToSystem(MESSAGE_TOKEN_SAFERAD);
    g_MessagePump.AddMessageToSystem(MESSAGE_TOKEN_POWSEEK);
    
    g_MessagePump.RegisterForMessage(MESSAGE_TOKEN_PSCAN,this,GetMessageID(),m_powerupDistCallback);
    g_MessagePump.RegisterForMessage(MESSAGE_TOKEN_MAXSPEED,this,GetMessageID(),m_maxSpeedCallback);
    g_MessagePump.RegisterForMessage(MESSAGE_TOKEN_APDIST,this,GetMessageID(),m_appDistCallback);
    g_MessagePump.RegisterForMessage(MESSAGE_TOKEN_ATDIST,this,GetMessageID(),m_attDistCallback);
    g_MessagePump.RegisterForMessage(MESSAGE_TOKEN_SAFERAD,this,GetMessageID(),m_safeRadiusCallback);
    g_MessagePump.RegisterForMessage(MESSAGE_TOKEN_POWSEEK,this,GetMessageID(),m_powerupSeekCallback);
    
    //default values
    m_safetyRadius      = SAFETYRADUIS;
    m_powerupScanDist   = POWERUP_SCAN_DIST;
    m_maxSpeed          = MAI_MAX_SPEED_TRY;
    m_appDist           = MAPPROACH_DIST;  
    m_attDist           = MATTACK_DIST;
    m_powerupSeek       = true;

    Init();
    
}

//---------------------------------------------------------
MessAIControl::~MessAIControl()
{
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
    
    //parse the script file
    TokenList tokens;
    tokens.push_back(new TokenPowerupSeek);
    tokens.push_back(new TokenPowerupScan);
    tokens.push_back(new TokenMaxSpeed);
    tokens.push_back(new TokenApproachDist);
    tokens.push_back(new TokenAttackDist);
    tokens.push_back(new TokenSafeRadius);
    Parser parser(&tokens);
    parser.ParseFile("test2.txt");
    
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

    m_machine->UpdateMachine(dt);
}

//---------------------------------------------------------
void MessAIControl::UpdatePerceptions(float dt)
{
    float safeDist = m_safetyRadius;
    if(m_willCollide)
        safeDist *= 2;
    
    //store closest asteroid and powerup
    m_isPowerup = m_isAsteroid = false;
    m_nearestAsteroid = Game.GetClosestGameObj(m_ship,GameObj::OBJ_ASTEROID);
    if(m_ship->GetShotLevel() < MAX_SHOT_LEVEL && m_powerupSeek)
        m_nearestPowerup  = Game.GetClosestGameObj(m_ship,GameObj::OBJ_POWERUP);
    else
        m_nearestPowerup = NULL;
    
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
        {
            m_willCollide = true;
            Message* msg = new Message(MESSAGE_WILL_COLLIDE);
            g_MessagePump.SendMessage(msg);
        }
        else
        {
            Message* msg = new Message(MESSAGE_WONT_COLLIDE);
            g_MessagePump.SendMessage(msg);
        }
        
    }
    else
    {
        Message* msg = new Message(MESSAGE_NO_ASTEROIDS);
        g_MessagePump.SendMessage(msg);
    }
    
    //powerup near determination
    if(m_nearestPowerup)
    {
        m_nearestPowerupDist = m_nearestPowerup->m_position.Distance(m_ship->m_position);
        m_isPowerup = true;
    }
    else
    {
        Message* msg = new Message(MESSAGE_NO_POWERUPS);
        g_MessagePump.SendMessage(msg);
    }
    
    //arbitrate asteroid/powerup near messages
    if(m_isPowerup && m_nearestAsteroidDist > 
        m_nearestPowerupDist)
    {
        Message* msg = new Message(MESSAGE_POWERUP_NEAR);
        g_MessagePump.SendMessage(msg);
    }
    else if(m_nearestAsteroid)
    {
        if(m_nearestAsteroidDist > MAPPROACH_DIST)
        {
            Message* msg = new Message(MESSAGE_ASTEROID_FAR);
            g_MessagePump.SendMessage(msg);
        }
        else
        {
            Message* msg =new Message(MESSAGE_ASTEROID_NEAR);
            g_MessagePump.SendMessage(msg);
        }
    }


}


