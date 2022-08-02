#include "MStateApproach.h"
#include "Ship.h"
#include "MessAIControl.h"
#include "utility.h"
#include "MessagePump.h"


//---------------------------------------------------------
void MStateApproach::Update(float dt)
{
    //turn and then thrust towards closest asteroid
    MessAIControl* parent = (MessAIControl*)m_parent;
    GameObj* asteroid = parent->m_nearestAsteroid;
    if(!asteroid)
        return;
    
    Ship*    ship     = parent->m_ship;
    Point3f deltaPos = asteroid->m_position - ship->m_position;
    deltaPos.Normalize();
    
    //add braking vec if you're going too fast
    float speed = ship->m_velocity.Length();
    if(speed > parent->m_maxSpeed)
        deltaPos += -ship->UnitVectorVelocity();
    
    //DOT out my velocity
    Point3f shpUnitVel = ship->UnitVectorVelocity();
    float dotVel = DOT(shpUnitVel,deltaPos);
    float proj = 1-dotVel;
    deltaPos -= proj*shpUnitVel;
    deltaPos.Normalize();
    
    //find new direction, and head to it
    float newDir = CALCDIR(deltaPos);
    float angDelta = CLAMPDIR180(ship->m_angle - newDir);
    if(fabsf(angDelta) <2 || fabsf(angDelta)> 177)
    {
        //thrust
        ship->StopTurn();
        if(speed < parent->m_maxSpeed || parent->m_nearestAsteroidDist > 40)
            fabsf(angDelta)<2? ship->ThrustOn() : ship->ThrustReverse();
        else
            ship->ThrustOff();
    }
    else if(fabsf(angDelta)<=90)
    {
        //turn when facing forwards
        if(angDelta >0)
            ship->TurnRight();
        else
            ship->TurnLeft();
    }
    else
    {
        //turn when facing rear
        if(angDelta<0)
            ship->TurnRight();
        else
            ship->TurnLeft();
    }
    
    parent->m_target->m_position = asteroid->m_position;
    parent->m_targetDir = newDir;
    parent->m_debugTxt = "Approach";
}

//---------------------------------------------------------
void MStateApproach::Enter()
{
    g_MessagePump.RegisterForMessage(MESSAGE_WILL_COLLIDE,this,GetMessageID(),m_evadeCallback);
    g_MessagePump.RegisterForMessage(MESSAGE_POWERUP_NEAR,this,GetMessageID(),m_getPowerupCallback);
    g_MessagePump.RegisterForMessage(MESSAGE_NO_ASTEROIDS,this,GetMessageID(),m_idleCallback);
    g_MessagePump.RegisterForMessage(MESSAGE_ASTEROID_NEAR,this,GetMessageID(),m_idleCallback);
}

//---------------------------------------------------------
void MStateApproach::Exit()
{
    g_MessagePump.UnRegisterForMessage(MESSAGE_WILL_COLLIDE,GetMessageID());
    g_MessagePump.UnRegisterForMessage(MESSAGE_POWERUP_NEAR,GetMessageID());
    g_MessagePump.UnRegisterForMessage(MESSAGE_NO_ASTEROIDS,GetMessageID());
    g_MessagePump.UnRegisterForMessage(MESSAGE_ASTEROID_FAR,GetMessageID());
    
    //send out messages to stop the ship
    Message* newMsg = new Message(MESSAGE_SHIP_TOTAL_STOP);
    newMsg->m_fromID = GetMessageID();
    g_MessagePump.SendMessage(newMsg);
}