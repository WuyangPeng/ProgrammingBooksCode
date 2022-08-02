//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

void goodFunction()
{
   double boxValue = 4.321; // Original statement
   GoodMemory gmObject; // Create a safe memory object
   gmObject.fixedLeak(boxValue); // Perform the task
}  // end goodFunction