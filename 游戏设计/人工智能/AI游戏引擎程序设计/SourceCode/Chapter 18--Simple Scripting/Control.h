#ifndef __CONTROL
#define __CONTROL

#include <stdlib.h>
#include "Ship.h"

class Control
{
public:
	//constructor/functions
	Control()          {m_ship = NULL;m_type = CONTROLTYPE_NONE;}
	Control(Ship* ship){m_ship = ship;m_type = CONTROLTYPE_NONE;}
	virtual void Update(float dt){}
	virtual void Init(){}
	void SetShip(Ship* ship)  {m_ship = ship;m_ship->m_control = this;}
	
	enum
	{
		CONTROLTYPE_NONE,
		CONTROLTYPE_HUMAN,
		CONTROLTYPE_AI
	};
		
	//data
	Ship* m_ship;
	int   m_type;
};
#endif