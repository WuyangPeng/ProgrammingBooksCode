//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

int main()
{
   // Listing C3-4
   // Create and initialize an array of boxes
   PlainBox<string> myBoxes[5]; // Array of PlainBox objects
   myBoxes[0] = PlainBox<string>("ring");
   myBoxes[1] = PlainBox<string>("hat");
   myBoxes[2] = PlainBox<string>("shirt");
   myBoxes[3] = PlainBox<string>("sock");
   myBoxes[4] = PlainBox<string>("shoe");
   PlainBox<string> foundBox;

   // Try to find a box containing glasses
   try
   {
      foundBox = findBox(myBoxes, 5, "glasses");
   }
   catch(logic_error logErr)
   {
      cout << logErr.what() << endl;          // Display error message to user
      foundBox = PlainBox<string>("nothing"); // Fix problem
   } // end try-catch
   // Because we catch the exception and fix the problem, the following
   // statement should work even if the target is not found
   cout << foundBox.getItem();

   return 0;
}
