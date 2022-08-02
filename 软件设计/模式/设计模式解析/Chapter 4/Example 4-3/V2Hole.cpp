#include "V2Hole.h"
#include "OOGFeature.h"

V2Hole::V2Hole(OOGFeature *feature)
{
    myOOGFeature= feature;
}

V2Hole::~V2Hole(void)
{
}
double V2Hole::getX () 
{
    return myOOGFeature->getX1();
}