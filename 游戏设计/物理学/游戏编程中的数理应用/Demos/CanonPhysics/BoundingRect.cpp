#include "BoundingRect.h"

#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>

#include <iostream>
using namespace std;

BoundingRect::BoundingRect(const float *b) : BoundingVolume(BT_RECT)
{
	SetBounds(b);
}

BoundingRect::BoundingRect(float left, float top, float right, float bottom) : BoundingVolume(BT_RECT)
{
	SetBounds(left, top, right, bottom);
}

void BoundingRect::Render(void) const
{
	// Set the color to white
	glColor3f(1.0f, 1.0f, 1.0f);
	glDisable(GL_TEXTURE_2D);
	glLineWidth(1.0f);

	glBegin(GL_LINE_LOOP);
		glVertex3f(bounds.left, bounds.top, -0.1f);
		glVertex3f(bounds.right, bounds.top, -0.1f);
		glVertex3f(bounds.right, bounds.bottom, -0.1f);
		glVertex3f(bounds.left, bounds.bottom, -0.1f);
	glEnd();

	glLineWidth(3.0f);
	glEnable(GL_TEXTURE_2D);
}

void BoundingRect::Print(void) const
{
	cout << "Rect";
}
