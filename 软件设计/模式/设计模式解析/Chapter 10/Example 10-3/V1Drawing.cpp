#include "V1Drawing.h"

V1Drawing::V1Drawing(void)
{
}

V1Drawing::~V1Drawing(void)
{
}

void V1Drawing::drawLine ( double x1,double y1, double x2,double y2) 
{
   DP1::draw_a_line(x1,y1,x2,y2);
}

void V1Drawing::drawCircle (double x,double y,double r) 
{
   DP1::draw_a_circle(x,y,r);
}