#include "../Fly3D.h"

int particle::compute_collision(vector& p,vector& v)
{
	static vector p0,dir,d,v1,v2,reflectdir,*n;

	float f1,f2,len;
	int ncol=-1;
	bsp_object *last_hit_obj=0;
	p0=pos;
	flyengine->moving=1;
	while(ncol<2)
	{
		dir=p-p0;
		len=dir.length();
		if (len<0.1f)
			break;
		if (ncol==-1)
			ncol++;
		dir/=len;

		if (0==flyengine->collision_bsp(flyengine->bsp,p0,p,0,radius))
		{
			p0=p - dir*0.1f;
			break;
		}
		
		ncol++;

		last_hit_obj=flyengine->hitobj;
		n=&flyengine->hitmesh->faces[flyengine->hitface]->normal;
		p0=flyengine->hitip - dir*0.1f;

		reflectdir=dir + (*n)*(-2.0f*vec_dot(*n,dir));
		reflectdir.normalize();
		f1=vec_dot(*n,reflectdir);

		f2=(p-p0).length();
		d=reflectdir*f2;
		v1=(*n)*(f1*f2);
		v2=d-v1;
		p=p0+v1*bump+v2*friction;

		f2=v.length();
		d=reflectdir*f2;
		v1=(*n)*(f1*f2);
		v2=d-v1;
		v=v1*bump+v2*friction;
	}
	p=p0;
	flyengine->moving=0;
	flyengine->hitobj=last_hit_obj;
	return ncol;
}

int particle::step(int dt)
{
	static vector p,v;
	float dtf=(float)dt;
	int move=1;
	
	p.x=pos.x+dtf*vel.x;
	p.y=pos.y+dtf*vel.y;
	p.z=pos.z+dtf*vel.z;
	v.x=vel.x+dtf*(force.x/mass);
	v.y=vel.y+dtf*(force.y/mass);
	v.z=vel.z+dtf*(force.z/mass);
	life-=dt;

	if (col_flag&1)
	{
		move=compute_collision(p,v);
		if (move==-1)
			move=0;
		else
		{
			if (move&&(col_flag&2))
				life=-1;
			move=1;
		}
	}

	pos=p;
	vel=v;

	return move;
}

