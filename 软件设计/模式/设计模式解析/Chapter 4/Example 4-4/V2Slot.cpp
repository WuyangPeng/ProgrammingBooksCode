#include "V2Slot.h"
#include "OOGFeature.h"

V2Slot::V2Slot(OOGFeature *feature)
{
    myOOGFeature= feature;
}
V2Slot::~V2Slot(void)
{
}

double V2Slot::getX1 () 
{
    return myOOGFeature->getX1();
}
double V2Slot::getX2 () 
{

    return myOOGFeature->getX2();
}
