#include "BoundingCircle.h"
#include "Physics.h"

#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>

#include <cmath>
#include <iostream>
using namespace std;

BoundingCircle::BoundingCircle(float x, float y, float r) : BoundingVolume(BT_CIRCLE)
{
	SetBounds(x, y, r);
}

void BoundingCircle::Render(void) const
{
	glColor3f(1.0f, 1.0f, 1.0f);
	glDisable(GL_TEXTURE_2D);
	glLineWidth(1.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glPushMatrix();

		glTranslatef(position.x, position.y, -0.1f);
		glBegin(GL_POLYGON);

		for (float ang = 0; ang <= 2 * PI; ang += 0.1f)
			glVertex3f(radius * (GLfloat)cos(ang), radius * (GLfloat)sin(ang), 0);
		glEnd();

	glPopMatrix();

	glEnable(GL_TEXTURE_2D);
	glLineWidth(3.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void BoundingCircle::Print(void) const
{
	cout << "Circle";
}
