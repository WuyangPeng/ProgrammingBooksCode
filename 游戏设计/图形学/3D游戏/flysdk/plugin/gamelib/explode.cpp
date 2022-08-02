#include "..\..\lib\Fly3D.h"
#include "gamelib.h"

void explode::do_explode(vector& pos,vector& z,int fromplayer)
{
	if (directx->mpmode!=FLYMP_SERVER)
	{
	if (e)
		{
		exp_sphere *x=(exp_sphere *)e->clone();
		x->pos=pos;
		flyengine->activate(x);
		}
	if (s)
		{
		sprite_light *x=(sprite_light *)s->clone();
		x->pos=pos;
		x->align_z(z);
		flyengine->activate(x);
		}
	if (l)
		{
		light *x=(light *)l->clone();
		x->pos=pos;
		flyengine->activate(x);
		}
	if (ps)
		{
		particle_system *x=(particle_system *)ps->clone();
		x->pos=pos;
		x->align_z(z);
		flyengine->activate(x);
		}

	if (snd) 
		snd->add_sound_clone(&pos,0);
	}
	
	if (damage>0 && damageradius>0)
		flyengine->send_bsp_message(flyengine->bsp,pos,damageradius,FLYOBJM_DAMAGE,fromplayer,&damage);
}

int explode::get_custom_param_desc(int i,param_desc *pd)
{
	if (pd!=0)
	switch(i)
	{
		case 0:
			pd->type='f';
			pd->data=&damage;
			strcpy(pd->name,"damage");
			break;
		case 1:
			pd->type='f';
			pd->data=&damageradius;
			strcpy(pd->name,"damageradius");
			break;
		case 2:
			pd->type=TYPE_SPRITE_LIGHT;
			pd->data=&s;
			strcpy(pd->name,"sprite");
			break;
		case 3:
			pd->type=TYPE_LIGHT;
			pd->data=&l;
			strcpy(pd->name,"light");
			break;
		case 4:
			pd->type=TYPE_SOUND;
			pd->data=&snd;
			strcpy(pd->name,"sound");
			break;
		case 5:
			pd->type=TYPE_PARTICLE_SYSTEM;
			pd->data=&ps;
			strcpy(pd->name,"ps");
			break;
		case 6:
			pd->type=TYPE_EXP_SPHERE;
			pd->data=&e;
			strcpy(pd->name,"expsphere");
			break;
	}
	return 7;
}
