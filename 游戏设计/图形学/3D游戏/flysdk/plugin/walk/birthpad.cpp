#include "walk.h"

void birth_pad::init()
{
	if (objmesh)
		pos=objmesh->pivotpos;
	animtime0=0;
}

int birth_pad::get_custom_param_desc(int i,param_desc *pd)
{
	if (pd!=0)
	switch(i)
	{
		case 0:
			pd->type='3';
			pd->data=&objmesh;
			strcpy(pd->name,"mesh");
			break;
		case 1:
			pd->type='3';
			pd->data=&animobj;
			strcpy(pd->name,"animobj");
			break;
		case 2:
			pd->type='i';
			pd->data=&animtime;
			strcpy(pd->name,"animtime");
			break;
	}
	return 3;
}

void birth_pad::draw()
{
	if (objmesh==0) return;

	if (node)
		{
		objmesh->color=node->color+dynlight;
		dynlight.null();
		}

	glPushMatrix();
	glTranslatef(pos.x,pos.y,pos.z);
	glMultMatrixf((float *)&mat);
	objmesh->draw();
	if (animobj && flyengine->cur_time-animtime0<animtime)
	{
		glDepthMask(GL_FALSE);
		glDisable(GL_CULL_FACE);
		glBlendFunc(GL_ONE,GL_ONE);
		animobj->scrollu=(float)(flyengine->cur_time-animtime0)/animtime;
		animobj->scrollv=(float)(flyengine->cur_time-animtime0)/(-2*animtime);
		animobj->draw();
		glDepthMask(GL_TRUE);
		glEnable(GL_CULL_FACE);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	}
	glPopMatrix();
}

int birth_pad::message(vector& p,float rad,int msg,int param,void *data)
{
	if (msg==FLYOBJM_ILLUM)
	{
		float fac=(p-pos).length()/rad;
		if (fac<1.0f)
			dynlight+=*((vector *)data)*(1.0f-fac);
	}

	return 1;
}
