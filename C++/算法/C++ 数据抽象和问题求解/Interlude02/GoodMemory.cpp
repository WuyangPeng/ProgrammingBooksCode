//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

/** @file GoodMemory.cpp 
    Listing C2-3 */
#include "GoodMemory.h"

GoodMemory::GoodMemory() : someBoxPtr(nullptr)
{
}  // end default constructor

GoodMemory::~GoodMemory()
{
   delete someBoxPtr;
}  // end destructor

void GoodMemory::fixedLeak(const double& someItem)
{
   someBoxPtr = new ToyBox<double>();
   someBoxPtr->setItem(someItem);
}  // end fixedLeak