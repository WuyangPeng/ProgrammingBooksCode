#include "V2Drawing.h"

V2Drawing::V2Drawing(void)
{
}

V2Drawing::~V2Drawing(void)
{
}

void V2Drawing::drawLine (double x1,double y1, double x2,double y2) 
{
   // arguments are different in DP2
   // and must be rearranged
   DP2::drawline(x1,x2,y1,y2);
}

void V2Drawing::drawCircle ( double x, double y,double r) 
{
   DP2::drawcircle(x,y,r);
}