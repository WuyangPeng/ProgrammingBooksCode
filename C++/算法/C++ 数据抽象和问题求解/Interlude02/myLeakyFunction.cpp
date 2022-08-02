//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

void myLeakyFunction(const double& someItem)
{
   ToyBox<double>* someBoxPtr = new ToyBox<double>();
   someBoxPtr->setItem(someItem);
}  // end myLeakyFunction