#pragma once
#include "AIControl.h"

class Ship;
class FSMMachine;
class GameObj;

#define POWERUP_SCAN_DIST 180.0f
#define AI_MAX_SPEED_TRY  80.0f
#define APPROACH_DIST     180.0f

class FSMAIControl: public AIControl
{
public:
	//constructor/functions
	FSMAIControl(Ship* ship = NULL);
	void Update(float dt);
	void UpdatePerceptions(float dt);
	void Init();
	
	//perception data 
	//(public so that states can share it)
	GameObj*	m_nearestAsteroid;
	GameObj*	m_nearestPowerup;
	float       m_nearestAsteroidDist;
	float       m_nearestPowerupDist;
	bool        m_willCollide;
	bool        m_powerupNear;
	float       m_safetyRadius;
    float       m_maxSpeed;
    
protected:
	//data
	FSMMachine* m_machine;
};
