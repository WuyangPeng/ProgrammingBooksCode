#include "..\..\lib\Fly3D.h"
#include "weapon.h"

int mine::step(int dt)
{
	if (delay>0)
		{
		delay-=dt;
		return 0;
		}

	life-=dt;

	if(lookrange&&mine_find)
		{
		enemy=0;
		enemydist=lookrange;
		flyengine->apply_bsp(flyengine->bsp,pos,lookrange,this,mine_find);
		if (enemy)
			life=-1;
		}

	if (life<0 || shield<0)
		{
		life=-1;
		if (exp)
			exp->do_explode(pos,Z,player);
		return 0;
		}

	if ((life%1000)>500)
		factor=(1000-(life%1000))/500.0f;
	else factor=(life%1000)/500.0f;

	if (l)
		{
		l->pos=pos;
		l->illum_radius=lookrange*factor;
		l->step(dt);
		}
	
	if (snd)
		snd->step(dt);
	
	return 0;
}

void mine::draw()
{
	if (flyengine->cam==this) 
		return;

	if (objmesh)
	{
	static float d;
	if ((flyengine->cur_time%1000)>500)
		d=(250-(flyengine->cur_time%500))/500.0f;
	else d=((flyengine->cur_time%500)-250)/500.0f;
	d=(objmesh->bbox.max.z-objmesh->bbox.min.z)*d;
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

	if (s)
		{
		s->curradius=lookrange*factor;
		s->pos=pos;
		s->draw();
		}

	if (l)
		{
		l->pos=pos;
		l->draw();
		}
}

bsp_object *mine::clone()
{
	mine *tmp=new mine;
	*tmp=*this;
	tmp->source=this;
	return tmp;
}

int mine::get_custom_param_desc(int i,param_desc *pd)
{
	if (pd!=0)
	switch(i)
	{
		case 0:
			pd->type='f';
			pd->data=&lookrange;
			strcpy(pd->name,"lookrange");
			break;
		case 1:
			pd->type=TYPE_EXPLODE;
			pd->data=&exp;
			strcpy(pd->name,"explode");
			break;
		case 2:
			pd->type=TYPE_LIGHT;
			pd->data=&l;
			strcpy(pd->name,"light");
			break;
		case 3:
			pd->type=TYPE_SOUND;
			pd->data=&snd;
			strcpy(pd->name,"sound");
			break;
		case 4:
			pd->type='3';
			pd->data=&objmesh;
			strcpy(pd->name,"mesh");
			break;
		case 5:
			pd->type=TYPE_EXP_SPHERE;
			pd->data=&s;
			strcpy(pd->name,"expsphere");
			break;
		case 6:
			pd->type='i';
			pd->data=&delay;
			strcpy(pd->name,"delay");
			break;
		case 7:
			pd->type='f';
			pd->data=&shield;
			strcpy(pd->name,"shield");
			break;
	}
	return 8;
}

void mine::fire(vector& p,vector& dir,float v,int playerid)
{
	mine *m=(mine *)clone();
	m->pos=p;
	m->vel=dir*v;
	m->align_z(dir);
	m->player=playerid;
	if (m->snd)
		{
		m->snd=(dyn_sound *)m->snd->clone();
		m->snd->lockpos=&m->pos;
		m->snd->lockvel=&m->vel;
		m->snd->step(0);
		}
	flyengine->activate(m);
}

mesh *mine::ray_intersect(vector& ro,vector& rd,vector& ip,float& dist,int &facenum,float rad)
{
	if (objmesh==0)
		return 0;
	
	facenum=objmesh->ray_intersect(ro-pos,rd,ip,dist,rad);
	
	if (facenum!=-1)
		{
		if (flyengine->stepobj && 
			(flyengine->stepobj->type==TYPE_LASER || flyengine->stepobj->type==TYPE_MISSILE) 
			&& dist<1.0f && ((gun_projectile *)flyengine->stepobj)->damage>0.0f)
			shield-=((gun_projectile *)flyengine->stepobj)->damage;
		ip=ip+pos;
		return objmesh;
		}
	else 
		return 0;
}

int mine::message(vector& p,float rad,int msg,int param,void *data)
{
	if (msg==FLYOBJM_DAMAGE)
	{
		vector v=pos-p;
		float len=v.length();
		if (len>rad)
			return 0;

		flyengine->excludecollision=this;
		if(flyengine->collision_test(flyengine->bsp, p, pos))
			return 0;
		flyengine->excludecollision=0;
		
		shield-=*((float *)data)*(1-len/rad);
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
