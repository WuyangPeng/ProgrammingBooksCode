//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

int gcd(int a, int b)
{
   if (a % b == 0) // Base case
      return b;
   else
      return gcd(b, a % b);
}  // end gcd