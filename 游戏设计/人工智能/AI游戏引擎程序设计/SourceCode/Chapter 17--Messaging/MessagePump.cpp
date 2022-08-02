#pragma warning(disable: 4786)
#include <algorithm>
#include "MessagePump.h"
#include "Callback.h"


MessageTypeMap MessagePump::m_messageTypes;
MessageList MessagePump::m_messageQueue;
MessageList MessagePump::m_messageIncomingQueue;

int MessagePump::m_uniqueID = 0;

//---------------------------------------------------------
MessageReceiver::MessageReceiver()
{
    m_ID = MessagePump::GetUniqueMessageID();
}

//---------------------------------------------------------
//functor for removing delivered messages
bool RemoveIfDelivered(Message* msg)
{
    if(msg->m_delivered)
    {
        delete msg;
        return true;
    }
    return false;
}

//---------------------------------------------------------
MessagePump::MessagePump()
{
//    m_messageTypes.clear();
//    m_messageQueue.clear();
}

//---------------------------------------------------------
void MessagePump::Update(float dt)
{
    //move over new incoming messages
    m_messageQueue.merge(m_messageIncomingQueue);
    m_messageIncomingQueue.clear();
    
    if(m_messageQueue.size() == 0)
        return;

    //process messages
    MessageList::iterator msg;
    for(msg=m_messageQueue.begin();msg!=m_messageQueue.end();++msg)
    {
        Message* pMsg = (*msg);
        if(pMsg->m_timer >= 0)
        {
            //delayed message, decrement timer
            pMsg->m_timer -= dt;
        }
        else
        {
            //check for registrations
            MessageTypeMap::iterator mType;
            mType = m_messageTypes.find(pMsg->m_typeID);
            if(mType == m_messageTypes.end())
                continue;
            MessageType* pmType = (*mType).second;

            MessageRegList::iterator msgReg;
            MessageRegList* pMessReg = &(*mType).second->m_messageRegistrations;
            for(msgReg=(*mType).second->m_messageRegistrations.begin();msgReg!=(*mType).second->m_messageRegistrations.end();++msgReg)
            {
                MessageReg* pmReg = (*msgReg);
                //deliver message by launching callback
                if(pmReg->m_callBack)
                    pmReg->m_callBack->function(pmReg->m_parent,pMsg);
            }
            pMsg->m_delivered = true;
        }
    }

    //remove all delivered messages from queue
    MessageList::iterator end    = m_messageQueue.end();
    MessageList::iterator newEnd = std::remove_if(m_messageQueue.begin(),m_messageQueue.end(),RemoveIfDelivered);
    if(newEnd != end)
        m_messageQueue.erase(newEnd,end);
}

//---------------------------------------------------------
void MessagePump::AddMessageToSystem(int type)
{
    //ensure that this type isn't already in the system
    MessageTypeMap::iterator mType;
    mType = m_messageTypes.find(type);
    
    if(mType == m_messageTypes.end())
    {
        MessageType *newType = new MessageType;
        newType->m_typeID = type;
        m_messageTypes[type] = newType;
        newType->m_name = new char[20];
        newType->m_name = GetMessageName(type);
    }
}

//---------------------------------------------------------
char* MessagePump::GetMessageName(int type)
{
    switch(type)
    {
        case MESSAGE_WILL_COLLIDE:
            return "Will Collide";
        case MESSAGE_WONT_COLLIDE:
            return "Wont Collide";
        case MESSAGE_NO_ASTEROIDS:
            return "No Asteroids";
        case MESSAGE_NO_POWERUPS:
            return "No Powerups";
        case MESSAGE_ASTEROID_FAR:
            return "Asteroid Far";
        case MESSAGE_ASTEROID_NEAR:
            return "Asteroid Near";
        case MESSAGE_POWERUP_NEAR:
            return "Powerup Near";
        case MESSAGE_POWERUP_FAR:
            return "Powerup Far";
        case MESSAGE_CHANGE_STATE:
            return "Change State";
        case MESSAGE_SHIP_TOTAL_STOP:
            return "Ship Total Stop";
        default:
            return "Error Message";
            break;
    }
}
//---------------------------------------------------------
void MessagePump::SendMessage(Message* newMessage)
{
    m_messageIncomingQueue.push_back(newMessage);
}

//---------------------------------------------------------
int MessagePump::RegisterForMessage(int type, void* parent, int objectID, Callback& cBack)
{
    //only register once
    MessageTypeMap::iterator mType;
    mType = m_messageTypes.find(type);
    MessageType* pmtype = (*mType).second;
        
    if(mType == m_messageTypes.end())
        return REGISTER_ERROR_MESSAGE_NOT_IN_SYSTEM;

    MessageRegList::iterator msgReg;
    for(msgReg=(*mType).second->m_messageRegistrations.begin();msgReg!=(*mType).second->m_messageRegistrations.end();++msgReg)
    {
        if((*msgReg)->m_objectID == objectID)
            return REGISTER_ERROR_ALREADY_REGISTERED;
    }
    //add new registration
    MessageReg* newRegistration  = new MessageReg;
    newRegistration->m_parent    = parent;
    newRegistration->m_callBack  = &cBack;
    newRegistration->m_objectID  = objectID;

    (*mType).second->m_messageRegistrations.push_back(newRegistration);
    return REGISTER_MESSAGE_OK;
    
    
}

//---------------------------------------------------------
void MessagePump::UnRegisterForMessage(int type, int objectID)
{
    //find entry
    MessageTypeMap::iterator mType;
    mType = m_messageTypes.find(type);
    
    if(mType == m_messageTypes.end())
        return;
    
    MessageRegList::iterator msgReg;
    for(msgReg=(*mType).second->m_messageRegistrations.begin();msgReg!=(*mType).second->m_messageRegistrations.end();)
    {
        if((*msgReg)->m_objectID == objectID)
        {
            (*mType).second->m_messageRegistrations.erase(msgReg);
            //you can exit out here, there is only one registration 
            //allowed per message type
            return;
        }
        else
            msgReg++;
    }
}

//---------------------------------------------------------
void MessagePump::UnRegisterAll(int objectID)
{
    MessageTypeMap::iterator mType;
    for(mType = m_messageTypes.begin();mType != m_messageTypes.end(); ++mType)
    {
        MessageRegList::iterator msgReg;
        for(msgReg=(*mType).second->m_messageRegistrations.begin();msgReg!=(*mType).second->m_messageRegistrations.end();)
        {
            if((*msgReg)->m_objectID == objectID)
            {
                (*mType).second->m_messageRegistrations.erase(msgReg);
                //you can exit out here, there is only one registration 
                //allowed per message type
                return;
            }
            else
                msgReg++;
        }
    }
}