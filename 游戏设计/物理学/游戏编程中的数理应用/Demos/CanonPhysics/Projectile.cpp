#include "Projectile.h"
#include "Physics.h"
#include "BoundingCircle.h"
#include "BoundingRect.h"

extern bool drawBounds;

Projectile::Projectile(void) : boundsRect(new BoundingRect)
{
	alive = false;
	bounds = new BoundingCircle;
}

Projectile::Projectile(const Projectile &p)
{
	this->operator=(p);
}

Projectile::~Projectile(void)
{
	delete boundsRect;
}

Projectile &Projectile::operator=(const Projectile &p)
{
	if (this != &p)
	{
		previousList = p.previousList;
		i_velocity = p.i_velocity;
		f_velocity = p.f_velocity;
		position = p.position;
		acceleration = p.acceleration;
		mass = p.mass;
		offset = p.offset;
		*boundsRect = *p.boundsRect;
		*bounds = *p.bounds;
	}
	return (*this);
}

void Projectile::Render(void) const
{
	glColor3f(1.0f, 1.0f, 1.0f);
	glPointSize(4.0f);
	glDisable(GL_TEXTURE_2D);

	glBegin(GL_POINTS);

		for (size_t j = 0; j < previousList.size(); j++)
			glVertex3f(previousList[j].x, previousList[j].y, -0.1f);

		glVertex3f(position.x, position.y, -0.1f);

	glEnd();

	if (drawBounds)
	{
		bounds->Render();
		boundsRect->Render();
	}

	glEnable(GL_TEXTURE_2D);
}

void Projectile::Update(float time)
{
	// Evaluate change in x and y using Equations of motion
	position.y = Physics_Util::instance().Eq4_deltax(time, i_velocity.y, acceleration.y) + offset.y;
	position.x = Physics_Util::instance().Eq4_deltax(time, i_velocity.x, acceleration.x) + offset.x;

	//f_velocity.y = Physics_Util::instance()->Eq1_vf(time, i_velocity.y, acceleration.y);
	//f_velocity.x = Physics_Util::instance()->Eq1_vf(time, i_velocity.x, acceleration.x);

	// Update the bounds
	BoundingCircle *circle = static_cast<BoundingCircle *>(bounds);
	circle->SetBounds(position.x, position.y, 0.25);

	BoundingRect *rect = static_cast<BoundingRect *>(boundsRect);
	rect->SetBounds(position.x - 0.25, position.y - 0.25, position.x + 0.25, position.y + 0.25);
}
