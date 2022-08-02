//File: Shapes.h

#ifndef  _SHAPE_H
#define  _SHAPE_H

#include <iostream>
using namespace std;

class Shape
{
public:
	//purely virtual, no actual function exists
	virtual void WhatAmI() =0 ;  

};

class Pyramid:public Shape
{
public:
	void WhatAmI() { cout << "\nI am a pyramid. "; }
};

class Sphere : public Shape
{
public:
	void WhatAmI() { cout << "\nI am a sphere. "; }
};

class Cone:public Shape
{
public:
	void WhatAmI() { cout << "\nI am a cone. "; }
};

class Box : public Shape
{
public:
	void WhatAmI() { cout << "\nI am a box. "; }
};

#endif
