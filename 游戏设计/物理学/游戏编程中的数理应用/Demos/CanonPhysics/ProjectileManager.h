// This is a little overboard for such a simple program because there can
// only possibly be 1 projectile active at a time, however in any larger
// scale program where there can be potentially an unlimited number of
// projectiles active at one time, a Projectile Manager is practically a
// must-have.  This class has most of the functionality for that kind of
// use.  In this program, most of those features remain unused.

#ifndef PROJECTILEMANAGER_H
#define PROJECTILEMANAGER_H

#include "StopWatch.h"
#include "BoundingVolume.h"

class Projectile;

class ProjectileManager
{
	public:
		void ActivateProjectile(const Point2f &position, float angle, float veloc, float mass);
		void Update(void);
		void Render(void) const;
		void CollisionCheck(Projectile *proj);
		void Reset(void);

		inline static ProjectileManager &instance(void)
		{
			static ProjectileManager inst;
			return inst;
		}

	private:
		// In any game you would adjust this number for maximum efficiency between
		// memory vs performance.  Obviously the best performance-wise would be the
		// maximum number of projectiles theoretically possible.  Perhaps the best
		// giving memory consideration would be the most that usually happen in a
		// normal, in-game situation.
		enum { MAX_PROJECTILES = 256, };

		Projectile *projectiles;
		SS_StopWatch stopWatch;
		SS_StopWatch slice;
		double elapsed_time;

		ProjectileManager(void);
		~ProjectileManager(void);
};

#endif
