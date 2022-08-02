#pragma once
#include "ticketdecorator.h"

class Footer2 :    public TicketDecorator
{
public:
    Footer2(Component *myComponent);
    void prtTicket();
public:
    ~Footer2(void);
};