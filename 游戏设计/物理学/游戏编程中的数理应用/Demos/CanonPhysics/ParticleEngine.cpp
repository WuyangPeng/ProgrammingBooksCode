#include "ParticleEngine.h"
#include "Physics.h"

#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>

#include <cmath>

ParticleEngine::ParticleEngine(void)
{
	deadList.reserve(MAX_PARTICLES);
	for (int i = 0; i < MAX_PARTICLES; i++)
		deadList.push_back(Particle());
}

void ParticleEngine::Create(float _x, float _y)
{
	int size = (int)deadList.size();
	for (int i = 0; i < size; i++)
	{
		activeList.push_back(deadList.back());
		deadList.pop_back();

		// The RGBA color
		activeList[i].red = 154 / 255.0f;//(rand() % 6 + 5) / 10.0f;	// 0.5->1.0
		activeList[i].blue = 124 / 255.0f;//0.0f;
		activeList[i].green = 22 / 255.0f;//0.0f;
		activeList[i].alpha = (rand() % 51 + 50) / 100.0f;	// Higher resolution 0.5->1.0
		
		activeList[i].x = _x;
		activeList[i].y = _y;

		activeList[i].vel_x = (float)cos(DEGTORAD(rand() % 180)) / (rand() % 10 + 1);
		activeList[i].vel_y = (float)sin(DEGTORAD(rand() % 180)) / (rand() % 10 + 1);
	}
}

void ParticleEngine::Update(void)
{
	for (size_t i = 0; i < activeList.size(); i++)
	{
		// Move the particle
		activeList[i].x += activeList[i].vel_x;
		activeList[i].y += activeList[i].vel_y;

		// Dampen the particle
		activeList[i].vel_x *= 0.9f;
		activeList[i].vel_y *= 0.9f;

		// Fade the particle
		activeList[i].alpha -= 0.02f;

		if (activeList[i].alpha < 0.0f)
		{
			deadList.push_back(activeList[i]);
			activeList.erase(&activeList[i--]);
		}
	}
}

void ParticleEngine::Render(void) const
{
	glDisable(GL_TEXTURE_2D);

	glBegin(GL_POINTS);

	int size = activeList.size();
	for (int i = 0; i < size; i++)
	{
		glColor4f(activeList[i].red, activeList[i].blue, activeList[i].green, activeList[i].alpha);
		glVertex3f(activeList[i].x, activeList[i].y, -0.1f);
	}

	glEnd();

	glEnable(GL_TEXTURE_2D);
}
