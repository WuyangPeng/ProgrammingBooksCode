#include "Header2.h"

Header2::Header2( Component *myComponent) : TicketDecorator( myComponent)
{
}

Header2::~Header2(void)
{
}

void Header2::prtTicket()
{
    // place printing header 2 code here
    callTrailer();
}