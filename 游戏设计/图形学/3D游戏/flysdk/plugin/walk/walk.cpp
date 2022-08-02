#include "walk.h"

void mp_message(int from,mp_msg *msg);
void draw_game_status();

person_desc cd_person;
jump_pad_desc cd_jump_pad;
birth_pad_desc cd_birth_pad;
gib_desc cd_gib;

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
	};
	return TRUE;
}

__declspec( dllexport )
int num_classes()
{
	return 4;
}

__declspec( dllexport )
class_desc *get_class_desc(int i)
{
	switch(i)
	{
	case 0:
		return &cd_birth_pad;
	case 1:
		return &cd_jump_pad;
	case 2:
		return &cd_gib;
	case 3:
		return &cd_person;
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
			flyengine->set_camera(flyengine->cam);
			flyengine->draw_bsp();
		
			if (flyengine->stencil)
				{
				flyengine->start_text_mode();
				glEnable(GL_STENCIL_TEST);
				glStencilFunc(GL_NOTEQUAL,0,~0);
				glColor3fv(&flyengine->shadowcolor.x);
				glStencilOp(GL_KEEP,GL_KEEP,GL_KEEP);
				glBlendFunc(GL_ZERO, GL_SRC_COLOR);
				glRecti(0, 0, screen_sx, screen_sy);
				glDisable(GL_STENCIL_TEST);
				}
			}
		break;
	case FLYM_DRAWTEXT:
		draw_game_status();
		break;
	case FLYM_MPUPDATE:
		((person *)(flyengine->player))->mp_send_pos(
			FLYMP_MSG_POS,
			0xf|
			((person *)(flyengine->player))->flag|
			(((person *)(flyengine->player))->points<<16));
		return 0;
	case FLYM_MPMESSAGE:
		mp_message(param,(mp_msg *)data);
		return 1;
	}
	return 1;
}

void mp_message(int from,mp_msg *msg)
{	
	switch( msg->type )
		{
		case FLYMP_MSG_POS:
			{
				struct mp_data *data=(mp_data *)&msg->type;
				person *s=(person *)directx->players[from].data;
				if (from>0)
					{
					s->remove_from_bsp();
					s->pos=data->pos;
					s->vel=data->vel;
					s->walkvec=data->walkvel;
					s->ls.Y=data->Y;
					s->ls.Z=data->Z;
					s->ls.X=data->X;
					s->ls.update_mat();
					s->updownrot=data->rot;
					*((local_system *)s)=s->ls;
					s->rotate(s->updownrot,s->X);
					s->flag=data->flag&0xffff;
					s->points=(short)(data->flag>>16);
					s->add_to_bsp();
					}
				if (from>=0 && ((data->flag&0xf)!=0xf))
					if (s->g)
					{
						s->g->fire(s,s->player);
						s->cur_anim_time=flyengine->cur_time;
						s->cur_anim=2;
						s->loop_anim=0;
					}
			}
			break;
		case FLYMP_MSG_DAMAGE:
				{
				struct mp_data_damage *data=(mp_data_damage *)&msg->type;
				person *p=(person *)directx->players[from].data;
				p->curshield-=data->value;
				p->jumpvec=data->pushvec;
				p->jumpflag=50;
				if (from==0)
					flyengine->filter.x=1.0f;
				}
			break;
		case FLYMP_MSG_KILL:
			{
				struct mp_data_kill *data=(mp_data_kill *)&msg->type;
				person *p=(person *)directx->players[from].data;
				int i;
				for( i=0;i<directx->nplayers;i++ )
					if (directx->players[i].dpid==data->dpidpoints)
						break;
				p->die(i,data->hitpos,data->birthpad);
			}
			break;
		case FLYMP_MSG_JOIN:
			{
				player_data *data=(player_data *)&msg->type;
				person *p=(person *)flyengine->cam->clone();
				p->pos.null(); p->vel.null(); p->force.null(); 
				p->walkvec.null(); p->jumpflag=0;
				p->player=directx->add_player(data->name,data->dpid,p);
				flyengine->set_status_msg("%s HAS JOINED THE GAME",data->name);
				flyengine->activate(p,(directx->mpmode==FLYMP_SERVER));
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
						((person *)directx->players[i].data)->player=i;
					if (obj) obj->life=-1;
					}
			}
			break;
		}
}

void draw_game_status()
{
	static DWORD t=timeGetTime();
	static int frame_rate=0,frame_count=0;
	static char str[256];
	frame_count++;
	if (flyengine->cur_time-t>1000)
		{
		frame_rate=frame_count*1000/(flyengine->cur_time-t);
		t=flyengine->cur_time;
		frame_count=0;
		}
	if (flyengine->cur_time - flyengine->status_msg_time > 2000)
		{
		sprintf(str,"FPS:%i N:%i",frame_rate,flyengine->nodedrawcount);
		flyengine->draw_text( screen_sx-96, 0, str );
		}

	for( int i=0;i<directx->nplayers;i++)
		{
		sprintf(str,"%s %03i %02i",directx->players[i].name,
			(int)(((person *)directx->players[i].data)->curshield*100),
			((person *)directx->players[i].data)->points);
		flyengine->draw_text( 0, i*16, str );
		}
}

