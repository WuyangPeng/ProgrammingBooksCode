#include "MCallbacks.h"
#include "MessagePump.h"
#include "MFSM.h"
#include "MessState.h"
#include "iostream.h"


//---------------------------------------------------------
void EvadeCallback::function(void* parent, Message* msg)
{
    DataMessage<int>* newMsg = new DataMessage<int>(MESSAGE_CHANGE_STATE,MFSM_STATE_EVADE);
    newMsg->m_fromID  = ((MessState*)parent)->GetMessageID();
    g_MessagePump.SendMessage(newMsg);
}

//---------------------------------------------------------
void ApproachCallback::function(void* parent,Message* msg)
{
    DataMessage<int>* newMsg = new DataMessage<int>(MESSAGE_CHANGE_STATE,MFSM_STATE_APPROACH);
    newMsg->m_fromID  = ((MessState*)parent)->GetMessageID();;
    g_MessagePump.SendMessage(newMsg);
}

//---------------------------------------------------------
void AttackCallback::function(void* parent,Message* msg)
{
    DataMessage<int>* newMsg = new DataMessage<int>(MESSAGE_CHANGE_STATE,MFSM_STATE_ATTACK);
    newMsg->m_fromID  = ((MessState*)parent)->GetMessageID();;
    g_MessagePump.SendMessage(newMsg);
}

//---------------------------------------------------------
void GetPowerupCallback::function(void* parent,Message* msg)
{
    DataMessage<int>* newMsg = new DataMessage<int>(MESSAGE_CHANGE_STATE,MFSM_STATE_GETPOWERUP);
    newMsg->m_fromID  = ((MessState*)parent)->GetMessageID();;
    g_MessagePump.SendMessage(newMsg);
}

//---------------------------------------------------------
void IdleCallback::function(void* parent,Message* msg)
{
    DataMessage<int>* newMsg = new DataMessage<int>(MESSAGE_CHANGE_STATE,MFSM_STATE_IDLE);
    newMsg->m_fromID  = ((MessState*)parent)->GetMessageID();;
    g_MessagePump.SendMessage(newMsg);
}
