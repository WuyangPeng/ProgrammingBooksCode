#include "MStateIdle.h"
#include "MessAIControl.h"
#include "MessagePump.h"

//---------------------------------------------------------
void MStateIdle::Update(float dt)
{
    //Do nothing
    MessAIControl* parent = (MessAIControl*)m_parent;
    parent->m_debugTxt = "Idle";
}

//---------------------------------------------------------
void MStateIdle::Enter()
{
    g_MessagePump.RegisterForMessage(MESSAGE_WILL_COLLIDE,this,GetMessageID(),m_evadeCallback);
    g_MessagePump.RegisterForMessage(MESSAGE_ASTEROID_FAR,this,GetMessageID(),m_approachCallback);
    g_MessagePump.RegisterForMessage(MESSAGE_ASTEROID_NEAR,this,GetMessageID(),m_attackCallback);
    g_MessagePump.RegisterForMessage(MESSAGE_POWERUP_NEAR,this,GetMessageID(),m_getPowerupCallback);
}

//---------------------------------------------------------
void MStateIdle::Exit()
{
    g_MessagePump.UnRegisterForMessage(MESSAGE_WILL_COLLIDE,GetMessageID());
    g_MessagePump.UnRegisterForMessage(MESSAGE_ASTEROID_FAR,GetMessageID());
    g_MessagePump.UnRegisterForMessage(MESSAGE_ASTEROID_NEAR,GetMessageID());
    g_MessagePump.UnRegisterForMessage(MESSAGE_POWERUP_NEAR,GetMessageID());
}
