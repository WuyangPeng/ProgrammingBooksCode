#include "walk.h"

void person::init()
{
	if (bp==0)
		bp=(birth_pad *)flyengine->get_next_active_object(0,TYPE_BIRTH_PAD);
	if (bp==0)
		{
		if (flyengine->get_random_point(pos,height)==0)
			pos.null();
		}
	else
		{
		pos=bp->pos;
		bp->animtime0=flyengine->cur_time;
		}
	pos.z+=height;

	align_z(vector(1,0,0));
	ls=*((local_system *)this);
	updownrot=0;
	
	vel.null();
	force.null();
	
	contactobj=0;
	jumpflag=0;
	curshield=shield;

	zoompos=0;
	flyengine->camangle=zoomangle1;
}

mesh *person::ray_intersect(vector& ro,vector& rd,vector& ip,float& dist,int &facenum,float rad)
{ 
	if (p_anim[cur_anim]) 
	{
		static float d1,d2;
		vector ro_local=ro-pos;
		vector rd_local=rd*mat_t;
		ro_local.z+=height/2;
		ro_local=ro_local*mat_t;
		if (p_anim[cur_anim]->bbox.ray_intersect(ro_local,rd_local,d1,d2))
		{
		facenum=p_anim[cur_anim]->ray_intersect(ro_local,rd_local,ip,dist,rad);
		if (facenum>-1)
			{
			ip=ip*mat+pos;
			ip.z-=height/2;
			bsp_object *so=flyengine->stepobj;
			
			if (directx && directx->mpmode==FLYMP_SERVER)
			if (flyengine->stepobj)
			if (flyengine->stepobj->type==TYPE_LASER || flyengine->stepobj->type==TYPE_MISSILE)
			if (dist<1.0f)
				{
				int from=((gun_projectile *)flyengine->stepobj)->player;
				float value=((gun_projectile *)(flyengine->stepobj))->damage;
				curshield-=value;
				if (directx->mpmode==FLYMP_SERVER)
					mp_send_damage(from,ip,value);
				else flyengine->filter.x=1.0f;
				if (curshield<=0)
					die(((gun_projectile *)flyengine->stepobj)->player,ip,-1);
				}

			return p_anim[cur_anim];
			}
		}
	}
	return 0;
}

void person::mp_send_pos(int msgtype,int msgflag)
{
	static struct mp_data data;
	
	data.type=msgtype;
	data.dpid=directx->players[player].dpid;
	data.flag=msgflag;
	data.pos=pos;
	data.vel=vel;
	data.walkvel=walkvec;
	data.X=ls.X;
	data.Y=ls.Y;
	data.Z=ls.Z;
	data.rot=updownrot;

	directx->send_message((mp_msg *)&data,sizeof(struct mp_data));
}

void person::mp_send_damage(int from,vector& pushvec,float value)
{
	static struct mp_data_damage data;
	
	data.type=FLYMP_MSG_DAMAGE;
	data.dpid=directx->players[player].dpid;
	data.from=from;
	data.pushvec=pushvec;
	data.value=value;

	directx->send_message((mp_msg *)&data,sizeof(struct mp_data_damage));
}

void person::die(int killer,vector& hitpos,int padindx)
{
	int i;
	if (node && gb)
	for( i=0;i<ngib;i++ )
		{
		gib *x=(gib *)gb->clone();
		x->pos=pos;
		x->pos.x+=FRAND*radius;
		x->pos.y+=FRAND*radius;
		x->pos.z+=FRAND*radius;
		x->vel=x->pos-hitpos;
		x->vel.normalize();
		x->vel*=gibforce;
		flyengine->activate(x);
		}

	int npad=0;
	birth_pad *pad=0,*pads[16];
	while( pad=(birth_pad *)flyengine->get_next_active_object(pad,TYPE_BIRTH_PAD))
		pads[npad++]=pad;
	if (padindx==-1&&npad)
		padindx=rand()%npad;
	else if (padindx>=npad)
			padindx=-1;
	if (padindx==-1)
		bp=0;
	else bp=pads[padindx];

	if (player==killer)
		if (killer==0)
			{
			flyengine->set_status_msg("YOU COMMITTED SUICIDE",directx->players[killer].name);
			((person *)flyengine->player)->points--;
			}
		else
			flyengine->set_status_msg("%s COMMITTED SUICIDE",directx->players[killer].name);
	else
		if (killer==0)
			{
			((person *)flyengine->player)->points++;
			flyengine->set_status_msg("YOU KILLED %s",directx->players[player].name);
			}
		else 
		if (player==0)
			flyengine->set_status_msg("%s KILLED YOU",directx->players[killer].name);
		else 
			flyengine->set_status_msg("%s KILLED %s",directx->players[killer].name,directx->players[player].name);

	if (directx->mpmode==FLYMP_SERVER)
		mp_send_kill(killer,padindx,hitpos);

	init();
	add_to_bsp();
}

void person::mp_send_kill(int killer,int pad,vector& hitpoint)
{
	static struct mp_data_kill data;
	
	data.type=FLYMP_MSG_KILL;
	data.dpid=directx->players[player].dpid;
	data.dpidpoints=directx->players[killer].dpid;
	data.pos=pos;
	data.hitpos=hitpoint;
	data.birthpad=pad;

	directx->send_message((mp_msg *)&data,sizeof(struct mp_data_kill));
}

int person::step(int dt)    
{
	if (directx->mpmode==FLYMP_SERVER && player==0)
		{
		life=-1;
		flyengine->cam=source;
		flyengine->player=source;
		directx->players[0].data=0;
		return 0;
		}

	vector p,v,ip,rd;
	float dist;
	mesh *lastcontact=contactobj;

	// if outside level, wrong place
	if (node==0)
	{
		if (player==0)
			die(0,vector(0,0,0),-1);
		return 1;
	}

	// if spoton, illum
	if (spot && (flag&0x100))
		spot->reposition(this);

	// check keys/mouse with horizontal look dir
	if (player==0)
		do_input(dt);

	// add jump forces 
	if (jumpflag!=0)
	{
	jumpflag-=dt;
	if (jumpflag<=0)
		{
		force+=jumpvec*((float)(dt+jumpflag)/dt);
		jumpflag=0;
		}
	else force+=jumpvec;
	}

	// exclude the player model from any collision
	flyengine->excludecollision=this;

	// apply forces and compute collision

	v=vel+force*((float)dt/mass);
	p=pos+(walkvec+vel)*(float)dt;
	compute_collision(p,v);
	pos=p;
	vel=v;
	force.null();

	contactobj=0;
	p.z-=height;
	rd=p-pos;

	bsp_object *o=0;
	while( o=flyengine->get_next_active_object(o,TYPE_JUMP_PAD) )
		if (contactobj=o->ray_intersect(pos,rd,ip,dist,contactfacenum))
			if (dist<=1.0f && jumpflag==0)
				{
				jumpvec=
					contactobj->faces[contactfacenum]->normal*
					((jump_pad *)o)->jumpforce;
				if (((jump_pad *)o)->invert)
					{
					jumpvec.x=-jumpvec.x;
					jumpvec.y=-jumpvec.y;
					}
				jumpflag=((jump_pad *)o)->forcetime;
				break;
				}
			else contactobj=0;

	if (flyengine->collision_bsp(flyengine->bsp,pos,p))
		{
		contactobj=flyengine->hitmesh;
		ip=flyengine->hitip;
		contactfacenum=flyengine->hitface;
		} 
	else contactobj=0;

	// restore player model collision
	flyengine->excludecollision=0;

	// if a network player, return
	if (player!=0) 
		return 1;

	// if in contact
	if (contactobj)
		{
		if (lastcontact==0)
			vel.null();
		pos=ip;
		pos.z+=height-0.1f;
		}
	else 
		force.z-=gravity;

	directx->set_listener(
		&pos.x,0,
		&ls.Y.x,&ls.Z.x);

	return 1;
}

void person::do_input(int dt)
{
	*((local_system *)this)=ls;

	static int lastmouse[2][2]={ { 0,0 },{ 0,0 } },lm=0,jumpkeyflag=0;
	float mousedx=(directx->dims.lX+lastmouse[0][0]+lastmouse[1][0])/3.0f;
	float mousedy=(directx->dims.lY+lastmouse[0][1]+lastmouse[1][1])/3.0f;
	lastmouse[lm][0]=directx->dims.lX;
	lastmouse[lm][1]=directx->dims.lY;
	lm=!lm;

	unsigned char *diks=directx->diks;

	if (diks[0x39]&0x80) // SPACE key
		if (jumpkeyflag==0)
		{
		jumpkeyflag=1;
		if ( jumpflag==0 && contactobj)
			{
			jumpvec.null();
			jumpvec.z+=jumpforce;
			jumpflag=jumpforcetime;
			}
		}
		else ;
	else jumpkeyflag=0;

	walkvec.null();
	if (diks[0x38]&0x80)	// ALT key
		{
		if (diks[0xcb]&0x80)	// left arrow
			walkvec-=X*walkvel;

		if (diks[0xcd]&0x80)	// right arrow
			walkvec+=X*walkvel;

		if (diks[0x1f]&0x80||	// S key
			diks[0xc8]&0x80)	// up arrow
			walkvec-=Z*walkvel;

		if (diks[0x2d]&0x80||	// X key
			diks[0xd0]&0x80)	// down arrow
			walkvec+=Z*walkvel;
		}
	else
		{
		if (diks[0xc8]&0x80)	// up arrow
			{
			updownrot-=dt*rotvel;
			if (updownrot<-80) updownrot=-80;
			}
		
		if (diks[0xd0]&0x80)	// down arrow
			{
			updownrot+=dt*rotvel;
			if (updownrot>80) updownrot=80;
			}

		if (diks[0xcb]&0x80)	// left arrow
			rotate(dt*rotvel,Y);

		if (diks[0xcd]&0x80)	// right arrow
			rotate(-dt*rotvel,Y);

		if (diks[0x10]&0x80)	// Q key
			walkvec-=X*walkvel;

		if (diks[0x12]&0x80)	// E key
			walkvec+=X*walkvel;

		if (diks[0x1f]&0x80)	// S key
			walkvec-=Z*walkvel;

		if (diks[0x2d]&0x80)	// X key
			walkvec+=Z*walkvel;
		}

	if (diks[0x11]&0x80)   // W key
		if ((flag&0x1000)==0)
			flag^=0x1100;
		else ;
	else if (flag&0x1000)
			flag^=0x1000;

	if (mousedx)	// mouse X
		rotate(-mousedx*mousespeed,Y);

	if (mousedy)	// mouse Y
		{
		updownrot+=mousedy*mousespeed;
		if (updownrot<-80) updownrot=-80;
		if (updownrot>80) updownrot=80;
		}

	ls=*((local_system *)this);
	rotate(updownrot,X);

	if (g)
	if (directx->diks[0x9d]&0x80 ||
		directx->dims.rgbButtons[0]&0x80)
		if (g->fire_status())
			if (directx->mpmode==FLYMP_NOMP)
			{
				g->fire(this,player);
				cur_anim_time=flyengine->cur_time;
				cur_anim=2;
				loop_anim=0;
			}
			else mp_send_pos(FLYMP_MSG_POS,flag|(points<<16));

	if (directx->dims.rgbButtons[1]&0x80)
		{
		zoompos+=dt;
		if (zoompos>zoomtime) 
			zoompos=zoomtime;
		}
	else
		{
		zoompos-=dt;
		if (zoompos<0) 
			zoompos=0;
		}
	flyengine->camangle=zoomangle1+(zoomangle2-zoomangle1)*((float)zoompos/zoomtime);
}

void person::draw()
{
	if (player==0) return;

	if ((cur_anim&0xfe)==0)
		if (vel.x!=0.0f || vel.y!=0.0f || vel.z!=0.0f ||
			walkvec.x!=0.0f || walkvec.y!=0.0f || walkvec.z!=0.0f)
			cur_anim=1;
		else 
			cur_anim=0;

	if (p_anim[cur_anim]==0 || w_anim[cur_anim]==0) 
		return;

	int anim_time=p_anim[cur_anim]->nframes*100;
	int ikey=flyengine->cur_time-cur_anim_time;
	if (loop_anim==0)
		if (ikey>=anim_time)
			ikey=anim_time;
	float fkey=(ikey%anim_time)/(float)anim_time;
	p_anim[cur_anim]->set_key(fkey);
	w_anim[cur_anim]->set_key(fkey);
	p_anim[cur_anim]->texpic=skin;

	if(personshadow && flyengine->stencil==0)
		{
		personshadow->reposition(this);
		personshadow->draw();
		}

	if (flyengine->hwlights)
		{
		p_anim[cur_anim]->color.vec(1,1,1,1);
		w_anim[cur_anim]->color.vec(1,1,1,1);
		dynlights.init_draw(this);
		}
	else if (node)
		{
		p_anim[cur_anim]->color=node->color+dynlight;
		w_anim[cur_anim]->color=node->color+dynlight;
		dynlight.null();
		}
	glPushMatrix();
	glTranslatef(pos.x,pos.y,pos.z-height/2);
	glMultMatrixf((float *)&ls.mat);
	p_anim[cur_anim]->draw();
	w_anim[cur_anim]->draw();
	if (flyengine->stencil)
	{
		glDisable(GL_LIGHTING);
		int i,mini=-1;
		float f,minf=BIG;
		vector lp;
		for( i=0;i<dynlights.nlights;i++ )
		{
			f=(dynlights.pos[i]-pos).length();
			if (f<minf)
			{
				minf=f;
				mini=i;
			}
		}
		if (mini!=-1)
		{
			lp=dynlights.pos[mini]-pos;
			lp.z+=height/2;
			lp=lp*mat_t;
			lp.normalize();
			lp*=flyengine->shadowdepth;
			p_anim[cur_anim]->draw_shadow_volume(lp);
			w_anim[cur_anim]->draw_shadow_volume(lp);
		}
	}
	glPopMatrix();

	if (flyengine->hwlights)
		dynlights.end_draw();

	if (loop_anim==0 && ikey==anim_time)
	{
		cur_anim=0;
		loop_anim=1;
	}
}

int person::get_custom_param_desc(int i,param_desc *pd)
{
	if (pd!=0)
	switch(i)
	{
		case 0:
			pd->type='f';
			pd->data=&height;
			strcpy(pd->name,"height");
			break;
		case 1:
			pd->type='f';
			pd->data=&jumpforce;
			strcpy(pd->name,"jumpforce");
			break;
		case 2:
			pd->type='i';
			pd->data=&jumpforcetime;
			strcpy(pd->name,"jumpforcetime");
			break;
		case 3:
			pd->type='f';
			pd->data=&gravity;
			strcpy(pd->name,"gravity");
			break;
		case 4:
			pd->type='f';
			pd->data=&walkvel;
			strcpy(pd->name,"walkvel");
			break;
		case 5:
			pd->type='f';
			pd->data=&rotvel;
			strcpy(pd->name,"rotvel");
			break;
		case 6:
			pd->type='f';
			pd->data=&mousespeed;
			strcpy(pd->name,"mousespeed");
			break;
		case 7:
			pd->type=TYPE_SPOT_LIGHT;
			pd->data=&spot;
			strcpy(pd->name,"spot");
			break;
		case 8:
			pd->type=TYPE_GUN;
			pd->data=&g;
			strcpy(pd->name,"gun");
			break;
		case 9:
			pd->type='m';
			pd->data=&p_anim[0];
			strcpy(pd->name,"p_stand");
			break;
		case 10:
			pd->type='m';
			pd->data=&p_anim[1];
			strcpy(pd->name,"p_run");
			break;
		case 11:
			pd->type='m';
			pd->data=&p_anim[2];
			strcpy(pd->name,"p_attack");
			break;
		case 12:
			pd->type='m';
			pd->data=&w_anim[0];
			strcpy(pd->name,"w_stand");
			break;
		case 13:
			pd->type='m';
			pd->data=&w_anim[1];
			strcpy(pd->name,"w_run");
			break;
		case 14:
			pd->type='m';
			pd->data=&w_anim[2];
			strcpy(pd->name,"w_attack");
			break;
		case 15:
			pd->type=TYPE_SHADOW;
			pd->data=&personshadow;
			strcpy(pd->name,"shadow");
			break;
		case 16:
			pd->type='p';
			pd->data=&skin;
			strcpy(pd->name,"skin");
			break;
		case 17:
			pd->type='i';
			pd->data=&ngib;
			strcpy(pd->name,"ngib");
			break;
		case 18:
			pd->type=TYPE_GIB;
			pd->data=&gb;
			strcpy(pd->name,"gibobj");
			break;
		case 19:
			pd->type='f';
			pd->data=&gibforce;
			strcpy(pd->name,"gibforce");
			break;
		case 20:
			pd->type='i';
			pd->data=&zoomtime;
			strcpy(pd->name,"zoomtime");
			break;
		case 21:
			pd->type='f';
			pd->data=&zoomangle1;
			strcpy(pd->name,"zoomangle1");
			break;
		case 22:
			pd->type='f';
			pd->data=&zoomangle2;
			strcpy(pd->name,"zoomangle2");
			break;
		case 23:
			pd->type='f';
			pd->data=&shield;
			strcpy(pd->name,"shield");
			break;
	}
	return 24;
}

int person::message(vector& p,float rad,int msg,int param,void *data)
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

		if (directx->mpmode!=FLYMP_CLIENT)
		{
			float value=*((float *)data)*(1.0f-len/rad);
			jumpvec=v*((*((float *)data))/(len*100));
			if (contactobj && jumpvec.z<0)
				jumpvec.z=-jumpvec.z;
			jumpflag=50;
			if (directx->mpmode==FLYMP_SERVER)
				mp_send_damage(param,jumpvec,value);
			else flyengine->filter.x=1.0f;
			curshield-=value;
			if (curshield<=0)
				die(param,p,-1);
		}
	}
	else
	if (flyengine->hwlights)
		if (msg==FLYOBJM_ILLUM || msg==FLYOBJM_DYNILLUM)
			dynlights.add_light(p,*((vector *)data),rad);
		else ;
	else if (msg==FLYOBJM_ILLUM)
	{
		float fac=(p-pos).length()/rad;
		if (fac<1.0f)
			dynlight+=*((vector *)data)*(1.0f-fac);
	}

	return 1;
}
