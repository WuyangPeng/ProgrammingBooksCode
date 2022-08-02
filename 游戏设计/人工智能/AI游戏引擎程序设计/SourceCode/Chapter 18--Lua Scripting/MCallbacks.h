#ifndef __MFUNCTORS
#define __MFUNCTORS

#include "Callback.h"

//callbacks for handling messages
class EvadeCallback : public Callback   
{       
    void function(void* parent, Message* msg);
};
class ApproachCallback : public Callback    
{       
    void function(void* parent, Message* msg);
};
class AttackCallback : public Callback  
{       
    void function(void* parent, Message* msg);
};
class GetPowerupCallback : public Callback  
{       
    void function(void* parent, Message* msg);
};
class IdleCallback : public Callback  
{       
    void function(void* parent, Message* msg);
};

#endif