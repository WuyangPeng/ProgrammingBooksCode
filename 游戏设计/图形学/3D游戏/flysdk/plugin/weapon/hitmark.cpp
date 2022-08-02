#include "..\..\lib\Fly3D.h"
#include "weapon.h"

int hitmark::step(int dt)
{
	if (node==0)
		life=-1;
	else
	{
	life-=dt;
	if (mode)
		{
		pos.z+=vel.z*dt;
		return 1;
		}
	}
	return 0;
}

void hitmark::draw()
{
	if (texture==-1 || node==0)
		return;
	tc->use(texture);

	float transp;
	if (life<fadetime)
		if (life>=0)
			transp=(float)life/fadetime;
		else transp=0.0f; 
	else transp=1.0f;

	glDepthMask(GL_FALSE);

	if (flyengine->piclib[texture]->bytespixel!=4)
	{
		glBlendFunc(GL_ZERO,GL_ONE_MINUS_SRC_COLOR);
		glColor3f(transp,transp,transp);
	}
	else
	{
		glColor4f(node->color.x+dynlight.x,node->color.y+dynlight.y,node->color.z+dynlight.z,transp);
		dynlight.null();
	}

	static vector x,y;
	if (mode)
	{
		x=flyengine->cam->X*size;
		y=flyengine->cam->Y*size;
	}
	else 
	{
		x=X*size;
		y=Y*size;
	}

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

	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glDepthMask(GL_TRUE);
}

bsp_object *hitmark::clone()
{
	hitmark *tmp=new hitmark;
	*tmp=*this;
	tmp->source=this;
	return tmp;
}

int hitmark::get_custom_param_desc(int i,param_desc *pd)
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
			pd->type='i';
			pd->data=&fadetime;
			strcpy(pd->name,"fadetime");
			break;
	}
	return 3;
}

int hitmark::message(vector& p,float rad,int msg,int param,void *data)
{
	if (msg==FLYOBJM_ILLUM)
	{
		float fac=(p-pos).length()/rad;
		if (fac<1.0f)
			dynlight+=*((vector *)data)*(1.0f-fac);
	}

	return 1;
}
