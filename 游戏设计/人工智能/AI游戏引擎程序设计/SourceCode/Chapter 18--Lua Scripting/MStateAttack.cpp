#include "MStateAttack.h"
#include "Ship.h"
#include "MessAIControl.h"
#include "utility.h"
#include "MessagePump.h"


//---------------------------------------------------------
void MStateAttack::Update(float dt)
{
    //turn towards closest asteroid's future position, and then fire
    MessAIControl* parent = (MessAIControl*)m_parent;
    GameObj* asteroid = parent->m_nearestAsteroid;
    if(!asteroid)
        return;
    
    Ship*    ship     = parent->m_ship;
    
    Point3f futureAstPosition = asteroid->m_position;
    Point3f deltaPos = futureAstPosition - ship->m_position;
    float dist  = deltaPos.Length();
    float time = dist/BULLET_SPEED;
    futureAstPosition += time*asteroid->m_velocity;
    Point3f deltaFPos = futureAstPosition - ship->m_position;
    deltaFPos.Normalize();

    float newDir     = CALCDIR(deltaFPos);
    float angDelta   = CLAMPDIR180(ship->GetClosestGunAngle(newDir) - newDir);
    float dangerAdjAngle = ((1.0f - parent->m_nearestAsteroidDist/ parent->m_appDist)*5.0f) + 1.0f;

    if(angDelta >dangerAdjAngle)
        ship->TurnRight();
    else if(angDelta < -dangerAdjAngle)
        ship->TurnLeft();
    else
    {
        ship->StopTurn();
        ship->Shoot();
    }
    
    parent->m_target->m_position = futureAstPosition;
    parent->m_targetDir = newDir;
    parent->m_debugTxt = "Attack";
}

//---------------------------------------------------------
void MStateAttack::Enter()
{
    g_MessagePump.RegisterForMessage(MESSAGE_WILL_COLLIDE,this,GetMessageID(),m_evadeCallback);
    g_MessagePump.RegisterForMessage(MESSAGE_POWERUP_NEAR,this,GetMessageID(),m_getPowerupCallback);
    g_MessagePump.RegisterForMessage(MESSAGE_NO_ASTEROIDS,this,GetMessageID(),m_idleCallback);
    g_MessagePump.RegisterForMessage(MESSAGE_ASTEROID_FAR,this,GetMessageID(),m_idleCallback);
}

//---------------------------------------------------------
void MStateAttack::Exit()
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