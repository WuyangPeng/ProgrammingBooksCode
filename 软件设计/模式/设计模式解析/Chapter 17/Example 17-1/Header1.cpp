#include "Header1.h"

Header1::Header1(Component *myComponent) : TicketDecorator( myComponent)
{
}

Header1::~Header1(void)
{
}

void Header1::prtTicket()
{
    // place printing header 1 code here
    callTrailer();
}