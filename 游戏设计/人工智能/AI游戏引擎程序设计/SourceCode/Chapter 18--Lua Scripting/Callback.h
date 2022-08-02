#ifndef __CALLBACK
#define __CALLBACK

class Message;

class Callback
{
public:
    virtual void function(void* parent, Message* msg){}
};
#endif