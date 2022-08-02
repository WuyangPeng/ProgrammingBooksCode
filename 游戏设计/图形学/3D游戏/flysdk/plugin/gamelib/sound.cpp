#include "..\..\lib\Fly3D.h"
#include "gamelib.h"

void dyn_sound::play()
{
	if (instance!=-1)
		snd->buf[instance]->Play(0,0,loop?DSBPLAY_LOOPING:0);
}

dyn_sound::dyn_sound()
{
	type=TYPE_SOUND;
	lockpos=0;
	lockvel=0;
	snd=0;
	mindist=maxdist=0;
	volume=0;
	instance=-1;
}

dyn_sound::~dyn_sound()
{
	if (instance!=-1 && snd)
		snd->free_sound_instance(instance);
}

bsp_object *dyn_sound::clone()
{
	dyn_sound *s=new dyn_sound;

	*s=*this;
	s->source=this;

	if (snd)
		s->instance=snd->get_sound_instace();

	return s;
}

int dyn_sound::step(int dt)
{
	int ret=0;
	life-=dt;
	if (instance!=-1 && snd->buf3d[instance])
	if (lockpos!=0 || dt==0)
	{
		if (lockpos) 
		{
			pos=*lockpos;
			ret=1;
			snd->buf3d[instance]->SetPosition(pos.x,pos.y,pos.z,DS3D_DEFERRED);
		}

		if (lockvel) 
		{
			vel=*lockvel;
			snd->buf3d[instance]->SetVelocity(vel.x,vel.y,vel.z,DS3D_DEFERRED);
		}
		else 
			lockpos=0;

		if (dt==0)
			{
			snd->buf3d[instance]->SetMinDistance(mindist,DS3D_DEFERRED);
			snd->buf3d[instance]->SetMaxDistance(maxdist,DS3D_DEFERRED);
			snd->buf[instance]->SetVolume(volume);
			snd->buf[instance]->Play(0,0,loop?DSBPLAY_LOOPING:0);
			}
	}
	return ret;
}

int dyn_sound::get_custom_param_desc(int i,param_desc *pd)
{
	if (pd!=0)
	switch(i)
	{
		case 0:
			pd->type='f';
			pd->data=&mindist;
			strcpy(pd->name,"mindist");
			break;
		case 1:
			pd->type='f';
			pd->data=&maxdist;
			strcpy(pd->name,"maxdist");
			break;
		case 2:
			pd->type='i';
			pd->data=&volume;
			strcpy(pd->name,"volume");
			break;
		case 3:
			pd->type='i';
			pd->data=&loop;
			strcpy(pd->name,"loop");
			break;
		case 4:
			pd->type='w';
			pd->data=&snd;
			strcpy(pd->name,"file");
			break;
	}
	return 5;
}

void dyn_sound::add_sound_clone(vector *lock_pos,vector *lock_vel)
{
	if (flyengine->mute==0 && directx->mpmode!=FLYMP_SERVER && snd)
	{
		dyn_sound *s=(dyn_sound *)clone();
		s->life=snd->total_time;
		s->lockpos=lock_pos;
		s->lockvel=lock_vel;
		s->step(0);
		flyengine->activate(s);
	}
}
