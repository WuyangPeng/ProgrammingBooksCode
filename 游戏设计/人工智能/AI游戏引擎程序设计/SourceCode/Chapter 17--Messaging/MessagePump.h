#ifndef __MESSAGEPUMP
#define __MESSAGEPUMP

#include "Message.h"
#include "Messages.h"
#include <stdlib.h>
#pragma warning(disable: 4786)
#include <list>
#include <map>

class  Message;
struct MessageReg;
struct MessageType;
class Callback;

typedef std::list<Message*> MessageList;
typedef std::map<int,MessageType*> MessageTypeMap;

//miniclass for receiving messages
class MessageReceiver
{
public:
    MessageReceiver();
    int m_ID;
};

class MessagePump 
{
public:
    static inline MessagePump& Instance()
    {
        static MessagePump inst;
        return inst;
    }
    
    static void Update(float dt);
    static void AddMessageToSystem(int type);
    static  int RegisterForMessage(int type, void* parent, int objectID, Callback& cBack);
    static void UnRegisterForMessage(int type, int objectID);
    static void UnRegisterAll(int objectID);
    static void SendMessage(Message* newMessage);
    static char* GetMessageName(int type);


    //unique ID handler
    static int  m_uniqueID;
    static int  GetUniqueMessageID(){return m_uniqueID++;}
    
    
protected:
    MessagePump();
    MessagePump& operator= (const MessagePump&){}

private:
    static MessageTypeMap m_messageTypes;
    static MessageList    m_messageQueue;
    static MessageList    m_messageIncomingQueue;
};

#define g_MessagePump MessagePump::Instance() 

#endif