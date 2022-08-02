//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

// Listing C3-2
PlainBox<string> findBox(PlainBox<string> boxes[], int size, string target)
{
   int index = 0;
   bool found = false;
   while (!found && (index < size))
   {
      if (target == boxes[index].getItem())
         found = true;
      else
         index++;
   } // end while
   
   assert(found);     // Verify that there is a box to return
   return boxes[index];
} // end findBox