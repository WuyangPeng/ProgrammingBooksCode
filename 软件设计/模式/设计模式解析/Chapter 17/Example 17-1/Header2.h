#pragma once
#include "ticketdecorator.h"

class Header2 :    public TicketDecorator
{
public:
    Header2(Component *myComponent);
    void prtTicket();
public:
    ~Header2(void);
};