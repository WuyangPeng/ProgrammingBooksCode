#include "Tank.h"
#include "Physics.h"
#include "BoundingRect.h"
#include "ProjectileManager.h"

extern bool drawBounds;

Tank::Tank() : force(0.0f), base_height(1.0f), base_width(1.0f), mass(1.0f), velocity(0.0f), barrel_length(1.0f)
{
 	alive = true;
	bounds = new BoundingRect;
}

Tank::~Tank()
{
}

void Tank::SetBarrelColor(COLORREF color)
{
	barrel_color.red = GetRValue(color);
	barrel_color.green = GetGValue(color);
	barrel_color.blue = GetBValue(color);
}

void Tank::Place(float x, float y, float z)
{
	Entity::Place(x, y, z);
	
	// Offset the barrel based on the base's position
	barrel_position.x = x + base_width * Physics::Halve;
	barrel_position.y = y + base_height;
	barrel_position.z = z;

	// Set the bounding rect
	BoundingRect *rect = static_cast<BoundingRect *>(bounds);
	rect->SetBounds(x, y + base_height, x + base_width, y);
}

void Tank::Render(void) const
{
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthMask(GL_FALSE);

	glBindTexture(GL_TEXTURE_2D, texObj);
	glColor3ub(255, 255, 255);
	
	// Draw the tank base
	glPushMatrix();
		glTranslatef(position.x, position.y, position.z);

		glBegin(GL_QUADS);

			glTexCoord2f(0, 0);	glVertex3f(0.0f, 0.0f, -0.1f);
			glTexCoord2f(1, 0); glVertex3f(base_width, 0.0f, -0.1f);
			glTexCoord2f(1, 1); glVertex3f(base_width, base_height, -0.1f);
			glTexCoord2f(0, 1); glVertex3f(0.0f, base_height, -0.1f);

		glEnd();

	glPopMatrix();

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	glDepthMask(GL_TRUE);
	
	glColor3ub(barrel_color.red, barrel_color.green, barrel_color.blue);

	// Draw the barrel
	glPushMatrix();
		glTranslatef(barrel_position.x, barrel_position.y, barrel_position.z);

		glBegin(GL_LINES);

			glVertex3f(0.0f, 0.0f, -0.1f);
			glVertex3f((float)cos(DEGTORAD(angle)) * barrel_length, (float)sin(DEGTORAD(angle)) * barrel_length, -0.1f);

		glEnd();
	glPopMatrix();

	// Draw the bounding volume perhaps
	if (drawBounds)
		bounds->Render();
}

void Tank::FireProjectile(void)
{
	Point2f pos;
	pos.x = (float)cos(DEGTORAD(angle)) * barrel_length + barrel_position.x;
	pos.y = (float)sin(DEGTORAD(angle)) * barrel_length + barrel_position.y;

	float accel = Physics_Util::instance().Newton2(mass,force);
	
	velocity = Physics_Util::instance().Eq5_vf(0.0f, barrel_length, accel);

	ProjectileManager::instance().ActivateProjectile(pos, DEGTORAD(angle), velocity, mass);
}
