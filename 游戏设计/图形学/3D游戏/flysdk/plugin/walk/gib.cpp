#include "walk.h"

int gib::step(int dt)
{
	if (numbounces==0)
	{
		life-=dt;
		return 0;
	}
	else
	{
		force.z-=gravity*dt;
		particle::step(dt);
		force.null();
		if (hm)
		{
			if (flyengine->hitobj && flyengine->hitmesh->localfaces==0)
			{
				hitmark *tmp=(hitmark *)hm->clone();
				tmp->mode=0;
				tmp->pos=flyengine->hitip+flyengine->hitmesh->faces[flyengine->hitface]->normal;
				tmp->align_z(flyengine->hitmesh->faces[flyengine->hitface]->normal);
				if (flyengine->hitmesh->faces[flyengine->hitface]->normal.z>0.7)
					if (--numbounces==0)
					{
					pos=tmp->pos;
					vel.null();
					gravity=0.0f;
					}
				flyengine->activate(tmp);
			}
			
			if (flyengine->cur_time-lasttrail>traildelay)
			{
				lasttrail=flyengine->cur_time;
				hitmark *tmp=(hitmark *)hm->clone();
				tmp->mode=1;
				tmp->pos=pos;
				tmp->life>>=2;
				tmp->size*=0.5f;
				flyengine->activate(tmp);
			}
			
		}
		return 1;
	}
}

int gib::get_custom_param_desc(int i,param_desc *pd)
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
			pd->type=TYPE_HITMARK;
			pd->data=&hm;
			strcpy(pd->name,"hitmark");
			break;
		case 2:
			pd->type='f';
			pd->data=&gravity;
			strcpy(pd->name,"gravity");
			break;
		case 3:
			pd->type='i';
			pd->data=&fadetime;
			strcpy(pd->name,"fadetime");
			break;
		case 4:
			pd->type='i';
			pd->data=&numbounces;
			strcpy(pd->name,"numbounces");
			break;
		case 5:
			pd->type='i';
			pd->data=&traildelay;
			strcpy(pd->name,"traildelay");
			break;
	}
	return 6;
}

void gib::draw()
{
	if (life<0 || objmesh==0) return;
	
	if (node)
		{
		objmesh->color=node->color+dynlight;
		dynlight.null();
		}
	if (life<fadetime)
		objmesh->color.w=(float)life/fadetime;
	else objmesh->color.w=1.0f;

	glPushMatrix();
	glTranslatef(pos.x,pos.y,pos.z);
	glMultMatrixf((float *)&mat);
	objmesh->draw();
	glPopMatrix();
}

int gib::message(vector& p,float rad,int msg,int param,void *data)
{
	if (msg==FLYOBJM_ILLUM)
	{
		float fac=(p-pos).length()/rad;
		if (fac<1.0f)
			dynlight+=*((vector *)data)*(1.0f-fac);
	}

	return 1;
}
