#include "AIControl.h"
#include "Ship.h"

//---------------------------------------------------------
AIControl::AIControl(Ship* ship):
Control(ship)
{
	if(m_ship)
		m_ship->m_control = this;
	m_type = CONTROLTYPE_AI;

	m_debugTxt = new char[30];
    m_target   = NULL;
}

void AIControl::Update(float dt)
{
	//put AI code here
}
