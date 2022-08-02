#ifndef WALL_H
#define WALL_H

#include "Entity.h"

class Wall : public Entity
{
	public:
		Wall(void);
		~Wall(void);

		void SetBounds(float left, float top, float right, float bottom);
		void Render(void) const;

	private:
		float width, height;
};

#endif
