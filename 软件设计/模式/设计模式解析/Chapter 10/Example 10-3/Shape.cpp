#include "Shape.h"

Shape::Shape(Drawing *aDrawing)
{
    myDrawing= aDrawing;
}

Shape::~Shape(void)
{
}

void Shape::drawLine( double x1,double y1, double x2,double y2) 
{
   myDrawing->drawLine(x1,y1,x2,y2);
}

void Shape::drawCircle( double x,double y,double r) 
{
   myDrawing->drawCircle(x,y,r);
}