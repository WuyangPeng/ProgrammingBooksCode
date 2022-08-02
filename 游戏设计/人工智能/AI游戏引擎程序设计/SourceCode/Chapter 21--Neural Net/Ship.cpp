#include <GL/glut.h>
#include "GameObj.h"
#include "Bullet.h"
#include "Powerup.h"
#include "Ship.h"
#include "Exp.h"
#include "GameSession.h"
#include "utility.h"

//---------------------------------------------------------
Ship::Ship(int size):
GameObj(size)
{
	m_shotPowerLevel   = 0;
	m_type             = GameObj::OBJ_SHIP;
	m_collisionFlags   = GameObj::OBJ_ASTEROID;

	Init();
}

//---------------------------------------------------------
void Ship::Init()
{
	m_invincibilityTimer= 3.0f;
	m_thrust           = false;
	m_revThrust        = false;
	m_position		   = Point3f(256,256,0);
	m_velocity		   = Point3f(0,0,0);
	m_angle			   = 0;
	m_angVelocity	   = 0;
	m_activeBulletCount= 0;
    m_agThrust         = false;
    m_tractor          = false;
    m_agNorm           = Point3f(0,0,0);
    m_tractorNorm      = Point3f(0,0,0);
    m_shotPowerLevel   = 0;
    m_willCollide      = false;
    
}

//---------------------------------------------------------
void Ship::Update(float dt)
{ 
    Point3f na;
    m_accelleration=Point3f(0,0,0);
    if(m_thrust)
    {
        na=UnitVectorFacing();
        na*=MAX_SHIP_SPEED;
        m_accelleration+=na;
    }

    if(m_revThrust)
    {
        na=UnitVectorFacing();
        na*=-MAX_SHIP_SPEED;
        m_accelleration+=na;
    }

    if(m_agThrust)
        AGMove(dt);
    m_agNorm.x() = 0.0f;
    m_agNorm.y() = 0.0f;
    m_agNorm.z() = 0.0f;

    if(m_tractor)
        ApplyTractorBeam(dt);
    
    if(m_invincibilityTimer > 0)
        m_invincibilityTimer -= dt;
    GameObj::Update(dt);
}

//---------------------------------------------------------
void Ship::AGThrustOn(Point3f &offset)
{
    m_agThrust = true;
    m_agNorm = offset.Normalize();
    m_agNorm;
}

//---------------------------------------------------------
void Ship::AGThrustAccumulate(Point3f &offset)
{
    m_agThrust = true;
    m_agNorm += offset;
}

//---------------------------------------------------------
void Ship::AGMove(float dt)
{
    //antigravity move, no acceleration or velocity
    //directly affects position
    m_position	+= dt*MAX_AG_SHIP_SPEED*m_agNorm.Normalize();
}

//---------------------------------------------------------
void Ship::TractorBeamOn(Point3f &offset)
{
    m_tractor = true;
    m_tractorNorm = offset;
    m_tractorNorm.Normalize();
}

//---------------------------------------------------------
void Ship::ApplyTractorBeam(float dt)
{
    //is anybody intersecting the tractor line?
    //have to pass back to Game object, which is keeper of 
    //all the objects in the game world
    Point3f endOfTractor = m_position+ m_tractorNorm*MAX_TRACTOR_POWER;
    Game.ApplyForce(GameObj::OBJ_POWERUP,m_position,endOfTractor,m_tractorNorm*MAX_TRACTOR_POWER, dt);
}

//---------------------------------------------------------
int Ship::MaxBullet()
{
	int num = 0;
	switch(m_shotPowerLevel)
	{
		case 3:
			num = 25;
			break;
		case 2:
			num = 20;
			break;
		case 1:
			num = 15;
			break;
		case 0:
		default:
			num = 10;
			break;
	}
	return num;
}

//---------------------------------------------------------
void Ship::Shoot(float angle)
{
    if(angle == -1)
        angle = m_angle;
    
	if(m_activeBulletCount > MaxBullet())
  		return;
	
	Bullet *bb;
	switch(m_shotPowerLevel)
	{
		case 3:
			m_activeBulletCount+=4;
			bb =new Bullet(this,m_position,angle-180.0f);
			Game.PostGameObj(bb);
			bb =new Bullet(this,m_position,angle);
			Game.PostGameObj(bb);
			bb =new Bullet(this,m_position,angle-90.0f);
			Game.PostGameObj(bb);
			bb =new Bullet(this,m_position,angle+90.0f);
			Game.PostGameObj(bb);
			break;
		case 2:
			m_activeBulletCount+=3;
			bb =new Bullet(this,m_position,angle-180.0f);
			Game.PostGameObj(bb);
			bb =new Bullet(this,m_position,angle);
			Game.PostGameObj(bb);
			bb =new Bullet(this,m_position,angle-90.0f);
			Game.PostGameObj(bb);
			break;
		case 1:
			m_activeBulletCount+=2;
			bb =new Bullet(this,m_position,angle-180.0f);
			Game.PostGameObj(bb);
			bb =new Bullet(this,m_position,angle);
			Game.PostGameObj(bb);
			break;
		case 0:
		default:
			m_activeBulletCount++;
			bb =new Bullet(this,m_position,angle);
			Game.PostGameObj(bb);
			break;

	}
}

//---------------------------------------------------------
void Ship::Draw()
{ 
	//just a triangle
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glTranslate(m_position);
	glRotatef(m_angle,0,0,1);
    glScalef(m_size,m_size,m_size);
    if(m_invincibilityTimer > 0)
	{
		//blinking dashed lines
		static unsigned short flag;
        //rolling dashed line
        if(flag == 0xff00)
            flag = 0x0ff0;
        else if(flag == 0x0ff0)
            flag = 0x00ff;
        else if(flag == 0x00ff)
            flag = 0xf00f;
        else
            flag = 0xff00;
        glEnable(GL_LINE_STIPPLE);
		glLineStipple (1, flag);
        glBegin(GL_LINE_LOOP);
        if(m_willCollide)
            glColor3f(1,0,0);
        else
            glColor3f(.8,.8,.8);
        glVertex3f(-3,-2,0);
        glVertex3f( 4,0,0);
        glVertex3f(-3,2,0);
        glEnd();
        glDisable(GL_LINE_STIPPLE);
	}
	else
	{
		//solid triangle
		glBegin(GL_LINE_LOOP);
        if(m_willCollide)
            glColor3f(1,0,0);
        else
            glColor3f(.8,.8,.8);
        glVertex3f(-3,-2,0);
		glVertex3f( 4,0,0);
		glVertex3f(-3,2,0);
		glEnd();
	}
	if(m_thrust)
	{
		glColor3f(.8,.4,.1);
		glBegin(GL_LINE_STRIP);
		glVertex3f(-2,-1,0);
		glVertex3f(-4,0,0);
		glVertex3f(-2,1,0);
		glEnd();
	}
	if(m_revThrust)
	{
		glColor3f(.8,.4,.1);
		glBegin(GL_LINE_STRIP);
		glVertex3f(3, 1,0);
		glVertex3f(5, 0,0);
		glVertex3f(3,-1,0);
		glEnd();
	}
    if(m_tractor)
    {
        glColor3f(.1,.9,.1);
        glBegin(GL_LINE_STRIP);
        glVertex3f(0, MAX_TRACTOR_POWER,0);
        glVertex3f(0, 0,0);
        glEnd();
    }
	glEnable(GL_LIGHTING);
    glPopMatrix();
}

//---------------------------------------------------------
void Ship::DoCollision(GameObj *obj)
{
    //just take myself out
    Game.m_respawnTimer = 2.0f;
    m_active=false;
    Game.KillShip(this);
}

//---------------------------------------------------------
bool Ship::IsColliding(GameObj *obj)
{
    //only collide if you're not invincible
    if(m_invincibilityTimer > 0)
        return false;
    return GameObj::IsColliding(obj);
}

//---------------------------------------------------------
void Ship::Stop()
{
    m_velocity.x() = 0.0f;
    m_velocity.y() = 0.0f;
    m_velocity.z() = 0.0f;
}

//---------------------------------------------------------
void Ship::Hyperspace()
{
    m_position.x() = randflt()*Game.m_screenW;
    m_position.y() = randflt()*Game.m_screenH;
}

//---------------------------------------------------------
void Ship::GetPowerup(int powerupType)
{
    switch(powerupType)
    {
    case Powerup::POWERUP_SHOT:
        if(m_shotPowerLevel < MAX_SHOT_LEVEL) 
            m_shotPowerLevel++;
        break;
    default:
        break;
    }
}

//---------------------------------------------------------
float Ship::GetClosestGunAngle(float angle)
{
    if(fabsf(angle)< 45 || m_shotPowerLevel == 0)
        return m_angle;
    if(fabsf(angle)> 135 && m_shotPowerLevel > 0)
        return m_angle+180;
    if(angle < 0 && m_shotPowerLevel >1)
        return m_angle-90;
    if(angle > 0 && m_shotPowerLevel >2)
        return m_angle+90;
    
    return m_angle;
}

//---------------------------------------------------------
float Ship::GetClosestGunApproachAngle(float angle)
{
    if(fabsf(angle) > 90 && m_shotPowerLevel != 0)
        return m_angle+180;
    return m_angle;
}

//---------------------------------------------------------
void Ship::TurnLeft()
{
    m_angVelocity =  MAX(120.0f,320.0f/Game.m_timeScale);
}

//---------------------------------------------------------
void Ship::TurnRight()
{
    m_angVelocity = MIN(-120.0f,-320.0f/Game.m_timeScale);
}

//---------------------------------------------------------
bool Ship::IsTurningRight()
{
    return m_angVelocity < 0.0f;
}

//---------------------------------------------------------
bool Ship::IsTurningLeft()
{
    return m_angVelocity > 0.0f;
}
