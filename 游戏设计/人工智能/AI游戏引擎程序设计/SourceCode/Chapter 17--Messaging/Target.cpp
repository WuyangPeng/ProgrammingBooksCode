#include <GL/glut.h>
#include "Target.h"

//---------------------------------------------------------
Target::Target():
GameObj()
{
	m_type = GameObj::OBJ_TARGET;
	m_collisionFlags = GameObj::OBJ_NONE;
}

Target::~Target()
{
    int i=0;
    i+=34;
    i--;
}

//---------------------------------------------------------
void Target::Draw()
{
	//just an "X"
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glTranslate(m_position);
	glRotatef(m_angle,0,0,1);
	glScalef(m_size,m_size,m_size);
	

	glBegin(GL_LINES);
	glColor3f( .8,.4,.1);
	glVertex3f(-5, 5, 0);
	glVertex3f( 5,-5, 0);
	glEnd();

	glBegin(GL_LINES);
	glColor3f( .8,.4,.1);
	glVertex3f( 5, 5, 0);
	glVertex3f(-5,-5, 0);
	glEnd();
	
	glEnable(GL_LIGHTING);
	glPopMatrix();
}
