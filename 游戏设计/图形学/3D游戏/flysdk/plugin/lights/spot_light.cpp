#include "../../lib/Fly3D.h"
#include "lights.h"

void spot_light::reposition(bsp_object *obj)
{
	if (directx->mpmode!=FLYMP_SERVER && l)
	{
		vector p1,p2;
		p1 = obj->pos;
		p2 = p1 - obj->Z*maxdist;
		flyengine->excludecollision=obj;
		if (flyengine->collision_bsp(flyengine->bsp,p1,p2))
		{
			flyengine->excludecollision=0;
			if (flyengine->hitobj)
			{
			l->color=color*(1.0f - (flyengine->hitip-p1).length()/maxdist);
			l->pos=flyengine->hitip;
			l->step(0);
			}
		}
		else flyengine->excludecollision=0;
	}
}

int spot_light::get_custom_param_desc(int i,param_desc *pd)
{
	if (pd!=0)
	switch(i)
	{
		case 0:
			pd->type='f';
			pd->data=&maxdist;
			strcpy(pd->name,"maxdist");
			break;
		case 1:
			pd->type='c';
			pd->data=&color;
			strcpy(pd->name,"color");
			break;
		case 2:
			pd->type=TYPE_LIGHT;
			pd->data=&l;
			strcpy(pd->name,"light");
			break;
	}
	return 3;
}
