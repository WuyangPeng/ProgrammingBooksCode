//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

#include "ArrayList.h"
#include <iostream>
#include <string>

int main()
{
   ListInterface<string>* listPtr = new ArrayList<string>();
   string data[] = {"one", "two", "three", "four", "five", "six"};
   cout << "isEmpty: returns " << listPtr->isEmpty()
   << "; should be 1 (true)" << endl;
   for (int i = 0; i < 6; i++)
   {
      if (listPtr->insert(i + 1, data[i]))
         cout << "Inserted " << listPtr->getEntry(i + 1)
         << " at position " << (i + 1) << endl;
      else
         cout << "Cannot insert " << data[i] << " at position " << (i + 1)
         << endl;
   }  // end for
   
   return 0;
}  // end main

/*
 isEmpty: returns 1; should be 1 (true)
 Inserted one at position 1
 Inserted two at position 2
 Inserted three at position 3
 Inserted four at position 4
 Inserted five at position 5
 Cannot insert six at position 6
 */