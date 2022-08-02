#include "Client.h"
#include "Shape.h"
#include "Factory.h"

Client::Client(void)
{
}

Client::~Client(void)
{
}

void static main ()
{
    Shape **myShapes;
    Factory myFactory;

    // get Rectangles from some other source
    myShapes= myFactory.getShapes();
    for (int i= 0; i < sizeof(myShapes)/ sizeof(myShapes[0]); i++)
        myShapes[i]->draw();
}