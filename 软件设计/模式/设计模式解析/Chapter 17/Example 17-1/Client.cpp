#include "Client.h"

Client::Client(void)
{
}

Client::~Client(void)
{
}

static void main ()
{
    Factory myFactory;
    Component *myComponent = myFactory.getComponent();
}