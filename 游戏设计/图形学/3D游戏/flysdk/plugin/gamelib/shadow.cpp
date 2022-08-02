#include "..\..\lib\Fly3D.h"
#include "gamelib.h"

void shadow::reposition(bsp_object *obj)
{
	curobj=obj;
	flyengine->excludecollision=obj;
	hit=flyengine->collision_bsp(flyengine->bsp,obj->pos,obj->pos+vector(0,0,-flyengine->bboxdiag),TYPE_STATIC_MESH);
	flyengine->excludecollision=0;
	if(hit)
	{
		pos=flyengine->hitip+flyengine->hitmesh->faces[flyengine->hitface]->normal;
		align_z(flyengine->hitmesh->faces[flyengine->hitface]->normal);
	}
}

void shadow::draw_simple_shadow()
{
	glDepthMask(GL_FALSE);
	glBlendFunc(GL_ZERO,GL_ONE_MINUS_SRC_COLOR);
	glDisable(GL_DEPTH_TEST);

	glColor3f(
		1.0f-flyengine->shadowcolor.x,
		1.0f-flyengine->shadowcolor.y,
		1.0f-flyengine->shadowcolor.z);

	tc->use(texture);

	static vector x,y;
	x=X*sizex;
	y=Y*sizey;

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

	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glDepthMask(GL_TRUE);
}

void shadow::draw()
{
	flyengine->excludecollision=curobj;
	if (flyengine->collision_test(flyengine->bsp,flyengine->cam->pos,pos))
	if (flyengine->hitobj!=flyengine->cam)
		{
		flyengine->excludecollision=0;
		return;
		}
	flyengine->excludecollision=0;

	if(hit)
		draw_simple_shadow();
}

int shadow::get_custom_param_desc(int i,param_desc *pd)
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
		pd->data=&sizex;
		strcpy(pd->name,"sizex");
		break;
	case 2: 
		pd->type='f';
		pd->data=&sizey;
		strcpy(pd->name,"sizey");
		break;
	}
	return 3;
}
