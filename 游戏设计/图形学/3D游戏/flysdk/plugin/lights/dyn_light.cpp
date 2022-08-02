#include "../../lib/Fly3D.h"
#include "lights.h"

int light::step(int dt)
{
	if (node) 
		life-=dt;

	if (directx->mpmode!=FLYMP_SERVER)
		{
		illum_radius+=dt*grow;
		
		flyengine->shadow_obj=shadow_obj;
		flyengine->send_bsp_message(flyengine->bsp,pos,illum_radius,FLYOBJM_ILLUM,shadowmode,&color);
		flyengine->shadow_obj=0;

		if (s)
			s->step(dt);
		}
	return 0;
}

void light::draw()
{
	if (s) 
	{
		s->pos=pos;
		s->draw();
	}
}

int light::get_custom_param_desc(int i,param_desc *pd)
{
	if (pd!=0)
	switch(i)
	{
		case 0:
			pd->type='c';
			pd->data=&color;
			strcpy(pd->name,"color");
			break;
		case 1:
			pd->type='f';
			pd->data=&illum_radius;
			strcpy(pd->name,"illumradius");
			break;
		case 2:
			pd->type='i';
			pd->data=&shadowmode;
			strcpy(pd->name,"shadowmode");
			break;
		case 3:
			pd->type='d';
			pd->data=&shadow_obj;
			strcpy(pd->name,"shadow_obj");
			break;
		case 4:
			pd->type=TYPE_SPRITE_LIGHT;
			pd->data=&s;
			strcpy(pd->name,"sprite");
			break;
		case 5:
			pd->type='f';
			pd->data=&grow;
			strcpy(pd->name,"grow");
			break;
	}
	return 6;
}
