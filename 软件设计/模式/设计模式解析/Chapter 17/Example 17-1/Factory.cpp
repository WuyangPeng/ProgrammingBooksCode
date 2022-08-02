#include "Factory.h"

Factory::Factory(void)
{
}

Factory::~Factory(void)
{
}

Component *Factory::getComponent()
{
    bool doHeader1;
    bool doHeader2;
    bool doFooter1;
    bool doFooter2;

    // Put code here that sets doHeader1, doHeader2, doFooter1, doFooter2
    // One way could look up in a configuration file.
    // Here I'll hardcode an example that gives a footer1 and a header1
    doHeader1= true;
    doHeader2= false;
    doFooter1= true;
    doFooter2= false;

    Component *myComponent;
    myComponent = new SalesTicket;

    // Note that the chain is built backwards so the last one instantiated
    // is at the front of the list
    if (doFooter2) myComponent= new Footer2( myComponent);
    if (doFooter1) myComponent= new Footer1( myComponent);
    if (doHeader2) myComponent= new Header2( myComponent);
    if (doHeader1) myComponent= new Header1( myComponent);

    return (myComponent);
}