#ifndef BOUNDINGVOLUME_H
#define BOUNDINGVOLUME_H

struct Point2f
{
	float x, y;
};
struct Point3f
{
	float x, y, z;
};

enum BoundingType { BT_CIRCLE, BT_RECT, BT_LINE, };

class BoundingVolume
{
	public:
		BoundingType type;

		BoundingVolume(void) { }
		BoundingVolume(BoundingType t) : type(t) { }
		virtual ~BoundingVolume(void) { }

		virtual void Render(void) const = 0;
		virtual void Print(void) const = 0;
};

#endif
