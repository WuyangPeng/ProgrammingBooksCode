#include "Entity.h"
#include "CollisionManager.h"

Entity::Entity(void) : bounds(0), alive(false), elasticity(1.0f)
{
	CollisionManager::instance().ObjectListAdd(this);
}

Entity::~Entity(void)
{
	delete bounds;
	// Delete the textures
	glDeleteTextures(1, &texObj);
}

void Entity::SetTexture(BYTE *pData, int Width, int Height)
{
	//	Creates texture object
	glGenTextures(1, &texObj);
	glBindTexture(GL_TEXTURE_2D, texObj);

	if (pData != NULL)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Width, Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pData);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_ENV, GL_MODULATE);

		delete [] pData;
	}
}

void Entity::Place(float x, float y, float z)
{
	position.x = x;
	position.y = y;
	position.z = z;
}
