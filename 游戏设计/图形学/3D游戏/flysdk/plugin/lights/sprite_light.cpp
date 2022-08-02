#include "../../lib/Fly3D.h"
#include "lights.h"

int sprite_light::step(int dt)
{
	if (mode&2)
		{
		life-=dt;
		if (directx->mpmode!=FLYMP_SERVER)
			{
			size+=dt*grow;
			if (mode&4)
				if (life<=0)
					color.w=0;
				else color.w=(float)life/source->life;
			}
		}
	return 0;
}

int sprite_light::get_custom_param_desc(int i,param_desc *pd)
{
	if (pd!=0)
	switch(i)
	{
		case 0:
			pd->type='p';
			pd->data=&texture;
			strcpy(pd->name,"texture");
			break;
		case 1:
			pd->type='f';
			pd->data=&size;
			strcpy(pd->name,"size");
			break;
		case 2:
			pd->type='c';
			pd->data=&color;
			strcpy(pd->name,"color");
			break;
		case 3:
			pd->type='f';
			pd->data=&grow;
			strcpy(pd->name,"grow");
			break;
		case 4:
			pd->type='f';
			pd->data=&color.w;
			strcpy(pd->name,"transp");
			break;
		case 5:
			pd->type='i';
			pd->data=&mode;
			strcpy(pd->name,"mode");
			break;
	}
	return 6;
}

void sprite_light::draw()
{
	static vector x,y,v;
	if (mode&1)
		{
		x=X*size;
		y=Y*size;
		}
	else
		{
		x=flyengine->cam->X*size;
		y=flyengine->cam->Y*size;
		}

	glDisable(GL_CULL_FACE);
	glBlendFunc(GL_ONE,GL_ONE);
	glDepthMask(GL_FALSE);
	glDisable(GL_FOG);

	glColor3f(color.x*color.w,color.y*color.w,color.z*color.w);

	tc->use(texture);

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

	glEnable(GL_CULL_FACE);
	glDepthMask(GL_TRUE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	if (flyengine->fog) glEnable(GL_FOG);
}
