#include "V1Circle.h"
#include "DP1.h"

V1Circle::V1Circle(double x, double y, double r) : Circle( x, y, r)
{
}

V1Circle::~V1Circle(void)
{
}

void V1Circle::drawCircle ( double x, double y, double r)
{
    DP1::draw_a_circle( x, y, r);
}