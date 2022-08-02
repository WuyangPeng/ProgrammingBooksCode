#include "game.h"

void powerup::draw()
{
	if (objmesh==0)
		return;

	objmesh->color.vec(1,1,1);
	if (life>500)
		objmesh->color.w=1;
	else
	if (life<500)
		objmesh->color.w=life/500.0f;
	else if (life>source->life-500)
			objmesh->color.w=(source->life-life)/500.0f;
		else objmesh->color.w=0;

	if (l)
		{
		l->pos=pos;
		if(l->s)
			l->s->color.w=objmesh->color.w;
		l->draw();
		}	
	glPushMatrix();
	glTranslatef(pos.x,pos.y,pos.z);
	glMultMatrixf((float *)&mat);
	if (mode&1)
		{
		glDisable(GL_CULL_FACE);
		glDepthMask(GL_FALSE);
		glBlendFunc(GL_ONE, GL_ONE);
		objmesh->draw();
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDepthMask(GL_TRUE);
		glEnable(GL_CULL_FACE);
		}
	else 
		objmesh->draw();
	glPopMatrix();
}

int powerup::step(int dt)
{
	life-=dt;
	switch(directx->mpmode)
	{
	case FLYMP_SERVER:
		{
			static struct mp_data data;
			data.flag=valuetype;
			for( int i=1;i<directx->nplayers;i++ )
			{
				if ((((bsp_object *)(directx->players[i].data))->pos-pos).length()<radius)
				{
					data.type=FLYMP_MSG_POWERUPGET;
					data.dpid=directx->players[i].dpid;
					directx->send_message((mp_msg *)&data,sizeof(mp_data));
					powerup_get((ship *)directx->players[i].data);
					life=-1;
					break;
				}
			}
			if (life<0)
				{
				flyengine->get_random_point(pos,radius);
				life=source->life;
				data.type=FLYMP_MSG_POWERUPMOVE;
				data.pos=pos;
				directx->send_message((mp_msg *)&data,sizeof(mp_data));
				}
		}
		break;
	case FLYMP_CLIENT:
		{
			if (life<0) 
				life=0;
			else
				{
				if (l && objmesh)
					{
					vector temp=l->color;
					l->color*=objmesh->color.w;
					l->pos=pos;
					l->step(dt);
					l->color=temp;
					}
				rotate(rot*(float)dt);
				}
		}
		break;
	case FLYMP_NOMP:
		{
			vector v=flyengine->cam->pos-pos;
			if ((v.x*v.x+v.y*v.y+v.z*v.z)<radius*radius)
				powerup_get((ship *)flyengine->cam);
			if (life<0 && ((mode&2)==0))
				{
				flyengine->get_random_point(pos,radius);
				life=source->life;
				}
			if (l && objmesh)
				{
				vector temp=l->color;
				l->color*=objmesh->color.w;
				l->pos=pos;
				l->step(dt);
				l->color=temp;
				}
			rotate(rot*(float)dt);
		}
		break;
	}
	return 1;
}

void powerup::powerup_get(ship *s)
{
	life=-1;

	if (valuetype>=0)
		{
		if (s!=flyengine->cam)
			return;
		if (valuetype<10 && s->g[valuetype])
			s->g[valuetype]->firecount+=value;
		}
	else 
		if (valuetype==-1)
			{
			s->shield+=(float)value;
			if (s->shield>s->shield) 
				s->shield=s->shield;
			}
		else 
		if (valuetype==-2 && s->flag3==0)
			s->flag3=value|SHIP_FLAG3_INVISIBLE;
		else 
		if (valuetype==-3 && s->flag3==0)
			s->flag3=value|SHIP_FLAG3_INVENSIBLE;
	
	if (l && s==flyengine->cam)
		flyengine->filter+=l->color;
	
	if (sndget)
		sndget->add_sound_clone(&pos,0);
}

int powerup::get_custom_param_desc(int i,param_desc *pd)
{
	if (pd==0)
		return 6;
	else 
	switch(i)
	{
		case 0:
			pd->type='i';
			pd->data=&valuetype;
			strcpy(pd->name,"type");
			break;
		case 1:
			pd->type='i';
			pd->data=&value;
			strcpy(pd->name,"value");
			break;
		case 2:
			pd->type=TYPE_LIGHT;
			pd->data=&l;
			strcpy(pd->name,"light");
			break;
		case 3:
			pd->type=TYPE_SOUND;
			pd->data=&sndget;
			strcpy(pd->name,"soundget");
			break;
		case 4:
			pd->type='3';
			pd->data=&objmesh;
			strcpy(pd->name,"mesh");
			break;
		case 5:
			pd->type='i';
			pd->data=&mode;
			strcpy(pd->name,"mode");
			break;
	}
	return 0;
}

