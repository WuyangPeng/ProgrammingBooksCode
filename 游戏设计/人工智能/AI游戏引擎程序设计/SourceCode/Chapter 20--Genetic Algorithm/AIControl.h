#ifndef __AICONTROL
#define __AICONTROL

#include "Control.h"

class Ship;

class AIControl: public Control
{
public:
	//constructor/functions
    AIControl(Ship* ship = NULL);
    ~AIControl(){}
	virtual void UpdatePerceptions(float dt){}
	virtual void Update(float dt);
    virtual void Reset(){}

	//debug data
	GameObj* m_target;
	char*	 m_debugTxt;
	float	 m_targetDir;
	
};
#endif