#include "CollisionManager.h"
#include "BoundingRect.h"
#include "BoundingCircle.h"

#include <iostream>
using namespace std;

void CollisionManager::ObjectListAdd(Entity *entity)
{
	objects.push_back(entity);
}

int CollisionManager::Collision(const BoundingVolume *object1, const BoundingVolume *object2) const
{
	switch (object1->type)
	{
		case BT_RECT:
		{
			if (object2->type == BT_RECT)
				return CollisionTest(static_cast<const BoundingRect *>(object1),
					static_cast<const BoundingRect *>(object2));

			break;
		}
		case BT_CIRCLE:
		{
			if (object2->type == BT_CIRCLE)
				return CollisionTest(static_cast<const BoundingCircle *>(object1),
					static_cast<const BoundingCircle *>(object2));

			break;
		}
		default:
			cout << "WARNING: Invalid bounding type(1) - " << object1->type << " - passed into Collision function." << endl;
	}

	return false;
}

// Rect to Rect
int CollisionManager::CollisionTest(const BoundingRect *object1, const BoundingRect *object2) const
{
	Rect4f one = object1->GetBounds();
	Rect4f two = object2->GetBounds();

	// Do the objects collide
	if (one.right < two.left)
		return 0;
	if (one.bottom > two.top)
		return 0;
	if (one.left > two.right)
		return 0;
	if (one.top < two.bottom)
		return 0;

	// At this point we know that the objects collide, we need to know which side of the volume the collision occurs
	if ((one.right < two.right && one.left < two.right) && (one.left > two.left && one.right > two.left) && 
		(one.bottom < two.top))
		return 1;

	if ((one.top < two.top && one.bottom < two.top) && (one.top > two.bottom && one.bottom > two.bottom) && 
		(one.right > two.left))
		return 2;

	if ((one.top < two.top && one.bottom < two.top) && (one.top > two.bottom && one.bottom > two.bottom) && 
		(one.left < two.right))
		return 3;

	return 0;	
}

// Circle to Circle
//
// Not Implemented.
int CollisionManager::CollisionTest(const BoundingCircle *object1, const BoundingCircle *object2) const
{
	object1->Print();
	cout << " to ";
	object2->Print();
	cout << endl;

	return false;
}
