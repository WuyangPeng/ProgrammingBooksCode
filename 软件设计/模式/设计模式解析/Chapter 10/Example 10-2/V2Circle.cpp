#include "V2Circle.h"
#include "DP2.h"

V2Circle::V2Circle(double x, double y, double r) : Circle( x, y, r)
{
}

V2Circle::~V2Circle(void)
{
}
void V2Circle::drawCircle ( double x, double y, double r)
{
    DP2::drawcircle( x, y, r);
}