#include "ccc_win.h"

int ccc_win_main()
{  
   double radius = cwin.get_double("Radius: ");
   Circle c(Point(0, 0), radius);

   double b = cwin.get_double("Line position: ");
   Line s(Point(-10, b), Point(10, b));

   cwin << c << s;
   return 0;
}

