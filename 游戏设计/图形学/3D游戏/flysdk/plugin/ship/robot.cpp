#include "game.h"

void robot::init()
{
	if (objmesh)
		pos=objmesh->pivotpos;
}

void robot::draw()
{
	active=2;
	if (objmesh==0 || shieldmesh==0) 
		return;
	if (node)
		{
		objmesh->color=node->color+dynlight;
		dynlight.null();
		}
	shieldmesh->scrollu=shieldmesh->scrollv=(flyengine->cur_time%750)/750.0f;
	glPushMatrix();
	glTranslatef(pos.x,pos.y,pos.z);
	glMultMatrixf((float *)&mat);
	objmesh->draw();
	if (flyengine->cur_time-lasthittime<500)
		{
		shieldmesh->color=shieldcolor*shieldmesh->color.w;
		shieldmesh->color.w=1.0f-(flyengine->cur_time-lasthittime)/500.0f;
		glDepthMask(GL_FALSE);
		glBlendFunc(GL_ONE, GL_ONE);
		shieldmesh->draw();
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDepthMask(GL_TRUE);
		}
	glPopMatrix();
}

void robot_find(void *data,bsp_object *e)
{
	robot *r=(robot *)data;
	if (e->type==TYPE_SHIP)
		{
		if (((ship *)e)->flag2 ||
			(((ship *)e)->flag3&SHIP_FLAG3_INVISIBLE))
			return;

		vector dir=r->pos-e->pos;
		float dist=dir.length();
		if (dist<r->enemydist)
			{
			dir/=dist;
			if (vec_dot(dir,r->Z)<r->lookangle)
				return;
			flyengine->excludecollision=e;
			if (flyengine->collision_test(flyengine->bsp,r->pos,e->pos,TYPE_STATIC_MESH,r->radius))
				{
				flyengine->excludecollision=0;
				return;
				}
			flyengine->excludecollision=0;
			r->enemy=e;
			r->enemydist=dist;
			}
		}
}

int robot::step(int dt)
{
	if (active!=2) 
		return 0;
	
	flyengine->stepobj=0;
	
	if (shield<0)
	{
		life=-1;
		if (exp)
			exp->do_explode(pos,Z,-1);
		return 0;
	}

	vector dir;
	float dist;

	// if enemy, test if enemy is still visible or is dead
	if (enemy)
	{
		flyengine->excludecollision=enemy;
		if (((ship *)enemy)->flag2 ||
			(((ship *)enemy)->flag3&SHIP_FLAG3_INVISIBLE) ||
			flyengine->collision_test(flyengine->bsp,pos,enemy->pos,TYPE_STATIC_MESH,radius))
			{
			flag=((ship *)enemy)->flag2?0:2; 
			enemy=0;
			}
		flyengine->excludecollision=0;
	}
	
	// if no enemy, look around for a possible enemys
	if (enemy==0) 
		{
		enemydist=lookrange;
		flyengine->apply_bsp(flyengine->bsp,pos,lookrange,this,robot_find);
		}

	if (enemy)
	{
		enemylastpos=enemy->pos;
		dir=pos-enemylastpos;
		dist=dir.length();
		dir/=dist;
		
		rotate(Z,dir,rotvel*dt); // try to face enemy
		rotate(Y,vector(0,0,1),rotvel*(dt>>2)); // try to align with floor

		// if in gun range, fire
		if (g && vec_dot(dir,Z)>fireang)
			if (g->fire_status())
				g->fire(this,-1);

		// if not too close, move behind the enemy
		if (dist>mindist)
			{
			flag=1; // moving
			enemylastpos+=enemy->Z*mindist;
			}
		else flag=0; // stay still
	}

	if (flag) // if moving, move in direction of enemylastpos
		{
		dir=enemylastpos-pos;
		dist=dir.length();
		if (dist<0.1f)
			flag=0;
		else 
			{
			vel=dir*(maxvel/dist);
			flyengine->stepobj=this;
			particle::step(dt);
			force.null();
			life=1;
			}
		}

	return 1;
}

int robot::get_custom_param_desc(int i,param_desc *pd)
{
	if (pd==0)
		return 12;
	else 
	switch(i)
	{
		case 0:
			pd->type='3';
			pd->data=&objmesh;
			strcpy(pd->name,"objmesh");
			break;
		case 1:
			pd->type='3';
			pd->data=&shieldmesh;
			strcpy(pd->name,"shieldmesh");
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
			pd->data=&lookangle;
			strcpy(pd->name,"lookangle");
			break;
		case 5:
			pd->type='a';
			pd->data=&fireang;
			strcpy(pd->name,"fireang");
			break;
		case 6:
			pd->type='f';
			pd->data=&maxvel;
			strcpy(pd->name,"maxvel");
			break;
		case 7:
			pd->type='f';
			pd->data=&rotvel;
			strcpy(pd->name,"rotvel");
			break;
		case 8:
			pd->type='f';
			pd->data=&mindist;
			strcpy(pd->name,"mindist");
			break;
		case 9:
			pd->type='f';
			pd->data=&shield;
			strcpy(pd->name,"shield");
			break;
		case 10:
			pd->type='c';
			pd->data=&shieldcolor;
			strcpy(pd->name,"shieldcolor");
			break;
		case 11:
			pd->type=TYPE_EXPLODE;
			pd->data=&exp;
			strcpy(pd->name,"explode");
			break;
	}
	return 0;
}

int robot::message(vector& p,float rad,int msg,int param,void *data)
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
		lasthittime=flyengine->cur_time;
		if (param>=0) 
			enemy=(bsp_object *)directx->players[param].data;
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

mesh *robot::ray_intersect(vector& ro,vector& rd,vector& ip,float& dist,int &facenum,float rad)
{
	if (shieldmesh)
	{
		static float d1,d2;
		vector 
			ro_local=(ro-pos)*mat_t,
			rd_local=rd*mat_t;
		if (shieldmesh->bbox.ray_intersect(ro_local,rd_local,d1,d2))
		{
		facenum=shieldmesh->ray_intersect(ro_local,rd_local,ip,dist,rad);
		if (facenum>-1)
			{
			if (flyengine->stepobj && 
				(flyengine->stepobj->type==TYPE_LASER || flyengine->stepobj->type==TYPE_MISSILE) 
				&& dist<1.0f && ((gun_projectile *)flyengine->stepobj)->damage>0.0f)
				{
				shield-=((gun_projectile *)flyengine->stepobj)->damage;
				lasthittime=flyengine->cur_time;
				if (((gun_projectile *)flyengine->stepobj)->player>=0) 
					enemy=(bsp_object *)directx->players[((gun_projectile *)flyengine->stepobj)->player].data;
				}
			ip=ip*mat+pos;
			return shieldmesh;
			}
		}
	}
	return 0;
}
