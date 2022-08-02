#include "V1Rectangle.h"
#include "DP1.h"

V1Rectangle::V1Rectangle(double x1, double y1, double x2, double y2) : 
    Rectangle(x1, y1, x2, y2)
{
}

V1Rectangle::~V1Rectangle(void)
{
}
void V1Rectangle::drawLine( double x1, double y1, double x2, double y2)
{
    DP1::draw_a_line( x1, y1, x2, y2);
}