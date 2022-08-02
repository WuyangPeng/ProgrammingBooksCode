#include "ccc_win.h"

int ccc_win_main()
{  
   cwin.coord(1, 33, 12, 11);
   cwin << Point(1, 11);
   cwin << Point(2, 13);
   cwin << Point(3, 16);
   cwin << Point(4, 20);
   cwin << Point(5, 25);
   cwin << Point(6, 31);
   cwin << Point(7, 33);
   cwin << Point(8, 32);
   cwin << Point(9, 29);
   cwin << Point(10, 23);
   cwin << Point(11, 16);
   cwin << Point(12, 12);

   return 0;
}
