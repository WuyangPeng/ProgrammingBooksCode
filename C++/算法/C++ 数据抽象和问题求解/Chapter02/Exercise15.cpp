//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

void recurse(int x, int y)
{
   if (y > 0)
   {
      x++;
      y--;
      cout << x << " " << y << endl;
      recurse(x, y);
      cout << x << " " << y << endl;
   }  // end if
}  // end recurse