#include "game.h"

ship_desc cd_ship;
turret_desc cd_turret;
robot_desc cd_robot;
powerup_desc cd_powerup;
container_desc cd_container;

void init_scene();
void mp_message(int from,mp_msg *msg);

BOOL APIENTRY DllMain(HINSTANCE hModule, 
                      DWORD  ul_reason_for_call, 
                      LPVOID lpReserved)
{    
	switch( ul_reason_for_call ) 
	{
    case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

__declspec( dllexport ) 
int num_classes() 
{
	return 5;
}

__declspec( dllexport ) 
class_desc *get_class_desc(int i) 
{
	switch(i) 
	{
	case 0: return &cd_powerup;
	case 1: return &cd_ship;
	case 2: return &cd_turret;
	case 3: return &cd_robot;
	case 4: return &cd_container;
	default: return 0;
	}
}

__declspec( dllexport )
int fly_message(int msg,int param,void *data)
{
	switch(msg)
	{
	case FLYM_DRAWSCENE:
	if (directx->mpmode!=FLYMP_SERVER)
		{
		ship *s=(ship *)(flyengine->cam);
		if (s->flag2)
			{
			vector dir=s->expcam.pos-s->pos;
			dir.normalize();
			s->expcam.pos=s->expcam.pos;
			s->expcam.rotate(s->expcam.Z,dir);
			flyengine->set_camera(&s->expcam);
			flyengine->draw_bsp();
			flyengine->set_camera(s);
			}
		else 
			{
			flyengine->set_camera(s);
			flyengine->draw_bsp();
			}
		}
		break;
	case FLYM_DRAWTEXT:
		((ship *)(flyengine->cam))->draw_game_status();
		break;
	case FLYM_MPUPDATE:
		((ship *)(flyengine->cam))->mp_send_pos(
			FLYMP_MSG_POS,
			0xf|
			((ship *)(flyengine->cam))->flag|
			(((ship *)(flyengine->cam))->points<<16));
		return 0;
	case FLYM_MPMESSAGE:
		mp_message(param,(mp_msg *)data);
		return 0;
	case FLYM_INITSCENE:
		init_scene();
		break;
	case FLYM_CLOSESCENE:
		break;
	}
	return 1;
}

void mp_message(int from,mp_msg *msg)
{	
	switch( msg->type )
		{
		case FLYMP_MSG_POS:
			{
				mp_data *data=(mp_data *)&msg->type;
				ship *s=(ship *)directx->players[from].data;
				if (from>0)
					{
					s->remove_from_bsp();
					s->pos=data->pos;
					s->vel=data->vel;
					s->Y=data->Y;
					s->Z=data->Z;
					s->X.cross(s->Y,s->Z);
					s->flag=data->flag&0xffff;
					s->points=data->flag>>16;
					s->update_mat();
					s->add_to_bsp();
					}
				if (from>=0 && ((data->flag&0xf)!=0xf))
					{
					if (s->g[data->flag&0xf])
						s->g[data->flag&0xf]->fire(s,from);
					if (data->flag&0x10)
						s->speedboost=s->speedboost0;
					else s->speedboost=0;
					}
			}
			break;
		case FLYMP_MSG_DAMAGE:
			{
				mp_data2 *data=(mp_data2 *)&msg->type;
				ship *s=(ship *)directx->players[from].data;
				s->force+=data->v;
				s->shield-=data->f;
				s->lasthittime=flyengine->cur_time;
				s->lasthitfrom=from;
				if (from==0)
					flyengine->filter.x+=data->f>1.0f?1.0f:data->f;
			}
			break;
		case FLYMP_MSG_KILL:
			{
				mp_data *data=(mp_data *)&msg->type;
				ship *s=(ship *)directx->players[from].data;
				s->flag2=s->exptime;
				s->expcam.pos=s->pos;
				s->expcam.node=s->node;
				*((local_system *)&s->expcam)=*((local_system *)s);
				int i;
				for( i=0;i<directx->nplayers;i++ )
					if (directx->players[i].dpid==data->flag)
						break;
				if (from==i)
					if (i==0)
						{
						flyengine->set_status_msg("YOU COMMITTED SUICIDE",directx->players[i].name);
						((ship *)flyengine->cam)->points--;
						}
					else
						flyengine->set_status_msg("%s COMMITTED SUICIDE",directx->players[i].name);
				else
					if (i==0)
						{
						((ship *)flyengine->cam)->points++;
						flyengine->set_status_msg("YOU KILLED %s",directx->players[from].name);
						}
					else 
					if (from==0)
						flyengine->set_status_msg("%s KILLED YOU",directx->players[i].name);
					else 
						flyengine->set_status_msg("%s KILLED %s",directx->players[i].name,directx->players[from].name);
			}
			break;
		case FLYMP_MSG_EXPLODE:
			{
				mp_data *data=(mp_data *)&msg->type;
				ship *s=(ship *)directx->players[from].data;
				if (s->exp) 
					s->exp->do_explode(data->pos,data->Z,from);
				s->flag2--;
				s->remove_from_bsp();
			}
			break;
		case FLYMP_MSG_JOIN:
			{
				player_data *data=(player_data *)&msg->type;
				ship *s=(ship *)flyengine->cam->clone();
				s->pos.null(); s->vel.null(); s->force.null();
				s->player=directx->add_player(data->name,data->dpid,s);
				flyengine->set_status_msg("%s HAS JOINED THE GAME",data->name);
				flyengine->activate(s,(directx->mpmode==FLYMP_SERVER));
				if (directx->mpmode==FLYMP_SERVER)
				{
					powerup *p=0;
					while( p=(powerup *)flyengine->get_next_active_object(p,TYPE_POWERUP) )
					{
						static mp_data d;
						d.type=FLYMP_MSG_POWERUPMOVE;
						d.dpid=DPID_SERVERPLAYER;
						d.flag=p->valuetype;
						d.pos=p->pos;
						directx->send_message((mp_msg *)&d,sizeof(mp_data),data->dpid);
					}
				}
			}
			break;
		case FLYMP_MSG_QUIT:
			{
				player_data *data=(player_data *)&msg->type;
				if (from<directx->nplayers)
					{
					flyengine->set_status_msg("%s HAS LEFT THE GAME",directx->players[from].name);
					bsp_object *obj=(bsp_object *)directx->remove_player(from);
					for( int i=from;i<directx->nplayers;i++ )
						((ship *)directx->players[i].data)->player=i;
					if (obj) obj->life=-1;
					}
			}
			break;
		case FLYMP_MSG_POWERUPMOVE:
			{
				mp_data *data=(mp_data *)&msg->type;
				powerup *p=0;
				while(p=(powerup *)flyengine->get_next_active_object(p,TYPE_POWERUP))
					if (p->valuetype==(int)data->flag)
						break;
				if (p)
					{
					p->pos=data->pos;
					p->life=p->source->life;
					}
			}
			break;
		case FLYMP_MSG_POWERUPGET:
			{
				mp_data *data=(mp_data *)&msg->type;
				powerup *p=0;
				while(p=(powerup *)flyengine->get_next_active_object(p,TYPE_POWERUP))
					if (p->valuetype==(int)data->flag)
						break;
				if (p)
					p->powerup_get((ship *)directx->players[from].data);
			}
			break;
		}
}

void missile_find(void *data,bsp_object *e)
{
	static vector v,hitip;
	static float f;
	static int hitface;
	missile *t=(missile *)data;

	if (e->type==TYPE_SHIP || (e->type==TYPE_ROBOT && t->player!=-1))
		{
		if (e->type==TYPE_SHIP && t->player==((ship *)e)->player)
			return;
		v=e->pos-t->pos;
		f=v.length();
		if (f<t->lookrange && f<t->enemydist)
			{
			v/=f;
			if (vec_dot(v,t->Z)<t->lookangle)
				return;
			
			if (flyengine->collision_test(flyengine->bsp,t->pos,e->pos,TYPE_STATIC_MESH))
				return;

			t->enemydist=f;
			t->enemy=e;
			}
		}
}

void mine_find(void *data,bsp_object *e)
{
	static vector v,hitip;
	static float f;
	static int hitface;
	mine *t=(mine *)data;

	if (e->type==TYPE_SHIP || (e->type==TYPE_ROBOT && t->player!=-1) )
		{
		v=e->pos-t->pos;
		f=v.length();
		if (f<t->lookrange && f<t->enemydist)
			{
			v/=f;
			if (flyengine->collision_test(flyengine->bsp,t->pos,e->pos,TYPE_STATIC_MESH))
				{
				flyengine->excludecollision=0;
				return;
				}

			t->enemydist=f;
			t->enemy=e;
			}
		}
}

void init_scene()
{
	bsp_object *obj;

	obj=0;
	while( obj=flyengine->get_next_stock_object(obj,TYPE_MINE) )
		if (((mine *)obj)->lookrange!=0.0f)
			((mine *)obj)->mine_find=mine_find;
	obj=0;
	while( obj=flyengine->get_next_stock_object(obj,TYPE_MISSILE) )
		if (((missile *)obj)->lookrange!=0.0f)
			((missile *)obj)->missile_find=missile_find;
}
