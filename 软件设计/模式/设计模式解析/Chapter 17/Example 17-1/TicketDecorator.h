#pragma once
#include "component.h"

class TicketDecorator :    public Component
{
public:
    TicketDecorator(Component *myComponent);
    void callTrailer();
public:
    ~TicketDecorator(void);
private:
     Component *myTrailer;
};