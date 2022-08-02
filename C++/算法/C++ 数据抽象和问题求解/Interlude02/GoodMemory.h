//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

/** @file GoodMemory.h 
    Listing C2-2 */
#include <string>
#include "ToyBox.h"
using namespace std;
class GoodMemory
{
private:
   ToyBox<string>* someBoxPtr;
public:
   GoodMemory(); // Default constructor
   ~GoodMemory(); // Destructor
   void fixedLeak(const double& someItem);
}; // end GoodMemory