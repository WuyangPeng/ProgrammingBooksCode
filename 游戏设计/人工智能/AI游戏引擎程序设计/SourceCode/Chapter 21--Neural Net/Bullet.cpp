#include <GL/glut.h>
#include "GameObj.h"
#include "Bullet.h"
#include "GameSession.h"
//#include "TestSession.h"
#include "utility.h"

//---------------------------------------------------------
Bullet::Bullet(Ship* _parent,const Point3f &_p, const float _angle):
GameObj(_p,_angle),
m_parent(_parent)
{
	Point3f vel(cos(M_PI*m_angle/180.0),sin(M_PI*m_angle/180.0),0);
	vel *= BULLET_SPEED;
	m_velocity = vel;
    m_size = 2.0f;
	Init();
}

//---------------------------------------------------------
Bullet::Bullet(Ship* _parent,const Point3f &_p, const float _angle, const Point3f &_v):
GameObj(_p,_angle,_v),
m_parent(_parent)
{
	Init();
}

//---------------------------------------------------------
void Bullet::Init()
{
	m_type = GameObj::OBJ_BULLET;
	m_collisionFlags = GameObj::OBJ_ASTEROID;
	m_lifeTimer = BULLET_MAX_LIFE;
}

//---------------------------------------------------------
void Bullet::Draw()
{
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glTranslate(m_position);
	glRotatef(m_angle,0,0,1);
    glScalef(m_size,m_size,m_size);
    
	glBegin(GL_LINES);
	glColor3f(.5, 1, 1);
	glVertex3f(4.0,0,0);
	glColor3f(0.,.3,.3);
	glVertex3f(0.0,0,0);
	glEnd();
	
	glEnable(GL_LIGHTING);
	glPopMatrix();
}

//---------------------------------------------------------
void Bullet::Update(float dt)
{
	GameObj::Update(dt);
	if(m_lifeTimer<0.0f) 
	{
		if(m_parent)
			m_parent->TerminateBullet();
	}
}

//---------------------------------------------------------
void Bullet::DoCollision(GameObj *obj)
{
	//take both me and the other object out
 	if(obj && obj->m_active)
	{
		obj->Explode();
		obj->DoCollision(this);
	}

	m_active=false;
	if(m_parent)
	{
		Game.IncrementScore(ASTEROID_SCORE_VAL);
		m_parent->TerminateBullet();
	}
}

