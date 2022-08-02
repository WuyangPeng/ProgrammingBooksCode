#ifndef __MESSAGE
#define __MESSAGE

#include "Messages.h"
#include <stdlib.h>

class Message
{
public:
    //constructor/functions
    Message(int type = MESSAGE_DEFAULT){m_typeID = type;m_delivered = false;m_timer = 0.0f;}
    virtual ~Message(){}
    
    //data
    int   m_typeID;
    int   m_fromID;
    int   m_toID;
    float m_timer;
    bool  m_delivered;
};

//simple template message class for simple data passing
template <typename T>
class DataMessage: public Message
{
public:
    DataMessage(int type, T data):Message(type){m_dataStorage = data;}
    ~DataMessage(){}

    //data member
    T m_dataStorage;
};

#endif