//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

void solveTowers(int count, char source, char destination, char spare)
{
   if (count == 1)
   {
      cout << "Move top disk from pole " << source
           << " to pole " << destination << endl;
   }
   else
   {
      solveTowers(count - 1, source, spare, destination); // X
      solveTowers(1, source, destination, spare);         // Y
      solveTowers(count - 1, spare, destination, source); // Z
   }  // end if
}  // end solveTowers