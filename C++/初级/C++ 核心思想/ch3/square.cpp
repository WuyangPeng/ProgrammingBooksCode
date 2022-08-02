#include "ccc_win.h"

int ccc_win_main()
{  
   Point p(1, 3);
   Point q = p;
   Point r = p;
   q.move(0, 1);
   r.move(1, 0);
   Line s(p, q);
   Line t(p, r);
   cwin << s << t;
   s.move(1, 0);
   t.move(0, 1);
   cwin << s << t;

   return 0;
}

