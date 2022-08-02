#ifndef __MESSAGES
#define __MESSAGES

#include <list>
#include "Callback.h"

class Message;

enum
{
    REGISTER_ERROR_MESSAGE_NOT_IN_SYSTEM = -1,
    REGISTER_ERROR_ALREADY_REGISTERED,
    REGISTER_MESSAGE_OK
};

enum
{
    MESSAGE_DEFAULT = -1,
    MESSAGE_WILL_COLLIDE,
    MESSAGE_WONT_COLLIDE,
    MESSAGE_NO_ASTEROIDS,        
    MESSAGE_NO_POWERUPS,        
    MESSAGE_ASTEROID_FAR,        
    MESSAGE_ASTEROID_NEAR,        
    MESSAGE_POWERUP_NEAR,        
    MESSAGE_POWERUP_FAR,        
    MESSAGE_CHANGE_STATE,        
    MESSAGE_SHIP_TOTAL_STOP,
    
    MESSAGE_TOKEN_PSCAN,
    MESSAGE_TOKEN_MAXSPEED,
    MESSAGE_TOKEN_APDIST,
    MESSAGE_TOKEN_ATDIST,
    MESSAGE_TOKEN_SAFERAD,
    MESSAGE_TOKEN_POWSEEK,
    MESSAGE_COUNT
};

struct MessageReg
{
    MessageReg(){m_objectID = -1;m_parent = NULL; m_callBack = NULL;}
    int       m_objectID;
    void*     m_parent;
    Callback* m_callBack;
};

typedef std::list<MessageReg*> MessageRegList;

struct MessageType
{
    int            m_typeID;
    MessageRegList m_messageRegistrations;

    //debug data
    char* m_name;
};

#endif