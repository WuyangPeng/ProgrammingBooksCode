#include "ccc_win.h"

int ccc_win_main()
{  
   Point p(1, 3);
   cwin << p << Circle(p, 2.5);

   return 0;
}

