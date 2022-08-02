#include "ccc_win.h"

int ccc_win_main()
{  
   Point p(1, 3);
   Point q(4, 7);
   Line s(p, q);
   cwin << s;

   return 0;
}

