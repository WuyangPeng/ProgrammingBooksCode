#pragma once
#include "component.h"

class SalesTicket :    public Component
{
public:
    SalesTicket(void);
    void prtTicket();
public:
    ~SalesTicket(void);
};