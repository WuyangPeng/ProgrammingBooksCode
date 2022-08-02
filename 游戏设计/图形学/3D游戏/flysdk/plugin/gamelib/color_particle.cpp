#include "..\..\lib\Fly3D.h"
#include "gamelib.h"

int color_particle::step(int dt)
{ 
	return particle::step(dt);
}

void color_particle::draw()
{
	glDepthMask(GL_FALSE);
	glBlendFunc(GL_ONE, GL_ONE);
	glDisable(GL_FOG);

	tc->use(texture);

	glColor3f(color.x*color.w,color.y*color.w,color.z*color.w);
	
	static vector x,y;
	x=flyengine->cam->X*size;
	y=flyengine->cam->Y*size;

	glBegin(GL_QUADS);

	glTexCoord2f(1,0);
	glVertex3f(pos.x+x.x-y.x, pos.y+x.y-y.y, pos.z+x.z-y.z);

	glTexCoord2f(1,1);
	glVertex3f(pos.x+x.x+y.x, pos.y+x.y+y.y, pos.z+x.z+y.z);

	glTexCoord2f(0,1);
	glVertex3f(pos.x+y.x-x.x, pos.y+y.y-x.y, pos.z+y.z-x.z);

	glTexCoord2f(0,0);
	glVertex3f(pos.x-x.x-y.x, pos.y+-x.y-y.y, pos.z-x.z-y.z);

	glEnd();

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	if (flyengine->fog) glEnable(GL_FOG);
	glDepthMask(GL_TRUE);
}
