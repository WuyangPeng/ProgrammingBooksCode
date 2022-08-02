#include "..\..\lib\Fly3D.h"
#include "weapon.h"

bsp_object *gun::clone()
{
	gun *tmp=new gun;
	*tmp=*this;
	tmp->source=this;
	return tmp;
}

int gun::get_custom_param_desc(int i,param_desc *pd)
{
	if (pd!=0)
	switch(i)
	{
		case 0:
			pd->type=TYPE_GUN_PROJECTILE;
			pd->data=&p;
			strcpy(pd->name,"projectile");
			break;
		case 1:
			pd->type='i';
			pd->data=&firecount;
			strcpy(pd->name,"firecount");
			break;
		case 2:
			pd->type=TYPE_SOUND;
			pd->data=&sndfire;
			strcpy(pd->name,"firesound");
			break;
		case 3:
			pd->type='f';
			pd->data=&firevel;
			strcpy(pd->name,"firevel");
			break;
		case 4:
			pd->type='i';
			pd->data=&delay;
			strcpy(pd->name,"delay");
			break;
		case 5:
			pd->type='i';
			pd->data=&firedelay;
			strcpy(pd->name,"firedelay");
			break;
		case 6:
			pd->type='i';
			pd->data=&nfire;
			strcpy(pd->name,"nfire");
			break;
		case 7:
			pd->type='f';
			pd->data=&randomangle;
			strcpy(pd->name,"randomangle");
			break;
		case 8:
			pd->type='i';
			pd->data=&nfirepos;
			strcpy(pd->name,"nfirepos");
			break;
		case 9:
			pd->type='v';
			pd->data=&firepos[0];
			strcpy(pd->name,"firepos0");
			break;
		case 10:
			pd->type='v';
			pd->data=&firepos[1];
			strcpy(pd->name,"firepos1");
			break;
		case 11:
			pd->type='v';
			pd->data=&firepos[2];
			strcpy(pd->name,"firepos2");
			break;
		case 12:
			pd->type='v';
			pd->data=&firepos[3];
			strcpy(pd->name,"firepos3");
			break;
	}
	return 13;
}

void gun::fire(bsp_object *obj,int player)
{
	vector v;
	for( int i=0;i<nfirepos;i++ )
		{
		if (randomangle)
			{
			v=obj->Z+obj->X*randomangle*FRAND+obj->Y*randomangle*FRAND;
			v.normalize();
			}
		else v=obj->Z;
		v.negate();
		if (p)
			p->fire(obj->pos+firepos[i]*obj->mat,v,firevel,player);
		if (sndfire)
			sndfire->add_sound_clone(&obj->pos,0);
		}
}

int gun::fire_status()
{
	int ret=0;
	if (firecount)
		{
		if (curfire==0)
			firetime=flyengine->cur_time;
		if (curfire<nfire &&
			(flyengine->cur_time-firetime)/firedelay>=curfire)
			{
			curfire++;
			firecount--;
			ret=1;
			}
		if (flyengine->cur_time-firetime>delay)
			curfire=0;
		}
	return ret;
}
