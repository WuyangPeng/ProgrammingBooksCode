#include <GL/glut.h>
#include "GameObj.h"
#include "Bullet.h"
#include "Powerup.h"
#include "Saucer.h"
#include "Exp.h"
#include "GameSession.h"
#include "utility.h"

//---------------------------------------------------------
Saucer::Saucer(int size):
Ship(size)
{
    m_type           = GameObj::OBJ_SAUCER;
    Init();
}

//---------------------------------------------------------
void Saucer::Init()
{
    Ship::Init();    
}

//---------------------------------------------------------
void Saucer::Shoot(float angle)
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
			bb =new Bullet(this,m_position,angle-10.0f);
			Game.PostGameObj(bb);
			bb =new Bullet(this,m_position,angle+10.0f);
			Game.PostGameObj(bb);
			break;
		case 2:
            m_activeBulletCount+=3;
            bb =new Bullet(this,m_position,angle+10.0f);
			Game.PostGameObj(bb);
			bb =new Bullet(this,m_position,angle);
			Game.PostGameObj(bb);
			bb =new Bullet(this,m_position,angle-10.0f);
			Game.PostGameObj(bb);
			break;
		case 1:
            m_activeBulletCount+=2;
            bb =new Bullet(this,m_position,angle-10.0f);
			Game.PostGameObj(bb);
			bb =new Bullet(this,m_position,angle);
			Game.PostGameObj(bb);
			break;
		case 0:
		default:
            m_activeBulletCount++;
			bb =new Bullet(this,m_position,angle);//,UnitVectorFacing()*BULLET_SPEED);
			Game.PostGameObj(bb);
			break;

	}
}

//---------------------------------------------------------
void Saucer::Draw()
{ 
	//a flattened diamond
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glTranslate(m_position);
	glRotatef(90,0,0,1);
    glScalef(m_size,m_size,m_size);
	if(m_invincibilityTimer > 0)
	{
        //rolling dashed line
        static unsigned short sflag;
        if(sflag == 0xff00)
            sflag = 0x0ff0;
        else if(sflag == 0x0ff0)
            sflag = 0x00ff;
        else if(sflag == 0x00ff)
            sflag = 0xf00f;
        else
            sflag = 0xff00;
        glEnable(GL_LINE_STIPPLE);
		glLineStipple (1, sflag);
        glBegin(GL_LINE_LOOP);
        glColor3f(.8,.8,.8);
        glVertex3f(  0,-7,0);
        glVertex3f(  2, 0,0);
        glVertex3f(  0, 7,0);
        glVertex3f( -2, 0,0);
        glEnd();
        glDisable(GL_LINE_STIPPLE);
	}
	else
	{
		glBegin(GL_LINE_LOOP);
		glColor3f(.8,.8,.8);
		glVertex3f(  0,-7,0);
		glVertex3f(  2, 0,0);
        glVertex3f(  0, 7,0);
        glVertex3f( -2, 0,0);
		glEnd();
	}
	if(m_agThrust)
	{
        //rolling dashed line
        static unsigned short s2flag;
        if(s2flag == 0xff00)
            s2flag = 0x0ff0;
        else if(s2flag == 0x0ff0)
            s2flag = 0x00ff;
        else if(s2flag == 0x00ff)
            s2flag = 0xf00f;
        else
            s2flag = 0xff00;
        glEnable(GL_LINE_STIPPLE);
        glLineStipple (1, s2flag);
        glColor3f(.8,.4,.1);
		glBegin(GL_LINE_STRIP);
		glVertex3f(0,-7,0);
		glVertex3f(0,7,0);
		glEnd();
        glDisable(GL_LINE_STIPPLE);
    }
    if(m_tractor)
    {
        glRotatef(CALCDIR(m_tractorNorm),0,0,1);
        glColor3f(.1,.9,.1);
        glBegin(GL_LINE_STRIP);
        glVertex3f(0, MAX_TRACTOR_POWER,0);
        glVertex3f(0, 0,0);
        glEnd();
    }
    
	glEnable(GL_LIGHTING);
	glPopMatrix();
}
