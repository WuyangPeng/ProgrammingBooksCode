#include "game.h"

ship::ship() 
{ 
	type=TYPE_SHIP;
	lasthitfrom=-1;
	lasthittime=0;
	flag=0;
	flag2=0;
	flag3=0;
	points=0; 
	player=0;
	abtime=0;
	rotvel.null(); 
	rotforce.null(); 
	mouserot.null(); 
	dynlight.null();
	firesel=0;
}

int ship::message(vector& p,float rad,int msg,int param,void *data)
{
	if (msg==FLYOBJM_DAMAGE)
	{
		if (directx->mpmode!=FLYMP_CLIENT && (flag3&0x20000)==0)
			{
			float len;
			mp_data2 msg;

			msg.v=pos-p;
			len=msg.v.length();
			if (len>rad || len<SMALL)
				return 0;

			flyengine->excludecollision=this;
			if(flyengine->collision_test(flyengine->bsp, p, pos))
				{
				flyengine->excludecollision=0;
				return 0;
				}
			flyengine->excludecollision=0;

			lasthittime=flyengine->cur_time;
			lasthitfrom=param;

			msg.f=*((float *)data);
			msg.v*=msg.f/(len*100.0f);
//			msg.f=*((float *)data)*(1-len/rad);
//			msg.v*=msg.f/(len*100.0f);
			force+=msg.v;
			shield-=msg.f;
			msg.type=FLYMP_MSG_DAMAGE;
			msg.from=directx->players[player].dpid;

			directx->send_message((mp_msg *)&msg,sizeof(mp_data2));

			if (directx->mpmode==FLYMP_NOMP)
				flyengine->filter.x+=msg.f>1.0f?1.0f:msg.f;
			}
	}
	else
	if (msg==FLYOBJM_ILLUM)
	{
		float fac=(p-pos).length()/rad;
		if (fac<1.0f)
			dynlight+=*((vector *)data)*(1.0f-fac);
	}

	return 1;
}

int ship::step(int dt)
{
	float len;

	switch( directx->mpmode )
	{
	case FLYMP_SERVER:
		{
		if (player==0)
			{
			life=-1;
			flyengine->cam=source;
			flyengine->player=source;
			directx->players[0].data=0;
			return 0;
			}

		if (shield<0 && flag2==0)
			{
			flag2=exptime;
			mp_send_pos(
				FLYMP_MSG_KILL,
				(lasthitfrom>=0)?directx->players[lasthitfrom].dpid:-1);
			}

		if (flag2==0 || flag2==exptime)
			{
			len=vel.length();
			if (len>0)
				{
				vel/=len;
				if (flag2==0)
					{
					len-=dt*veldamp;
					if (len<0) len=0;

					if (len>maxvel+speedboost)
						len=maxvel+speedboost;
					}
				vel*=len;
				}

			if (shield<0 && flag2==exptime)
				force.z-=0.0005f;

			flyengine->excludecollision=this;
			particle::step(dt);
			flyengine->excludecollision=0;
			}

		if (flag2)
			if (flag2==exptime)
				if (flyengine->hitobj)
					{
					flag2-=dt;
					mp_send_pos(
						FLYMP_MSG_EXPLODE,
						(lasthitfrom>=0)?directx->players[lasthitfrom].dpid:-1);
					remove_from_bsp();
					}
				else { ; }
			else 
				if (flag2>dt)
					flag2-=dt;
				else
					{
					pos=source->pos;
					add_to_bsp();
					vel.null();
					align_z(vector(0,0,1));
					rotate(rot);
					shield=((ship *)source)->shield;
					flag2=0;
					flag3=0;
					}

		if (flag3)
			{
			int i=flag3&0xffff;
			if (i<dt)
				flag3=0;
			else 
				flag3=(flag3&0xffff0000)|(i-dt);
			}

		force.null();
		life=1;
		}
		break;
	case FLYMP_NOMP:
		if (shield<0 && flag2==0)
			{
			flag2=exptime;
			expcam.pos=pos;
			expcam.node=node;
			*((local_system *)&expcam)=*((local_system *)this);
			}
	case FLYMP_CLIENT:
		{
		if (flag2==0 || flag2==exptime)
			{
			if (player==0)
				{
				if (flag2==0)
					check_keys(dt);

				rotvel+=rotforce;
				rotforce.x=rotforce.y=rotforce.z=0;
				rotate(mouserot);
				mouserot.x=mouserot.y=0;

				len=rotvel.length();
				if (len>0)
					{
					rotvel/=len;
					len-=dt*angulardamp;
					if (len<0) len=0;
					if (len>angularmaxvel) len=angularmaxvel;
					rotvel*=len;
					rotate(rotvel*(float)dt);
					}
				}

			len=vel.length();
			if (len>0)
				{
				vel/=len;
				if (flag2==0)
					{
					len-=dt*veldamp;
					if (len<0) len=0;

					if (len>maxvel+speedboost)
						len=maxvel+speedboost;
					}
				vel*=len;
				}

			if (shield<0 && flag2==exptime)
				force.z-=0.0005f;

			flyengine->excludecollision=this;
			particle::step(dt);
			flyengine->excludecollision=0;
			}

		if (flag2)
			if (flag2==exptime)
				if (directx->mpmode==FLYMP_NOMP && flyengine->hitobj)
					{
					if (exp) 
						exp->do_explode(pos,Z,player);
					flag2-=dt;
					remove_from_bsp();
					}
				else { ; }
			else 
				if (flag2>dt)
					flag2-=dt;
				else
					{
					pos=source->pos;
					add_to_bsp();
					vel.null();
					align_z(vector(0,0,1));
					rotate(rot);
					shield=((ship *)source)->shield;
					flag2=0;
					flag3=0;
					}

		if (flag3)
			{
			int i=flag3&0xffff;
			if (i<dt)
				flag3=0;
			else 
				flag3=(flag3&0xffff0000)|(i-dt);
			}

		force.null();
		life=1;

		if (flag&0x10 && englight)
			{
			englight->pos=pos+Z*engpos;
			flyengine->stepobj=englight;
			englight->step(dt);
			}
		
		if (spot && (flag&0x100))
			spot->reposition(this);
		}
		break;
	}
	
	if (player==0)
		directx->set_listener(&pos.x,0,&Y.x,&Z.x);

	return 1;
}

void ship::draw()
{
	if (objmesh==0) 
		return;
	if (player==0 && flag2!=exptime)
		return;
	if (flag2 && flag2!=exptime)
		return;
	
	// init dynamic light
	if (flyengine->hwlights)
		{
		objmesh->color.vec(1,1,1,1);
		dynlights.init_draw(this);
		}
	else if (node)
		{
		objmesh->color=node->color+dynlight;
		dynlight.null();
		}

	// draw ship and shield
	glPushMatrix();
	glTranslatef(pos.x,pos.y,pos.z);
	glMultMatrixf((float *)&mat);
	if (flag3&SHIP_FLAG3_INVISIBLE)
		objmesh->color.w=invistransp;
	else objmesh->color.w=1.0;
	objmesh->draw();
	if (shieldmesh)
		if ((flag3&SHIP_FLAG3_INVENSIBLE) || flyengine->cur_time-lasthittime<500 || (flag2==exptime))
		{
		glDepthMask(GL_FALSE);
		glBlendFunc(GL_ONE, GL_ONE);
		if (flag2==exptime)
			{
			shieldmesh->color=killcolor;
			shieldmesh->color.w=1.0f;
			}
		else
		if (flag3&SHIP_FLAG3_INVENSIBLE)
			{
			shieldmesh->color=invencolor;
			shieldmesh->color.w=1.0f;
			}
		else 
			{
			float t=1.0f-(flyengine->cur_time-lasthittime)/500.0f;
			shieldmesh->color=hitcolor*t;
			shieldmesh->color.w=t;
			}
		shieldmesh->scrollu=shieldmesh->scrollv=(flyengine->cur_time%750)/750.0f;
		shieldmesh->draw();
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDepthMask(GL_TRUE);
		}
	glPopMatrix();

	// end dynamic lights
	if (flyengine->hwlights)
		dynlights.end_draw();

	// draw ship engine light
	if (flag&0x10 && englight)
		{
		englight->pos=pos+Z*engpos;
		englight->draw();
		}

	// draw ship engine halo
	if (enghalo && (flag3&SHIP_FLAG3_INVISIBLE)==0)
		{
		enghalo->pos=pos+Z*engpos;
		enghalo->color.w=vel.length()/maxvel*0.6f+0.2f;
		if (enghalo->color.w>0.6f) 
			enghalo->color.w=0.6f;
		enghalo->draw();
		}
}

int ship::get_custom_param_desc(int i,param_desc *pd)
{
	if (pd==0)
		return 33;
	else 
	switch(i)
	{
		case 0:
			pd->type='p';
			pd->data=&display;
			strcpy(pd->name,"display");
			break;
		case 1:
			pd->type='f';
			pd->data=&speedboost0;
			strcpy(pd->name,"speedboost");
			break;
		case 2:
			pd->type='f';
			pd->data=&shield;
			strcpy(pd->name,"shield");
			break;
		case 3:
			pd->type='f';
			pd->data=&maxshield;
			strcpy(pd->name,"maxshield");
			break;
		case 4:
			pd->type='f';
			pd->data=&maxvel;
			strcpy(pd->name,"maxvel");
			break;
		case 5:
			pd->type='f';
			pd->data=&veldamp;
			strcpy(pd->name,"veldamp");
			break;
		case 6:
			pd->type='f';
			pd->data=&angularmaxvel;
			strcpy(pd->name,"angularmaxvel");
			break;
		case 7:
			pd->type='f';
			pd->data=&angulardamp;
			strcpy(pd->name,"angulardamp");
			break;
		case 8:
			pd->type='3';
			pd->data=&objmesh;
			strcpy(pd->name,"objmesh");
			break;
		case 9:
			pd->type='3';
			pd->data=&shieldmesh;
			strcpy(pd->name,"shieldmesh");
			break;
		case 10:
			pd->type=TYPE_EXPLODE;
			pd->data=&exp;
			strcpy(pd->name,"explode");
			break;
		case 11:
			pd->type='i';
			pd->data=&exptime;
			strcpy(pd->name,"exptime");
			break;
		case 12:
			pd->type='i';
			pd->data=&maxabtime;
			strcpy(pd->name,"maxabtime");
			break;
		case 13:
			pd->type=TYPE_LIGHT;
			pd->data=&englight;
			strcpy(pd->name,"englight");
			break;
		case 14:
			pd->type=TYPE_SPRITE_LIGHT;
			pd->data=&enghalo;
			strcpy(pd->name,"enghalo");
			break;
		case 15:
			pd->type='f';
			pd->data=&engpos;
			strcpy(pd->name,"engpos");
			break;
		case 16:
			pd->type=TYPE_SPOT_LIGHT;
			pd->data=&spot;
			strcpy(pd->name,"spot");
			break;
		case 17:
			pd->type='f';
			pd->data=&mousespeed;
			strcpy(pd->name,"mousespeed");
			break;
		case 18:
			pd->type='f';
			pd->data=&forcefactor;
			strcpy(pd->name,"forcefactor");
			break;
		case 19:
			pd->type='c';
			pd->data=&hitcolor;
			strcpy(pd->name,"hitcolor");
			break;
		case 20:
			pd->type='c';
			pd->data=&invencolor;
			strcpy(pd->name,"invencolor");
			break;
		case 21:
			pd->type='c';
			pd->data=&killcolor;
			strcpy(pd->name,"killcolor");
			break;
		case 22:
			pd->type='f';
			pd->data=&invistransp;
			strcpy(pd->name,"invistransp");
			break;
		case 23:
			pd->type='i';
			pd->data=&ng;
			strcpy(pd->name,"nguns");
			break;
		case 24:
			pd->type=TYPE_GUN;
			pd->data=&g[0];
			strcpy(pd->name,"gun1");
			break;
		case 25:
			pd->type=TYPE_GUN;
			pd->data=&g[1];
			strcpy(pd->name,"gun2");
			break;
		case 26:
			pd->type=TYPE_GUN;
			pd->data=&g[2];
			strcpy(pd->name,"gun3");
			break;
		case 27:
			pd->type=TYPE_GUN;
			pd->data=&g[3];
			strcpy(pd->name,"gun4");
			break;
		case 28:
			pd->type=TYPE_GUN;
			pd->data=&g[4];
			strcpy(pd->name,"gun5");
			break;
		case 29:
			pd->type=TYPE_GUN;
			pd->data=&g[5];
			strcpy(pd->name,"gun6");
			break;
		case 30:
			pd->type=TYPE_GUN;
			pd->data=&g[6];
			strcpy(pd->name,"gun7");
			break;
		case 31:
			pd->type=TYPE_GUN;
			pd->data=&g[7];
			strcpy(pd->name,"gun8");
			break;
		case 32:
			pd->type=TYPE_GUN;
			pd->data=&g[8];
			strcpy(pd->name,"gun9");
			break;
	}
	return 0;
}

void ship::check_keys(int time_step)
{
	static int lastmouse[2][2]={ { 0,0 },{ 0,0 } },lm=0;
	float mousedx=(directx->dims.lX+lastmouse[0][0]+lastmouse[1][0])/3.0f;
	float mousedy=(directx->dims.lY+lastmouse[0][1]+lastmouse[1][1])/3.0f;
	lastmouse[lm][0]=directx->dims.lX;
	lastmouse[lm][1]=directx->dims.lY;
	lm=!lm;

	unsigned char *diks=directx->diks;
		
	if (diks[0x38])
		{
		if (diks[0xcb])
			force-=X/forcefactor;
		if (diks[0xcd])
			force+=X/forcefactor;
		if (diks[0xc8])
			force+=Y/forcefactor;
		if (diks[0xd0])
			force-=Y/forcefactor;
		}
	else
		{
		if (diks[0xcb])
			rotforce.y+=1;
		if (diks[0xcd])
			rotforce.y-=1;
		if (diks[0xc8])
			rotforce.x-=1;
		if (diks[0xd0])
			rotforce.x+=1;
		}

	if (diks[0x1e])
		rotforce.z+=1;
	if (diks[0x20])
		rotforce.z-=1;

	if (diks[0x11])
		if ((flag&0x1000)==0)
			flag^=0x1100;
		else ;
	else if (flag&0x1000)
			flag^=0x1000;

	if (diks[0x10])
		force-=X/forcefactor;
	if (diks[0x12])
		force+=X/forcefactor;

	if (diks[0x1f] || diks[0x3A])
		force-=Z/forcefactor;
	if (diks[0x2d])
		force+=Z/forcefactor;

	if (diks[0x3A])
		{
		if (abtime>0)
			{
			speedboost=speedboost0;
			abtime-=time_step;
			flag|=0x10;
			}
		else 
			{
			abtime=0;
			speedboost=0.0f;
			flag&=0xff0f;
			}
		}
	else 
		{
		abtime+=time_step/4;
		if (abtime>maxabtime)
			abtime=maxabtime;
		speedboost=0.0f;
		flag&=0xff0f;
		}

	if (diks[0x38])
		{
		if (mousedx>4)
			force+=X/forcefactor;
		else if (mousedx<-4)
			force-=X/forcefactor;

		if (mousedy>4)
			force-=Y/forcefactor;
		else if(mousedy<-4)
			force+=Y/forcefactor;
		}
	else
		{
		mouserot.y=-mousedx/mousespeed;
		mouserot.x=mousedy/mousespeed;
		}

	int i;
	for( i=0;i<9;i++ )
		if (directx->diks[2+i])
			{
			firesel=i;
			break;
			}
	if (g[firesel])
	if (directx->diks[0x9d] || directx->diks[0x39] || 
		directx->dims.rgbButtons[0])
		if (g[firesel]->fire_status())
			if (directx->mpmode==FLYMP_NOMP)
				g[firesel]->fire(this,player);
			else mp_send_pos(FLYMP_MSG_POS,flag|firesel|(points<<16));
}

void ship::draw_game_status()
{
	static char str[256];
	int i,j,k;

	tc->use(display);
	glBegin(GL_QUADS);
		glTexCoord2f(0,1);
		glVertex2i(0,0);
		glTexCoord2f(0.375f,1);
		glVertex2i(48,0);
		glTexCoord2f(0.375f,0);
		glVertex2i(48,128);
		glTexCoord2f(0,0);
		glVertex2i(0,128);
	glEnd();

	tc->use(-1);
	glBegin(GL_QUADS);
		glColor4ub(153,255,178,255);
		j=18+(int)(104.0f*abtime/maxabtime);
		glVertex2i(5,18);
		glVertex2i(16,18);
		glVertex2i(16,j);
		glVertex2i(5,j);
	
		glColor4ub(40,40,255,255);
		j=18+(int)(104*shield/maxshield);
		glVertex2i(31,18);
		glVertex2i(42,18);
		glVertex2i(42,j);
		glVertex2i(31,j);
	glEnd();
	
	for( i=0;i<directx->nplayers;i++)
		{
		sprintf(str,"%s (%i)",directx->players[i].name,((ship *)directx->players[i].data)->points);
		flyengine->draw_text( 0, i*16, str );
		}
	k=screen_sy-16;
	j=screen_sx/2;
	for( i=0;i<ng;i++,j+=32 )
		{
		if (g[i])
			if (firesel==i)
				sprintf(str,"[%i]",g[i]->firecount);
			else sprintf(str,"%i",g[i]->firecount);
		flyengine->draw_text( j, k, str );
		}
	static DWORD t=timeGetTime();
	static int frame_rate=0,frame_count=0;
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
}

void ship::mp_send_pos(int msgtype,int msgflag)
{
	static struct mp_data data;
	
	data.type=msgtype;
	data.dpid=directx->players[player].dpid;
	data.flag=msgflag;
	data.pos=pos;
	data.vel=vel;
	data.Y=Y;
	data.Z=Z;

	directx->send_message((mp_msg *)&data,sizeof(struct mp_data));
}

mesh *ship::ray_intersect(vector& ro,vector& rd,vector& ip,float& dist,int &facenum,float rad)
{
	if (shieldmesh)
	{
		static float d1,d2;
		vector 
			ro_local=(ro-pos)*mat_t,
			rd_local=rd*mat_t;
		if (shieldmesh->bbox.ray_intersect(ro_local,rd_local,d1,d2))
		{
		facenum=shieldmesh->ray_intersect(ro_local,rd_local,ip,dist,rad);
		if (facenum>-1)
			{
			if (directx->mpmode!=FLYMP_CLIENT && (flag3&0x20000)==0 && flyengine->stepobj 
				&& (flyengine->stepobj->type==TYPE_LASER || flyengine->stepobj->type==TYPE_MISSILE) 
				&& dist<1.0f && ((gun_projectile *)flyengine->stepobj)->damage>0.0f)
					{
					shield-=((gun_projectile *)flyengine->stepobj)->damage;
					lasthittime=flyengine->cur_time;
					if (directx->mpmode==FLYMP_SERVER)
						{
						mp_data2 msg;
						msg.f=((gun_projectile *)flyengine->stepobj)->damage;
						msg.v=vel;
						msg.type=FLYMP_MSG_DAMAGE;
						msg.from=directx->players[player].dpid;
						directx->send_message((mp_msg *)&msg,sizeof(mp_data2));
						}
					}
			ip=ip*mat+pos;
			return shieldmesh;
			}
		}
	}
	return 0;
}
