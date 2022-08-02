#include "ProjectileManager.h"
#include "Projectile.h"
#include "ParticleEngine.h"
#include "Physics.h"
#include "CollisionManager.h"
#include "BoundingRect.h"
#include "BoundingCircle.h"

#include <algorithm>

extern HWND hWndDlg;
extern BYTE turn;
extern bool pause;
extern float pos_x_P1, pos_y_P1, pos_x_P2, pos_y_P2;
extern double T_time_P1, T_time_P2;
extern float max_height_P1, max_height_P2;
extern float launch_posx_P1, launch_posy_P1, launch_posx_P2, launch_posy_P2;

ProjectileManager::ProjectileManager(void) : elapsed_time(0.0f), projectiles(new Projectile[MAX_PROJECTILES])
{
}

ProjectileManager::~ProjectileManager(void)
{
	delete [] projectiles;
}

void ProjectileManager::ActivateProjectile(const Point2f &position, float angle, float veloc, float mass)
{
	// A better and faster implementation would be to have 2 seperate linked lists
	// of pointers into the projectiles array.  One for projectiles that are alive,
	// and one for the dead ones.

	// Using that implementaion, one would just activate the first projectile
	// on the dead list here, instead of searching to find a dead one.
	for (int i = 0; i < MAX_PROJECTILES; i++)
	{
		if (projectiles[i].alive == false)
		{
			projectiles[i].alive = true;
			projectiles[i].position = position;

			projectiles[i].offset.x = position.x;
			projectiles[i].offset.y = position.y;

			if (!turn)
			{
				launch_posx_P1 = projectiles[i].offset.x;
				launch_posy_P1 = projectiles[i].offset.y;
			}
			else
			{
				launch_posx_P2 = projectiles[i].offset.x;
				launch_posy_P2 = projectiles[i].offset.y;
			}

			projectiles[i].acceleration.x = 0.0f;
			projectiles[i].acceleration.y = -9.8f;

			projectiles[i].mass = mass;
			
			projectiles[i].i_velocity.x = GETX_COMPONENT(angle, veloc);
			projectiles[i].i_velocity.y = GETY_COMPONENT(angle, veloc);

			BoundingCircle *circle = static_cast<BoundingCircle *>(projectiles[i].GetBounds());
			circle->SetBounds(position.x, position.y, 0.25f);

			BoundingRect *rect = static_cast<BoundingRect *>(projectiles[i].boundsRect);
			rect->SetBounds(position.x - 0.25, position.y - 0.25, 
				position.x + 0.25, position.y + 0.25);

			elapsed_time = 0.0f;
			slice.Reset();
			break;
		}
	}
	// This Manager has the downfall(?) that it doesn't handle the case where none of the projectiles
	// are dead.  That means that someone would press fire but nothing would happen.  Sometimes that
	// is intended in the game, other times it is not.  In this implementation it doesn't matter.
}

void ProjectileManager::Update(void)
{
	double elapsed;
	if (!pause)
		elapsed = stopWatch.GetElapsedSeconds();
	else
		elapsed = 0.0;
	
	stopWatch.Reset();

	bool timeSlice = false;

	if (slice.GetElapsedSeconds() > 0.125f)
	{
		timeSlice = true;
		slice.Reset();
	}

	// Using the better implementation, one would simply traverse the linked list of
	// alive projectiles here and only updating them.  Here we have to go through the
	// entire array of 256 projectiles, even if none of them are active.
	//
	// However, this implementation brings us to a nice example that is very common.
	// Here's an example of an optimization many people miss.  If you know a code branch ahead
	// of time, take the time to write the extra code for a performance increase.
	// Don't be a lazy coder!
	//
	// for (int i = 0; i < NUM; i++)
	// {
	//    if (someBool)
	//       doSomething();
	//
	//    doSomethingElse();
	// }
	//
	// That loop evaluates "someBool" every iteration, when there is no chance that the value of
	// "someBool" will ever change within that loop.  It is much better to write out two different
	// code branches so that "someBool" only gets evaluated once instead of "NUM" times.
	//
	// if (someBool)
	// {
	//    for (int i = 0; i < NUM; i++)
	//    {
	//       doSomething();
	//       doSomethingElse();
	//    }
	// }
	// else
	// {
	//    for (int i = 0; i < NUM; i++)
	//       doSomethingElse();
	// }
	if (timeSlice)
	{
		double *total_time;
		float *pos_x, *pos_y;
		float *max_height;
		if (turn)
		{
			total_time = &T_time_P1;
			pos_x = &pos_x_P1;
			pos_y = &pos_y_P1;
			max_height = &max_height_P1;
		}
		else
		{
			total_time = &T_time_P2;
			pos_x = &pos_x_P2;
			pos_y = &pos_y_P2;
			max_height = &max_height_P2;
		}
		for (int i = 0; i < MAX_PROJECTILES; i++)
		{
			if (projectiles[i].alive)
			{
				projectiles[i].previousList.push_back(projectiles[i].position);
				elapsed_time += elapsed;
				projectiles[i].Update(elapsed_time);
				CollisionCheck(&projectiles[i]);

				*total_time += elapsed;
				*pos_x =  projectiles[i].position.x;// + projectiles[i].offset.x;
				*pos_y =  projectiles[i].position.y;// + projectiles[i].offset.y;
				if (*max_height < *pos_y)
					*max_height = *pos_y;
			}
		}
	}
	else
	{
		for (int i = 0; i < MAX_PROJECTILES; i++)
		{
			if (projectiles[i].alive)
			{
				elapsed_time += elapsed;
				projectiles[i].Update(elapsed_time);
				CollisionCheck(&projectiles[i]);
				if (!turn)
				{
					T_time_P1 += elapsed;
					pos_x_P1 =  projectiles[i].position.x;// + projectiles[i].offset.x;
					pos_y_P1 =  projectiles[i].position.y;// + projectiles[i].offset.y;
				}
				else
				{
					T_time_P2 += elapsed;
					pos_x_P2 =  projectiles[i].position.x;// + projectiles[i].offset.x;
					pos_y_P2 =  projectiles[i].position.y;// + projectiles[i].offset.y;
				}
			}
		}
	}


}

void ProjectileManager::Render(void) const
{
	// Using the better implementation, one would simply traverse the linked list of
	// alive projectiles here and only drawing them.
	for (int i = 0; i < MAX_PROJECTILES; i++)
	{
		if (projectiles[i].alive)
			projectiles[i].Render();
	}
}

void ProjectileManager::CollisionCheck(Projectile *proj)
{
	// Collision check
	int size = CollisionManager::instance().objectCount();
	for (int i = 0; i < size; i++)
	{
		if (proj == CollisionManager::instance().objects[i])
			continue;

		if (proj->alive && CollisionManager::instance().objects[i]->alive)
		{
			int collision = CollisionManager::instance().Collision(proj->boundsRect, CollisionManager::instance().objects[i]->GetBounds());
			
			// Test our rect
			if (collision == 1)
			{
				ParticleEngine::instance().Create(proj->position.x, proj->position.y);

				proj->f_velocity.y = Physics_Util::instance().Eq1_vf(elapsed_time, proj->i_velocity.y, proj->acceleration.y);
				proj->f_velocity.x = Physics_Util::instance().Eq1_vf(elapsed_time, proj->i_velocity.x, proj->acceleration.x);
				
				proj->i_velocity.y = Physics_Util::instance().ConMecEn_vi(CollisionManager::instance().objects[i]->elasticity, proj->f_velocity.y);
				proj->i_velocity.x = Physics_Util::instance().ConMecEn_vi(CollisionManager::instance().objects[i]->elasticity, proj->f_velocity.x);
				
				if (proj->f_velocity.x < 0)
					proj->i_velocity.x *= -1;
				
				proj->offset.y = proj->position.y;
				proj->offset.x = proj->position.x;

				elapsed_time = 0.0f;
				break;
			}

			if (collision == 2 || collision == 3)
			{
				ParticleEngine::instance().Create(proj->position.x, proj->position.y);

				proj->f_velocity.y = Physics_Util::instance().Eq1_vf(elapsed_time, proj->i_velocity.y, proj->acceleration.y);
				proj->f_velocity.x = Physics_Util::instance().Eq1_vf(elapsed_time, proj->i_velocity.x, proj->acceleration.x);
				
				proj->i_velocity.y = Physics_Util::instance().ConMecEn_vi(CollisionManager::instance().objects[i]->elasticity, proj->f_velocity.y);
				proj->i_velocity.x = Physics_Util::instance().ConMecEn_vi(CollisionManager::instance().objects[i]->elasticity, proj->f_velocity.x);
				
				if (proj->f_velocity.x > 0)
					proj->i_velocity.x *= -1;

				if (proj->f_velocity.y < 0)
					proj->i_velocity.y *= -1;
				
				proj->offset.y = proj->position.y;
				proj->offset.x = proj->position.x;

				elapsed_time = 0.0f;
				break;
			}

			// Test our circle
			if (CollisionManager::instance().Collision(proj->GetBounds(), CollisionManager::instance().objects[i]->GetBounds()))
			{
				ParticleEngine::instance().Create(proj->position.x, proj->position.y);

				proj->offset.y = proj->position.y;
				proj->offset.x = proj->position.x;

				elapsed_time = 0.0f;
				break;
			}
		}

		if (proj->position.x > 50 || proj->position.x < 0 || (abs(proj->i_velocity.x) <= 0.000000001f && abs(proj->i_velocity.y) <= 0.000000001f))
		{
			ShowWindow(hWndDlg, SW_NORMAL);
			return;
		}
	}
}

void ProjectileManager::Reset(void)
{
	for (int i = 0; i < MAX_PROJECTILES; i++)
	{
		projectiles[i].alive = false;
		projectiles[i].previousList.clear();
	}
}
