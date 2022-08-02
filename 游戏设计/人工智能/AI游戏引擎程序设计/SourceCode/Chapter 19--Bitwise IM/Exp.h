#ifndef __EXP
#define __EXP

#include "GameObj.h"

#define EXP_MAX_LIFE 1.0f

class Exp : public GameObj
{
public:
	//constructors/functions
	Exp(GameObj* parent = NULL);
	void Draw();
	void Init();

private:
	//data
	int	m_parentType;
	int	m_parentAngle;
};
#endif