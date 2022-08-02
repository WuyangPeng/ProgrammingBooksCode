#include "..\..\lib\Fly3D.h"
#include "gamelib.h"

void particle_system::draw()
{
	if (part)
	{
		int i;
		for( i=part0;i<part1;i++ )
			part[i].draw();
	}
}

int particle_system::step(int dt)
{
	if (directx->mpmode!=FLYMP_SERVER)
	{
	if (part==0)
		{
		part=new color_particle[totpart];
		part0=part1=0;
		}
	else
		{
		int i;
		for( i=part0;i<part1;i++ )
			{
			part[i].step(dt);
			if (part[i].life<0)
				part0++;
			else if (part[i].life<fadetime)
					part[i].color.w=(float)part[i].life/fadetime;
			}
		}

	float rnd;
	int i,tot;

	i=source->life-life;
	if (i>emmtime) i=emmtime;
	tot=totpart*i/emmtime-part1;
	for( i=0;i<tot;i++ )
		{
		rnd=FRAND;
		part[part1].life=source->life-emmtime;
		part[part1].col_flag=col_flag_new;
		part[part1].texture=texture_new;
		part[part1].radius=0.0f;
		part[part1].size=radius_new;
		part[part1].color=color_new+colorvar_new*rnd;
		part[part1].pos=pos;
		if (FP_BITS(ax)==0 && FP_BITS(ay)==0) 
			part[part1].vel=X*FRAND+Y*FRAND+Z*FRAND;
		else part[part1].vel=X*(FRAND*ax)+Y*(FRAND*ay)+Z;
		part[part1].vel.normalize();
		part[part1].vel*=speed_new+speed_var*rnd;
		part[part1].bump=bump_new;
		part[part1].friction=friction_new;
		part[part1].force.vec(0.0f,0.0f,-gravity_new);
		part[part1].color.w=1.0f;
		part[part1].mass=1.0f;
		part1++;
		}
	}

	life-=dt;
	return 0;
}

int particle_system::get_custom_param_desc(int i,param_desc *pd)
{
	if (pd!=0)
	switch(i)
	{
		case 0:
			pd->type='c';
			pd->data=&color_new;
			strcpy(pd->name,"partcolor");
			break;
		case 1:
			pd->type='c';
			pd->data=&colorvar_new;
			strcpy(pd->name,"partcolorvar");
			break;
		case 2:
			pd->type='f';
			pd->data=&bump_new;
			strcpy(pd->name,"partbump");
			break;
		case 3:
			pd->type='f';
			pd->data=&friction_new;
			strcpy(pd->name,"partfriction");
			break;
		case 4:
			pd->type='f';
			pd->data=&mass_new;
			strcpy(pd->name,"partmass");
			break;
		case 5:
			pd->type='f';
			pd->data=&radius_new;
			strcpy(pd->name,"partradius");
			break;
		case 6:
			pd->type='f';
			pd->data=&speed_new;
			strcpy(pd->name,"partspeed");
			break;
		case 7:
			pd->type='f';
			pd->data=&speed_var;
			strcpy(pd->name,"partspeedvar");
			break;
		case 8:
			pd->type='f';
			pd->data=&gravity_new;
			strcpy(pd->name,"partgravity");
			break;
		case 9:
			pd->type='i';
			pd->data=&col_flag_new;
			strcpy(pd->name,"partcolflag");
			break;
		case 10:
			pd->type='f';
			pd->data=&ax;
			strcpy(pd->name,"ax");
			break;
		case 11:
			pd->type='f';
			pd->data=&ay;
			strcpy(pd->name,"ay");
			break;
		case 12:
			pd->type='p';
			pd->data=&texture_new;
			strcpy(pd->name,"texture");
			break;
		case 13:
			pd->type='i';
			pd->data=&emmtime;
			strcpy(pd->name,"emmtime");
			break;
		case 14:
			pd->type='i';
			pd->data=&totpart;
			strcpy(pd->name,"totpart");
			break;
		case 15:
			pd->type='i';
			pd->data=&fadetime;
			strcpy(pd->name,"fadetime");
			break;
	}
	return 16;
}
