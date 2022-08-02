#include "MStateEvade.h"
#include "Ship.h"
#include "MessAIControl.h"
#include "utility.h"
#include "MessagePump.h"


//---------------------------------------------------------
void MStateEvade::Update(float dt)
{
    //evade by going to the quad opposite as the asteroid
    //is moving, add in a deflection, and cancel out your movement
    MessAIControl* parent = (MessAIControl*)m_parent;
    GameObj* asteroid = parent->m_nearestAsteroid;
    if(!asteroid)
        return;
    Ship*    ship     = parent->m_ship;
    Point3f vecSteer = CROSS(ship->m_position,asteroid->m_position);
    Point3f vecBrake = ship->m_position - asteroid->m_position;
    vecSteer += vecBrake;
    
    float newDir = CALCDIR(vecSteer);
    float angDelta = CLAMPDIR180(ship->m_angle - newDir);
    float dangerAdjAngle = ((1.0f - parent->m_nearestAsteroidDist/ parent->m_appDist)*10.0f) + 1.0f;
    if(fabsf(angDelta) <dangerAdjAngle || fabsf(angDelta)> 180-dangerAdjAngle)//thrust
    {
        ship->StopTurn();
        if(ship->m_velocity.Length() < parent->m_maxSpeed || parent->m_nearestAsteroidDist< 20+asteroid->m_size)
            fabsf(angDelta)<dangerAdjAngle? ship->ThrustOn() : ship->ThrustReverse();
        else
            ship->ThrustOff();

        //if I'm pointed right at the asteroid, shoot
        ship->Shoot();
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
    
    
    parent->m_target->m_position = parent->m_nearestAsteroid->m_position;
    parent->m_targetDir = newDir;
    parent->m_debugTxt = "Evade";
}

//---------------------------------------------------------
void MStateEvade::Enter()
{
    g_MessagePump.RegisterForMessage(MESSAGE_WONT_COLLIDE,this,GetMessageID(),m_idleCallback);
}

//---------------------------------------------------------
void MStateEvade::Exit()
{
    g_MessagePump.UnRegisterForMessage(MESSAGE_WONT_COLLIDE,GetMessageID());
    
    //send out messages to stop the ship
    Message* newMsg = new Message(MESSAGE_SHIP_TOTAL_STOP);
    newMsg->m_fromID = GetMessageID();
    g_MessagePump.SendMessage(newMsg);
}