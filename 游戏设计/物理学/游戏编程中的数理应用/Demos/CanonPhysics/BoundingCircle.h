#ifndef BOUNDINGCIRCLE_H
#define BOUNDINGCIRCLE_H

#include "BoundingVolume.h"

class BoundingCircle : public BoundingVolume
{
	public:
		BoundingCircle(float x = 0, float y = 0, float r = 0);
		~BoundingCircle(void) { }

		void Render(void) const;
		void Print(void) const;

		inline void SetBounds(float x, float y, float r)
		{
			position.x = x;
			position.y = y;
			radius = r;
		}
		inline void SetCenter(float x, float y)
		{
			position.x = x;
			position.y = y;
		}
		inline void SetRadius(float r) { radius = r; }

	private:
		Point2f position;
		float radius;
};

#endif
