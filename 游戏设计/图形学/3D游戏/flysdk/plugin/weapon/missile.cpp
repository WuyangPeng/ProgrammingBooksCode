#include "..\..\lib\Fly3D.h"
#include "weapon.h"

int missile::step(int dt)
{
	if (node==0)
	{
		life=-1;
		if (snd)
			delete snd;
		return 0;
	}

	if(lookrange&&missile_find)
	{
		enemy=0;
		enemydist=lookrange;
		flyengine->apply_bsp(flyengine->bsp,pos,lookrange,this,missile_find);
		if (enemy)
			{
			vector v=(enemy)->pos-pos;
			v.normalize();
			rotate(Z,v,rotvel*dt);
			vel=Z*vel.length();
			}
	}

	flyengine->hitobj=0;
	if (player>=0)
		flyengine->excludecollision=(bsp_object *)directx->players[player].data;
	particle::step(dt);
	flyengine->excludecollision=0;

	if (flyengine->hitobj || life<=0)
		{
		life=-1;
		if (flyengine->hitobj==0)
			if (exp)
				exp->do_explode(pos,Z,player);
			else ;
		else
			{
			pos=flyengine->hitip+flyengine->hitmesh->faces[flyengine->hitface]->normal;
			if (hm && flyengine->hitmesh->localfaces==0)
				{
				hitmark *tmp=(hitmark *)hm->clone();
				tmp->pos=pos;
				tmp->mode=0;
				tmp->align_z(flyengine->hitmesh->faces[flyengine->hitface]->normal);
				flyengine->activate(tmp);
				}
			if (exp)
				exp->do_explode(pos,flyengine->hitmesh->faces[flyengine->hitface]->normal,player);
			}
		if (player==0 && viewport && viewport->target==this)
			{
			viewport->target=0;
			viewport->on=0;
			}
		}
	
	if (l)
		{
		l->pos=pos-Z*lightzpos;
		l->step(dt);
		}
	
	if (snd)
	{
		if (life==-1)
			delete snd;
		else
			snd->step(dt);
	}

	force.x=force.y=force.z=0;

	return 1;
}

void missile::draw()
{
	if (node==0 || flyengine->cam==this) return;
	
	if (objmesh)
	{
		if (node)
			{
			objmesh->color=node->color+dynlight;
			dynlight.null();
			}
		glPushMatrix();
		glTranslatef(pos.x,pos.y,pos.z);
		glMultMatrixf((float *)&mat);
		objmesh->draw();
		glPopMatrix();
	}

	if (l)
		{
		l->pos=pos-Z*lightzpos;
		l->draw();
		}	
}

bsp_object *missile::clone()
{
	missile *tmp=new missile;
	*tmp=*this;
	tmp->source=this;
	return tmp;
}

int missile::get_custom_param_desc(int i,param_desc *pd)
{
	if (pd!=0)
	switch(i)
	{
		case 0:
			pd->type='f';
			pd->data=&rotvel;
			strcpy(pd->name,"rotvel");
			break;
		case 1:
			pd->type='f';
			pd->data=&lookrange;
			strcpy(pd->name,"lookrange");
			break;
		case 2:
			pd->type='a';
			pd->data=&lookangle;
			strcpy(pd->name,"lookangle");
			break;
		case 3:
			pd->type=TYPE_EXPLODE;
			pd->data=&exp;
			strcpy(pd->name,"explode");
			break;
		case 4:
			pd->type=TYPE_LIGHT;
			pd->data=&l;
			strcpy(pd->name,"light");
			break;
		case 5:
			pd->type='f';
			pd->data=&lightzpos;
			strcpy(pd->name,"lightzpos");
			break;
		case 6:
			pd->type=TYPE_SOUND;
			pd->data=&snd;
			strcpy(pd->name,"sound");
			break;
		case 7:
			pd->type=TYPE_VIEWPORT;
			pd->data=&viewport;
			strcpy(pd->name,"viewport");
			break;
		case 8:
			pd->type='3';
			pd->data=&objmesh;
			strcpy(pd->name,"mesh");
			break;
		case 9:
			pd->type=TYPE_HITMARK;
			pd->data=&hm;
			strcpy(pd->name,"hitmark");
			break;
		case 10:
			pd->type='f';
			pd->data=&damage;
			strcpy(pd->name,"damage");
			break;
	}
	return 11;
}

void missile::fire(vector& p,vector& dir,float v,int playerid)
{
	missile *m=(missile *)clone();
	m->pos=p;
	m->vel=dir*v;
	m->align_z(dir);
	m->player=playerid;
	if (m->snd && flyengine->mute==0)
		{
		m->snd=(dyn_sound *)m->snd->clone();
		m->snd->life=life;
		m->snd->lockpos=&m->pos;
		m->snd->lockvel=&m->vel;
		m->snd->step(0);
		}
	else m->snd=0;
	if (viewport && playerid==0)
	{
		viewport->target=m;
		viewport->on=1;
	}
	flyengine->activate(m);
}

int missile::message(vector& p,float rad,int msg,int param,void *data)
{
	if (msg==FLYOBJM_ILLUM)
	{
		float fac=(p-pos).length()/rad;
		if (fac<1.0f)
			dynlight+=*((vector *)data)*(1.0f-fac);
	}

	return 0;
}
