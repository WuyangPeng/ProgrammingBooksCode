#include "Footer2.h"

Footer2::Footer2(Component *myComponent) : TicketDecorator( myComponent)
{
}

Footer2::~Footer2(void)
{
}

void Footer2::prtTicket()
{
    callTrailer();
    // place printing footer 2 code here
}