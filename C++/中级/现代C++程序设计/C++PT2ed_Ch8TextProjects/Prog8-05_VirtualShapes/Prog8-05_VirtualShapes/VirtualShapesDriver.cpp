//File: VirtualShapesDriver.cpp

#include <iostream>
using namespace std;
#include "Shapes.h"

int main()
{
	cout << "The Virtual Shapes Program" << endl;

	Shape *basePtrs[4];	//make an array of
						//base class pointers

	Sphere MySphere;
	Pyramid MyPyramid;
	Cone MyCone;
	Box MyBox;

	basePtrs[0] = &MyCone;	//place addresses of child
	basePtrs[1] = &MySphere; //objects into base pointers
	basePtrs[2] = &MyPyramid; 
	basePtrs[3] = &MyBox;

	//can now loop through array to 
	//access each object's WhatAmI function
	for(int i = 0; i < 4; ++i)
	{
		basePtrs[i]->WhatAmI();
	}

	cout << "\n\nVery cool, don't you think? " << endl;
	return 0;
}