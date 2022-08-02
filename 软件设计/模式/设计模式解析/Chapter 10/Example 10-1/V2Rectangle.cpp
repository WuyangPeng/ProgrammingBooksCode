#include "V2Rectangle.h"
#include "DP2.h"

V2Rectangle::V2Rectangle(double x1, double y1, double x2, double y2) : 
    Rectangle(x1, y1, x2, y2)
{
}

V2Rectangle::~V2Rectangle(void)
{
}
void V2Rectangle::drawLine( double x1, double y1, double x2, double y2)
{
    DP2::drawline( x1, y1, x2, y2);
}