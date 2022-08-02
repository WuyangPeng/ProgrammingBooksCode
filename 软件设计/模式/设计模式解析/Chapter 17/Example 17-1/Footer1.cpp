#include "Footer1.h"

Footer1::Footer1(Component *myComponent) : TicketDecorator( myComponent)
{
}

Footer1::~Footer1(void)
{
}

void Footer1::prtTicket()
{
    callTrailer();
    // place printing footer 1 code here
}