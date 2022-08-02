//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

/** Writes a character string backward.
 @pre  The string s to write backward.
 @post  None.
 @param s  The string to write backward. */
void writeBackward(string s)
{
   int length = (int)s.size(); // Length of string
   if (length > 0)
   {
      // Write the last character
      cout << s.substr(length - 1, 1);
      
      // Write the rest of the string backward
      writeBackward(s.substr(0, length - 1)); // Point A
   } // end if
   
   // length == 0 is the base case - do nothing
}  // end writeBackward