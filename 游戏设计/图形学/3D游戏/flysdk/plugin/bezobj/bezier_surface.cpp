#include "..\..\lib\Fly3D.h"
#include "bezobj.h"

void bezier_surface::init()
{
	if (patch&&source)
	{
	pos=patch->pivot;
	patch->build_surface();
	if (objmesh)
		delete objmesh;
	objmesh=patch->build_mesh();
	}
}

bsp_object *bezier_surface::clone()
{
	bezier_surface *tmp=new bezier_surface;
	*tmp=*this;
	tmp->source=this;
	return tmp;
}

int bezier_surface::get_custom_param_desc(int i,param_desc *pd)
{
	if (pd!=0)
	switch(i)
	{
	case 0:
		pd->type='h';
		pd->data=&patch;
		strcpy(pd->name,"patch");
		break;
	}
	return 1;
}

void bezier_surface::draw()
{
	if (patch)
	{
		glPushMatrix();
		glTranslatef(pos.x,pos.y,pos.z);
		glMultMatrixf((float *)&mat);

		int i=((int)(flyengine->cam->pos-pos).length());
		int d=(int)flyengine->viewmaxdist;

		i-=(d>>1);
		if (i<0)
			patch->draw(0);
		else 
		{
			i-=(d>>2);
			if (i<0)
				patch->draw(1);
			else
				patch->draw(2);
		}

		glPopMatrix();
	}
}

int bezier_surface::message(vector& p,float rad,int msg,int param,void *data)
{
	if (msg==FLYOBJM_ILLUM && (flyengine->mapmode&MAPPING_LIGHTMAP))
		patch->illuminate((p-pos)*mat_t,rad,*((vector *)data),param);
	else 
	if (msg==FLYOBJM_CHANGEPARAM)
		if (param>=0 || 
			((param_desc *)data)->data==&flyengine->curveerr)
			init();
	return 0;
}
