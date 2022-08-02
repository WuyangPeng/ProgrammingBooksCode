#ifndef BOUNDINGRECT_H
#define BOUNDINGRECT_H

#include "BoundingVolume.h"

struct Rect4f
{
	float left, top, right, bottom;
};

class BoundingRect : public BoundingVolume
{
	public:
		BoundingRect(const float *b);
		BoundingRect(float left = 0, float top = 0, float right = 0, float bottom = 0);
		~BoundingRect(void) { }

		void Render(void) const;
		void Print(void) const;

		inline void SetBounds(float left, float top, float right, float bottom)
		{
			bounds.left = left;
			bounds.top = top;
			bounds.right = right;
			bounds.bottom = bottom;
		}
		inline void SetBounds(const float *b)
		{
			bounds.left = b[0];
			bounds.top = b[1];
			bounds.right = b[2];
			bounds.bottom = b[3];
		}
		inline Rect4f GetBounds(void) const { return bounds; }

	private:
		Rect4f bounds;
};

#endif
