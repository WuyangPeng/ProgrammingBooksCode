#include "ccc_win.h"

int ccc_win_main()
{  
   Point p(1, 3);
   Message greeting(p, "Hello, Window!");
   cwin << greeting;

   return 0;
}

