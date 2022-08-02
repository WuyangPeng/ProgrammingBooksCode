#ifndef __BULLET
#define __BULLET

#include "Ship.h"
#include "GameObj.h"

#define BULLET_MAX_LIFE 1.0f
#define ASTEROID_SCORE_VAL 100

class Bullet : public GameObj
{
public:
	//constructors/functions
	Bullet(Ship* _parent, const Point3f &_p, const float _angle);
  	Bullet(Ship* _parent, const Point3f &_p, const float _angle, const Point3f &_v);

	void Draw();
	void Update(float dt);
	void Init();
	void DoCollision(GameObj *obj);

	//data
	Ship*	m_parent;
};

#endif