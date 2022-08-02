#include "Circle.h"

Circle::Circle(double x, double y, double r)
{
    _x= x;
    _y= y;
    _r= r;
}

Circle::~Circle(void)
{
}

void Circle::draw ()
{
    drawCircle( _x, _y, _r);
}