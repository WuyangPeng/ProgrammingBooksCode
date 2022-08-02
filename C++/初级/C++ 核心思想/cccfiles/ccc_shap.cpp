#include <cstdio>

#include "ccc_shap.h"

Point::Point()
{  
   x = 0.0;
   y = 0.0;
}

Point::Point(double x1, double y1)
{  
   x = x1;
   y = y1;
}

double Point::get_x() const
{  
   return x;
}

double Point::get_y() const
{  
   return y;
}

void Point::move(double dx, double dy)
{  
   x += dx;
   y += dy;
}

/*-------------------------------------------------------------------------*/

Circle::Circle()
{  
   radius = 0.0;
}

Circle::Circle(Point p, double r)
{  
   center = p;
   radius = r;
}

Point Circle::get_center() const
{  
   return center;
}

double Circle::get_radius() const
{  
   return radius;
}

void Circle::move(double dx, double dy)
{  
   center.move(dx, dy);
}

/*-------------------------------------------------------------------------*/

Line::Line()
{
}

Line::Line(Point p1, Point p2)
{  
   from = p1;
   to = p2;
}

Point Line::get_start() const
{  
   return from;
}

Point Line::get_end() const
{  
   return to;
}

void Line::move(double dx, double dy)
{  
   from.move(dx, dy);
   to.move(dx, dy);
}

/*-------------------------------------------------------------------------*/

Message::Message()
{}

Message::Message(Point s, const string& m)
{  
   start = s;
   text = m;
}

Message::Message(Point s, double x)
{  
   start = s;
   char buf[20];
   sprintf(buf, "%g", x);
   text = buf;
}


Point Message::get_start() const
{  
   return start;
}

string Message::get_text() const
{  
   return text;
}

void Message::move(double dx, double dy)
{  
   start.move(dx, dy);
}

