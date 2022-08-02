#include "Rectangle.h"

Rectangle::Rectangle(double x1, double y1, double x2, double y2) 
{
    _x1= x1; _y1= y1; _x2= x2; _y2= y2;
}

Rectangle::~Rectangle(void)
{
}

void Rectangle::draw()
{
    drawLine( _x1, _y1, _x2, _y1);
    drawLine( _x2, _y1, _x2, _y2);
    drawLine( _x2, _y2, _x1, _y2);
    drawLine( _x1, _y2, _x1, _y1);
}