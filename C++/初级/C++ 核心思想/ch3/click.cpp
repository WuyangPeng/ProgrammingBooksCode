#include "ccc_win.h"

int ccc_win_main()
{  
   string name = cwin.get_string("Please type your name:");
   Circle c(Point(0, 0), 5);
   cwin << c;
   Point m = cwin.get_mouse("Please click inside the circle.");
   cwin << m << Message(m, "You clicked here");
   return 0;
}
