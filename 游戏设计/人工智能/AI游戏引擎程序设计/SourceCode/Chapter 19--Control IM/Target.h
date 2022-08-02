#ifndef __TARGET
#define __TARGET

#include "GameObj.h"

class Target : public GameObj
{
public:
	//constructors/functions
	Target();
    ~Target();
	void Draw();
};
#endif