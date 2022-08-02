#include "Wall.h"
#include "BoundingRect.h"

#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>

extern bool drawBounds;

Wall::Wall(void)
{
	bounds = new BoundingRect;
}
Wall::~Wall(void)
{
}

void Wall::SetBounds(float left, float top, float right, float bottom)
{
	BoundingRect *rect = static_cast<BoundingRect *>(bounds);
	rect->SetBounds(left, top, right, bottom);
	position.x = left;
	position.y = bottom;
	width = right - left;
	height = top - bottom;
}

void Wall::Render(void) const
{
	if (alive)
	{
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texObj);

		glPushMatrix();
			glTranslatef(position.x, position.y, position.z);

			glBegin(GL_QUADS);
				glTexCoord2f(0, 1);
				glVertex3f(0.0f, height, 0.0f);

				glTexCoord2f(10.0f, 1);
				glVertex3f(width, height, 0.0f);

				glTexCoord2f(10.0f, 0);
				glVertex3f(width, 0.0f, 0.0f);

				glTexCoord2f(0, 0);
				glVertex3f(0.0f, 0.0f, 0.0f);
			glEnd();
			
		glPopMatrix();

		if (drawBounds)
			bounds->Render();

		glDisable(GL_TEXTURE_2D);
	}
}
