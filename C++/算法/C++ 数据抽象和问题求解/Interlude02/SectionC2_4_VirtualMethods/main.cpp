//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

// Section C2.4

#include <iostream>
#include <string>
#include "PlainBox.h"
#include "MagicBox.h"

using namespace std;

void placeInBox(PlainBox<string>* theBox, string theItem)
{
   theBox->setItem(theItem);
} // end placeInBox

int main()
{
   string specialItem = "Riches beyond compare!";
   string otherItem = "Hammer";
   
   PlainBox<string>* myPlainBoxPtr = new PlainBox<string>();
   placeInBox(myPlainBoxPtr, specialItem);
   cout << myPlainBoxPtr->getItem() << endl;
   
   MagicBox<string>* myMagicBoxPtr = new MagicBox<string>();
   placeInBox(myMagicBoxPtr, otherItem);
   placeInBox(myMagicBoxPtr, specialItem);
   
   cout << myMagicBoxPtr->getItem() << endl;
   
   delete myPlainBoxPtr;
   myPlainBoxPtr = nullptr;
   delete myMagicBoxPtr;
   myMagicBoxPtr = nullptr;     
   
   return 0;
}  // end main

/*

Riches beyond compare!
Hammer

*/
