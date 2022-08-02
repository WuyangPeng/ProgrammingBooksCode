#include "..\..\lib\Fly3D.h"
#include "gamelib.h"

void fao_mesh::init()
{
	if (o)
		pos=o->pivotpos;
}

void fao_mesh::draw()
{
	if (o)
	{
	if (node)
		{
		o->color=node->color+dynlight;
		dynlight.null();
		}
	glPushMatrix();
	glTranslatef(pos.x,pos.y,pos.z);
	glMultMatrixf((float *)&mat);
	o->draw();
	glPopMatrix();
	}
}

mesh *fao_mesh::ray_intersect(vector& ro,vector& rd,vector& ip,float& dist,int &facenum,float rad)
{
	if (o)
	{
	facenum=o->ray_intersect((ro-pos)*mat_t,rd*mat_t,ip,dist);
	if (facenum!=-1)
		{
		if (flyengine->moving && timeactivate==0)
			timeactivate=flyengine->cur_time;
		ip=ip*mat+pos;
		return o;
		}
	}
	return 0;
}

int fao_mesh::step(int dt)    
{
	if (o==0) 
		return 0;
	if (mode==0)
		if (time)
		{
			rotate(rot*(float)dt);
			o->set_key((float)((flyengine->cur_time-timeactivate)%time)/time);
		}
		else ;
	else
	if (timeactivate)
	{
		int t=flyengine->cur_time-timeactivate;
		if (t>delay+time*2+wait)
			{
			o->set_key(0);
			timeactivate=0;
			}
		else
		if (t>delay+time+wait)
			o->set_key(0.5f+(float)(t-(delay+time+wait))/time*0.5f);
		else
		if (t>delay+time)
			;
		else 
		if (t>delay)
			o->set_key((float)(t-delay)/time*0.5f);
	}
	return 0;
}

int fao_mesh::get_custom_param_desc(int i,param_desc *pd)
{
	if (pd!=0)
	switch(i)
	{
		case 0:
			pd->type='m';
			pd->data=&o;
			strcpy(pd->name,"animobj");
			break;
		case 1:
			pd->type='i';
			pd->data=&mode;
			strcpy(pd->name,"mode");
			break;
		case 2:
			pd->type='i';
			pd->data=&time;
			strcpy(pd->name,"time");
			break;
		case 3:
			pd->type='i';
			pd->data=&delay;
			strcpy(pd->name,"delay");
			break;
		case 4:
			pd->type='i';
			pd->data=&wait;
			strcpy(pd->name,"wait");
			break;
	}
	return 5;
}

int fao_mesh::message(vector& p,float rad,int msg,int param,void *data)
{
	if (msg==FLYOBJM_ILLUM)
	{
		float fac=(p-pos).length()/rad;
		if (fac<1.0f)
			dynlight+=*((vector *)data)*(1.0f-fac);
	}

	return 1;
}
