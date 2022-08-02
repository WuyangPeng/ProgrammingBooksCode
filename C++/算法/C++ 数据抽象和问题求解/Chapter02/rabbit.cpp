//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

/** Computes a term in the Fibonacci sequence.
 @pre n  is a positive integer.
 @post  None.
 @param n  The given integer.
 @return  The nth Fibonacci number. */
int rabbit(int n)
{
   if (n <= 2)
      return 1;
   else // n > 2, so n - 1 > 0 and n - 2 > 0
      return rabbit(n - 1) + rabbit(n - 2);
}  // end rabbit