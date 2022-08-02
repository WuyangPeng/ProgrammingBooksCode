#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include "Entity.h"

#include <vector>

class BoundingVolume;
class BoundingRect;
class BoundingCircle;

class CollisionManager
{
	friend class ProjectileManager;
	public:
		void ObjectListAdd(Entity *entity);
		int Collision(const BoundingVolume *object1, const BoundingVolume *object2) const;

		inline static CollisionManager &instance(void)
		{
			static CollisionManager cm;
			return cm;
		}
		inline int objectCount(void) const { return (int)objects.size(); }

	private:
		std::vector<Entity *> objects;
	
		CollisionManager(void) { }
		~CollisionManager(void) { }

		int CollisionTest(const BoundingRect *object1, const BoundingRect *object2) const;
		int CollisionTest(const BoundingCircle *object1, const BoundingCircle *object2) const;
};

#endif
