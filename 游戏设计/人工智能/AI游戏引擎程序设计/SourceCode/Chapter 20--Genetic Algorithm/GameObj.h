#ifndef __GAMEOBJ
#define __GAMEOBJ
#include <math.h>
#include "Point3.h"
#include "Sphere3.h"
#pragma warning(disable: 4786)
#include <vector>
#include <list>

#define NO_LIFE_TIMER 99999

using namespace std;

class Point3;
class Sphere3;

class GameObj
{
public:
	//constructors/functions
	GameObj(float _size = 1);
    GameObj(const Point3f &_p, const float _angle);
    GameObj(const Point3f &_p, const float _angle, const Point3f &_v);
    ~GameObj();
	virtual void Draw(){}
    virtual void Init();
	virtual void Update(float dt);
	virtual bool IsColliding(GameObj *obj);
	virtual void DoCollision(GameObj *obj) {m_active = false;}
	virtual void Explode();
	Point3f UnitVectorFacing();//unit vector in facing direction
	Point3f UnitVectorVelocity();//unit vector in velocity direction
    

	enum//collision flags/object types
	{
		OBJ_NONE		= 0x00000001,
		OBJ_ASTEROID	= 0x00000002,
        OBJ_SHIP		= 0x00000004,
		OBJ_BULLET		= 0x00000008,
		OBJ_EXP			= 0x00000010,
		OBJ_POWERUP		= 0x00000020,
		OBJ_TARGET      = 0x00000040,
        OBJ_SAUCER		= 0x00000080
    };
	
	//data
	Point3f		m_position;	  
	Point3f		m_axis;	  
	float		m_angle;  
	Point3f		m_velocity;  
    Point3f     m_accelleration;
    float		m_angVelocity;
    bool		m_active; 
	bool		m_explodes; 
	float		m_size;
	Sphere3f	m_boundSphere;
	int			m_type;
	unsigned int m_collisionFlags;
	float		m_lifeTimer;

};

#endif