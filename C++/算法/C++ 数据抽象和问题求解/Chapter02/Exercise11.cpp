//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

int getValue(int a, int b, int n);

int main()
{
   cout << getValue(1, 7, 7) << endl;
   return 0;
}  // end main

int getValue(int a, int b, int n)
{
   int returnValue = 0;
   
   cout << "Enter: a = " << a << " b = " << b << endl;
   int c = (a + b)/2;
   if (c * c <= n)
      returnValue = c;
   else
      returnValue = getValue(a, c-1, n);
   
   cout << "Leave: a = " << a << " b = " << b << endl;
   
   return returnValue;
}  // end getValue