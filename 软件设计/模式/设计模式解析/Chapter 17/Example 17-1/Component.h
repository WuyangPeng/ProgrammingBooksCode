#pragma once

class Component
{
public:
    Component(void);
    virtual void prtTicket()= 0;
public:
    ~Component(void);
};