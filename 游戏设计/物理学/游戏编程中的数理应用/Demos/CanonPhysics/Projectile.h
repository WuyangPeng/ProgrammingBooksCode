#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Entity.h"
#include "BoundingVolume.h"

#include <vector>

class Projectile : public Entity
{
	public:	
		std::vector<Point2f> previousList;
		BoundingVolume *boundsRect;
		Point2f i_velocity;
		Point2f f_velocity;
		Point2f position;
		Point2f acceleration;
		Point2f offset;
		float mass;

	public:
		Projectile(void);
		Projectile(const Projectile &p);
		~Projectile(void);
		Projectile &operator=(const Projectile &p);

		void Render(void) const;
		void Update(float time);
};

#endif
