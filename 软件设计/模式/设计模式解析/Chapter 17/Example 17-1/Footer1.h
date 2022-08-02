#pragma once
#include "ticketdecorator.h"

class Footer1 :    public TicketDecorator
{
public:
    Footer1(Component *myComponent);
    void prtTicket();
public:
    ~Footer1(void);
};