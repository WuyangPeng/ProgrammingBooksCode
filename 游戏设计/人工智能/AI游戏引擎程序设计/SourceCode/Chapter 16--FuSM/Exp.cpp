#include <GL/glut.h>
#include "Exp.h"
#include "utility.h"

//---------------------------------------------------------
Exp::Exp(GameObj* parent):
GameObj(),
m_parentAngle(0)
{
	if(parent)
	{	m_parentType  = parent->m_type;
		m_parentAngle = parent->m_angle;
	}
	Init();
}

//---------------------------------------------------------
void Exp::Init()
{
	m_lifeTimer		= EXP_MAX_LIFE;
	m_type			= GameObj::OBJ_EXP;
}

//---------------------------------------------------------
void Exp::Draw()
{
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glTranslate(m_position);
	glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE);                    
    
	if(m_parentType == GameObj::OBJ_ASTEROID)
	{
		float size=(1.0f-m_lifeTimer)*20.0f;
		glScalef(size,size,size);

		const int nside=18;
		glBegin(GL_TRIANGLE_FAN);
		glColor4f(.5, .1, .1,0);
		glVertex3f(0,0,0);
		glColor4f(.9,.9,.3,0.6f);
		for(int i=0;i<=nside;i++)
			glVertex3f(cos(float(i)*M_PI*2.0/nside),sin(float(i)*M_PI*2.0/nside),0.0);
		glEnd();
	}
    else if(m_parentType == GameObj::OBJ_SHIP)//ship explosion
	{
        float size=(1.0f-m_lifeTimer)*15.0f;
       	glRotatef(m_parentAngle,0,0,1);
        glScalef(size,size,size);

        glBegin(GL_TRIANGLE_FAN);
        
        glColor4f(0.5f, 0.1f, 0.1f, 0.f);
        glVertex3f(0.f, 0.f, 0.f);
        
        glColor4f(0.9f, 0.9f, 0.3f, 6.f);

//        glColor3f(.9,.9,.3);
		glVertex3f(-3,-2,0);
		glVertex3f( 4,0,0);
		glVertex3f(-3,2,0);
		glVertex3f(-3,-2,0);
		glEnd();
	}
    else//saucer explosion
    {
        float size=(1.0f-m_lifeTimer)*10.0f;
        glRotatef(90,0,0,1);
        glScalef(size,size,size);
        
        glBegin(GL_TRIANGLE_FAN);
        
        glColor4f(0.5f, 0.1f, 0.1f, 0.f);
        glVertex3f(0.f, 0.f, 0.f);
        
        glColor4f(0.9f, 0.9f, 0.3f, 6.f);
        
        glVertex3f(2.f, 0.f, 0.f);
        glVertex3f(0.f, 7.f, 0.f);
        glVertex3f(-2.f, 0.f, 0.f);
        glVertex3f(0.f, -7.f, 0.f);
        glVertex3f(2.f, 0.f, 0.f);
        
        glEnd();
    }
	glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);
	glPopMatrix();
}
