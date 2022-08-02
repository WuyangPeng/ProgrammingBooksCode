#ifndef ENTITY_H
#define ENTITY_H

#include "BoundingVolume.h"

#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>

class Entity
{
	public:
		bool alive;
		float elasticity;

		Entity(void);
		virtual ~Entity(void);

		void SetTexture(BYTE *pData, int Width, int Height);
		virtual void Place(float x, float y, float z = -0.1f);
		virtual void Render(void) const = 0;

		inline GLuint GetTexture(void) const { return texObj; }
		inline BoundingVolume *GetBounds(void) const { return bounds; }

	protected:
		// The bounding volume
		BoundingVolume *bounds;

		// The texture and coords
		GLuint texObj;
		GLfloat texCoords[4];
		
		// Position
		Point3f position;
};

#endif
