#ifndef __HUMANCONTROL
#define __HUMANCONTROL

#include "Control.h"

class Ship;

class HumanControl: public Control
{
public:
	//constructor/functions
	HumanControl(Ship* ship = NULL);
	
};
// global keyboard functions
extern void Key(unsigned char key, int x, int y);
extern void KeyUp(unsigned char key, int x, int y);
extern void SpecialKey(int key, int x, int y);
extern void SpecialKeyUp(int key, int x, int y);

#endif