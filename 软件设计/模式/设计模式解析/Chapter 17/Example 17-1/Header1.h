#pragma once
#include "ticketdecorator.h"

class Header1 :    public TicketDecorator
{
public:
    Header1(Component *myComponent); 
    void prtTicket();
public:
    ~Header1(void);
};