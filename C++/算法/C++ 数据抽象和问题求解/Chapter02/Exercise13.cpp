//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

void displayOctal(int n)
{
   if (n > 0)
   {
      if (n / 8 > 0)
         displayOctal(n / 8);
      cout << n % 8;
   }  // end if
}  // end displayOctal