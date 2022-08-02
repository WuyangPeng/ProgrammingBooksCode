#include "ccc_win.h"
#include <cmath>
using namespace std;

int ccc_win_main()
{  
   double radius = cwin.get_double("Radius: ");
   Circle c(Point(0, 0), radius);

   double b = cwin.get_double("Line position: ");
   Line s(Point(-10, b), Point(10, b));

   cwin << c << s;

   double root = sqrt(radius * radius - b * b);
   
   Point p1(root, b);
   Point p2(-root, b);

   Message m1(p1, p1.get_x());
   Message m2(p2, p2.get_x());

   cwin << p1 << p2 << m1 << m2;

   return 0;
}

