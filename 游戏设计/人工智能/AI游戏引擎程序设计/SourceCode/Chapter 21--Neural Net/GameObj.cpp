#include <GL/glut.h>
#include "Point3.h"
#include "Sphere3.h"
#include "GameObj.h"
#include "Exp.h"
#include "GameSession.h"
#include "utility.h"
#include <vector>
#include <list>

//---------------------------------------------------------
GameObj::GameObj(float _size)
{
	m_position		= Point3f(0,0,0);
    m_accelleration = Point3f(0,0,0);
    m_velocity		= Point3f(0,0,0);
    Init();
	m_size			= _size;
	m_boundSphere.r	= m_size;
}

//---------------------------------------------------------
GameObj::GameObj(const Point3f &_p, const float _angle, const Point3f &_v)
{
	m_position		= _p;
    m_velocity		= _v;
	m_angle			= _angle;
    Init();
}

//---------------------------------------------------------
GameObj::GameObj(const Point3f &_p, const float _angle)
{
    m_position		= _p;
    m_velocity		= Point3f(0,0,0);
    m_angle			= _angle;
    Init();
}

//---------------------------------------------------------
GameObj::~GameObj()
{
}

//---------------------------------------------------------
void GameObj::Init()
{
    m_accelleration = Point3f(0,0,0);
    m_angVelocity	= 0;
    m_axis			= Point3f(0,0,1);
    m_active		= true;
    m_size			= 1;
    m_boundSphere.r	= m_size;
    m_collisionFlags= OBJ_NONE;
    m_type			= OBJ_NONE;
    m_lifeTimer		= NO_LIFE_TIMER;
}

//---------------------------------------------------------
bool GameObj::IsColliding(GameObj *obj)
{
	m_boundSphere.c		 = m_position;
	obj->m_boundSphere.c = obj->m_position;
	return m_boundSphere.Intersect(obj->m_boundSphere);
}

//---------------------------------------------------------
void GameObj::Update(float dt)
{
    m_velocity  += dt*m_accelleration;
    m_position  += dt*m_velocity;
    m_angle     += dt*m_angVelocity;
    m_angle      = CLAMPDIR180(m_angle);

    if(m_position.z() !=0.0f)
    {
        m_position.z() = 0.0f;
    }
    
    if(m_lifeTimer != NO_LIFE_TIMER)
    {
        m_lifeTimer -= dt;
        if(m_lifeTimer<0.0f) 
            m_active=false;
    }
};

//---------------------------------------------------------
void GameObj::Explode()
{
	Exp *e = NULL;
	switch(m_type)
	{
		case OBJ_ASTEROID:
        case OBJ_SHIP:
        case OBJ_SAUCER:
			e			= new Exp(this);
			e->m_position	= m_position;
			Game.PostGameObj(e);
			break;		

		case OBJ_NONE:
		case OBJ_BULLET:
		case OBJ_EXP:
		case OBJ_POWERUP:
		default:
			break;
	}
}
//---------------------------------------------------------
Point3f GameObj::UnitVectorFacing()
{
	return UNITFROMANGLE(m_angle);
}; 

//---------------------------------------------------------
Point3f GameObj::UnitVectorVelocity()
{
	Point3f temp = m_velocity;
	temp.Normalize();
	return temp;
}; 
