//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

/** Iterative version. */
void writeBackward(string s)
{
   int length = (int)s.size();
   while (length > 0)
   {
      cout << s.substr(length - 1, 1);
      length--;
   }  // end while
}  // end writeBackward