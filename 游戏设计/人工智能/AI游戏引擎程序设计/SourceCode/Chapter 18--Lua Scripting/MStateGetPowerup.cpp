#include "MStateGetPowerup.h"
#include "Ship.h"
#include "MessAIControl.h"
#include "utility.h"
#include "MessagePump.h"


//---------------------------------------------------------
void MStateGetPowerup::Update(float dt)
{
    MessAIControl* parent = (MessAIControl*)m_parent;
    GameObj* powerup = parent->m_nearestPowerup;
    Ship*    ship     = parent->m_ship;
    
    if(!powerup)
        return;
    
    //find future position of powerup
    Point3f futurePowPosition = powerup->m_position;
    Point3f deltaPos = futurePowPosition - ship->m_position;
    float dist  = deltaPos.Length();
    float speed = parent->m_maxSpeed;
    float time = dist/speed;
    futurePowPosition += time*powerup->m_velocity;
    Point3f deltaFPos = futurePowPosition - ship->m_position;
    deltaFPos.Normalize();
    
    //add braking vec if you're going too fast
    speed = ship->m_velocity.Length();
    if(speed > parent->m_maxSpeed)
        deltaFPos += -ship->UnitVectorVelocity();

    //DOT out my velocity
    Point3f shpUnitVel = ship->UnitVectorVelocity();
    float dotVel = DOT(shpUnitVel,deltaFPos);
    float proj = 1-dotVel;
    deltaFPos -= proj*shpUnitVel;
    deltaFPos.Normalize();

    float newDir = CALCDIR(deltaFPos);
    float angDelta = CLAMPDIR180(ship->m_angle - newDir);
    if(fabsf(angDelta) <2 || fabsf(angDelta)> 177)//thrust
    {
        ship->StopTurn();
        if(speed < parent->m_maxSpeed || parent->m_nearestPowerupDist > 20)
            fabsf(angDelta)<2? ship->ThrustOn() : ship->ThrustReverse();
        else
            ship->ThrustOff();
    }
    else if(fabsf(angDelta)<=90)//turn front
    {
        if(angDelta >0)
            ship->TurnRight();
        else
            ship->TurnLeft();
    }
    else//turn rear
    {
        if(angDelta<0)
            ship->TurnRight();
        else
            ship->TurnLeft();
    }
    
    parent->m_target->m_position = futurePowPosition;
    parent->m_targetDir = newDir;
    parent->m_debugTxt = "GetPowerup";
}

//---------------------------------------------------------
void MStateGetPowerup::Enter()
{
    g_MessagePump.RegisterForMessage(MESSAGE_WILL_COLLIDE,this,GetMessageID(),m_evadeCallback);
    g_MessagePump.RegisterForMessage(MESSAGE_ASTEROID_NEAR,this,GetMessageID(),m_idleCallback);
    g_MessagePump.RegisterForMessage(MESSAGE_NO_POWERUPS,this,GetMessageID(),m_idleCallback);
}

//---------------------------------------------------------
void MStateGetPowerup::Exit()
{
    g_MessagePump.UnRegisterForMessage(MESSAGE_WILL_COLLIDE,GetMessageID());
    g_MessagePump.UnRegisterForMessage(MESSAGE_ASTEROID_NEAR,GetMessageID());
    g_MessagePump.UnRegisterForMessage(MESSAGE_NO_POWERUPS,GetMessageID());

    //send out messages to stop the ship
    Message* newMsg = new Message(MESSAGE_SHIP_TOTAL_STOP);
    newMsg->m_fromID = GetMessageID();
    g_MessagePump.SendMessage(newMsg);
}