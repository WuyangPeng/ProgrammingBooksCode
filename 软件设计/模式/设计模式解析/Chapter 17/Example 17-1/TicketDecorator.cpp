#include "TicketDecorator.h"

TicketDecorator::TicketDecorator(Component *myComponent)
{
    myTrailer= myComponent;
}

TicketDecorator::~TicketDecorator(void)
{
}

void TicketDecorator::callTrailer()
{
    if (myTrailer != 0l) myTrailer->prtTicket();
}