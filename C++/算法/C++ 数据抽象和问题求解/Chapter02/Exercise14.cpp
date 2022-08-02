//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

int f(int n);

int main()
{
   cout << "The value of f(8) is " << f(8) << endl;
   return 0;
}  // end main

/** @pre n >= 0. */
int f(int n)
{
   cout << "Function entered with n = " << n << endl;
   switch (n)
   {
      case 0: case 1: case 2:
         return n + 1;
      default:
         return f(n-2) * f(n-4);
   }  // end switch
}  // end f