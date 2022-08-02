#include "game.h"

void container::init()
{
	if (objmesh)
		pos=objmesh->pivotpos;
}

void container::draw()
{
	if (objmesh)
	{
	if (node)
		{
		objmesh->color=node->color+dynlight;
		if (objmesh->color.x>1.0f) objmesh->color.x=1.0f;
		if (objmesh->color.y>1.0f) objmesh->color.y=1.0f;
		if (objmesh->color.z>1.0f) objmesh->color.z=1.0f;
		objmesh->color.w=1;
		dynlight.null();
		}
	glPushMatrix();
	glTranslatef(pos.x,pos.y,pos.z);
	glMultMatrixf((float *)&mat);
	objmesh->draw();
	glPopMatrix();
	}
}

int container::step(int dt)
{
	if (shield<0)
	{
		life=-1;
		if (exp)
			exp->do_explode(pos,Z,-1);
		if (p)
		{
			powerup *tmp=(powerup *)p->clone();
			tmp->pos=pos;
			flyengine->activate(tmp);
		}
	}
	return 0;
}

int container::get_custom_param_desc(int i,param_desc *pd)
{
	if (pd==0)
		return 4;
	else 
	switch(i)
	{
		case 0:
			pd->type='3';
			pd->data=&objmesh;
			strcpy(pd->name,"objmesh");
			break;
		case 1:
			pd->type=TYPE_EXPLODE;
			pd->data=&exp;
			strcpy(pd->name,"explode");
			break;
		case 2:
			pd->type=TYPE_POWERUP;
			pd->data=&p;
			strcpy(pd->name,"powerup");
			break;
		case 3:
			pd->type='f';
			pd->data=&shield;
			strcpy(pd->name,"shield");
			break;
	}
	return 0;
}

int container::message(vector& p,float rad,int msg,int param,void *data)
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

mesh *container::ray_intersect(vector& ro,vector& rd,vector& ip,float& dist,int &facenum,float rad)
{
	if (objmesh)
	{
		static float d1,d2;
		vector 
			ro_local=(ro-pos)*mat_t,
			rd_local=rd*mat_t;
		if (objmesh->bbox.ray_intersect(ro_local,rd_local,d1,d2))
		{
		facenum=objmesh->ray_intersect(ro_local,rd_local,ip,dist,rad);
		if (facenum>-1)
			{
			if (flyengine->stepobj && 
				(flyengine->stepobj->type==TYPE_LASER || flyengine->stepobj->type==TYPE_MISSILE) 
				&& dist<1.0f && ((gun_projectile *)flyengine->stepobj)->damage>0.0f)
				shield-=((gun_projectile *)flyengine->stepobj)->damage;
			ip=ip*mat+pos;
			return objmesh;
			}
		}
	}
	return 0;
}
