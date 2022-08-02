#ifndef __MESSSTATE
#define __MESSSTATE

#include "MFSM.h"
#include "MessagePump.h"
#include <stdlib.h>

class Control;

class MessState
{
public:
    //constructor/functions
    MessState(int type = MFSM_STATE_NONE,Control* parent = NULL)
        {m_type = type;m_parent=parent;}
    virtual void Enter()            {}
    virtual void Exit()             {}
    virtual void Update(float dt)   {}
    virtual void Init()             {}
    int GetMessageID()              {return m_messReceiver.m_ID;}

    //data
    Control*   m_parent;
    int        m_type;
    MessageReceiver m_messReceiver;
};
#endif