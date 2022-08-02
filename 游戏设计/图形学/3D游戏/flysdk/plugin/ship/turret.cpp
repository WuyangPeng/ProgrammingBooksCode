#include "game.h"

void turret::init()
{
	if (base)
		pos=base->pivotpos;
	tubels=*((local_system *)this);
	tubels.rotate(vector(180,0,0));
}

void turret::draw()
{
	active=2;
	if (base==0 || tube==0)
		return;
	if (node)
		{
		base->color=node->color+dynlight;
		tube->color=base->color;
		dynlight.null();
		}
	glPushMatrix();
	glTranslatef(pos.x,pos.y,pos.z);
	glPushMatrix();
	glMultMatrixf((float *)&mat);
	base->draw();
	glPopMatrix();
	glMultMatrixf((float *)&tubels.mat);
	tube->draw();
	glPopMatrix();
}

void turret_find(void *data,bsp_object *e)
{
	turret *t=(turret *)data;
	if (e->type==TYPE_SHIP)
		{
		float dist=(e->pos-t->pos).length();
		if (dist<t->enemydist)
			{
			flyengine->excludecollision=e;
			if (flyengine->collision_test(flyengine->bsp,t->pos,e->pos))
				{
				flyengine->excludecollision=0;
				return;
				}
			flyengine->excludecollision=0;
			t->enemy=e;
			t->enemydist=dist;
			}
		}
}

int turret::step(int dt)
{
	// not activated yet by a render
	if (active!=2) return 0;

	// if no shield, exlode and die
	if (shield<0.0f)
		{
		life=-1; // die
		if (exp)
			exp->do_explode(pos,Z,-1); // explode
		return 0;
		}

	// look around for enemy
	enemy=0;
	enemydist=lookrange;
	flyengine->apply_bsp(flyengine->bsp,pos,lookrange,this,turret_find);

	// if enemy found
	if (enemy)
	{
		// get enemy direction and try to align cannon
		vector dir=pos-enemy->pos;
		dir.normalize();
		tubels.rotate(tubels.Z,dir,rotvel*dt);

		// if cannon is inside fire angle threshold
		if (g && vec_dot(dir,tubels.Z)>fireang)
			if (g->fire_status())
			{
			local_system ls=*((local_system *)this);
			*((local_system *)this)=tubels;
			g->fire(this,-1);
			*((local_system *)this)=ls;
			}
	}

	return 0;
}

int turret::get_custom_param_desc(int i,param_desc *pd)
{
	if (pd==0)
		return 8;
	else 
	switch(i)
	{
		case 0:
			pd->type='3';
			pd->data=&base;
			strcpy(pd->name,"base");
			break;
		case 1:
			pd->type='3';
			pd->data=&tube;
			strcpy(pd->name,"tube");
			break;
		case 2:
			pd->type=TYPE_GUN;
			pd->data=&g;
			strcpy(pd->name,"gun");
			break;
		case 3:
			pd->type='f';
			pd->data=&lookrange;
			strcpy(pd->name,"lookrange");
			break;
		case 4:
			pd->type='a';
			pd->data=&fireang;
			strcpy(pd->name,"fireang");
			break;
		case 5:
			pd->type='f';
			pd->data=&shield;
			strcpy(pd->name,"shield");
			break;
		case 6:
			pd->type=TYPE_EXPLODE;
			pd->data=&exp;
			strcpy(pd->name,"explode");
			break;
		case 7:
			pd->type='f';
			pd->data=&rotvel;
			strcpy(pd->name,"rotvel");
			break;
	}
	return 0;
}

int turret::message(vector& p,float rad,int msg,int param,void *data)
{
	if (msg==FLYOBJM_DAMAGE)
	{
		vector v=pos-p;
		float len=v.length();
		if (len>rad || len<SMALL)
			return 0;

		flyengine->excludecollision=this;
		if(flyengine->collision_test(flyengine->bsp, p, pos))
		{
			flyengine->excludecollision=0;
			return 0;
		}
		flyengine->excludecollision=0;

		shield-=*((float *)data)*(1.0f-len/rad);
	}
	else
	if (msg==FLYOBJM_ILLUM)
	{
		float fac=(p-pos).length()/rad;
		if (fac<1.0f)
			dynlight+=*((vector *)data)*(1.0f-fac);
	}

	return 0;
}

mesh *turret::ray_intersect(vector& ro,vector& rd,vector& ip,float& dist,int &facenum,float rad)
{
	if (base)
	{
		static float d1,d2;
		vector 
			ro_local=(ro-pos)*mat_t,
			rd_local=rd*mat_t;
		if (base->bbox.ray_intersect(ro_local,rd_local,d1,d2))
		{
		facenum=base->ray_intersect(ro_local,rd_local,ip,dist,rad);
		if (facenum>-1)
			{
			if (flyengine->stepobj && 
				(flyengine->stepobj->type==TYPE_LASER || flyengine->stepobj->type==TYPE_MISSILE) 
				&& dist<1.0f && ((gun_projectile *)flyengine->stepobj)->damage>0.0f)
				shield-=((gun_projectile *)flyengine->stepobj)->damage;
			ip=ip*mat+pos;
			return base;
			}
		}
	}
	return 0;
}
