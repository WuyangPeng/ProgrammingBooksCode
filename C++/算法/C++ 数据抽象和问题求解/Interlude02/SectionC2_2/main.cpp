//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

// Section C2.2

#include <iostream>
#include <string>
#include "PlainBox.h"
#include "MagicBox.h"

using namespace std;

void placeInBox(PlainBox<string>& theBox, string theItem)
{
   theBox.setItem(theItem);
} // end placeInBox

int main()
{
   string specialItem = "Riches beyond compare!";
   string otherItem = "Hammer";
   
   PlainBox<string> myPlainBox;
   placeInBox(myPlainBox, specialItem);
   
   MagicBox<string> myMagicBox;
   placeInBox(myMagicBox, otherItem);
   placeInBox(myMagicBox, specialItem);     // specialItem is stored!
   
   cout << myMagicBox.getItem() << endl;    // "Riches beyond compare!"
   
   PlainBox<string> mySpecialBox = MagicBox<string>();
   mySpecialBox.setItem(otherItem);
   mySpecialBox.setItem(specialItem);      // specialItem is stored!
   cout << mySpecialBox.getItem() << endl; // "Riches beyond compare!"
   
   return 0;
}  // end main

/*
 Riches beyond compare!
 Riches beyond compare!

*/
