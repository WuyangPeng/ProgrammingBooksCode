#include "..\..\lib\Fly3D.h"
#include "..\gamelib\gamelib.h"
#include "car.h"

void mp_message(int from,mp_msg *msg);

camera_desc cd_camera;
car_desc cd_car;
sun_desc cd_sun;

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
	return 3;
}

__declspec( dllexport )
class_desc *get_class_desc(int i)
{
	switch(i)
	{
	case 0:
		return &cd_camera;
	case 1:
		return &cd_car;
	case 2:
		return &cd_sun;
	default: 
		return 0;
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
		// sets view
		flyengine->set_camera(flyengine->cam);
		
		// draws the sun 
		if (flyengine->cam->type==TYPE_CAMERA)
			if (((camera *)flyengine->cam)->s) 
				((camera *)flyengine->cam)->s->draw();

		// draws the scene
		flyengine->draw_bsp(1);

		// draw stencil shadow filter polygon
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
		if (directx->mpmode!=FLYMP_SERVER)
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
		}
		break;
	case FLYM_UPDATESCENE:
		{
		bsp_object *obj=0;
		while(obj=flyengine->get_next_active_object(obj,TYPE_CAR))
			if (obj==flyengine->player)
				((car *)obj)->check_keys(param);
			else if (((car *)obj)->player==0)
					((car *)obj)->check_robot_keys(param);
		}
		break;
	case FLYM_MPUPDATE:
		((car *)flyengine->player)->mp_send_pos(FLYMP_MSG_POS,0);
		return 0;
	case FLYM_MPMESSAGE:
		mp_message(param,(mp_msg *)data);
		return 0;
	}
	return 1;
}

bsp_object *car::clone()
{
	car *tmp=new car;
	*tmp=*this;
	tmp->source=this;
	return tmp;
}

int car::get_custom_param_desc(int i,param_desc *pd)
{
	if (pd!=0)
	switch(i)
	{
	case 0:
		pd->type='f';
		pd->data=&maxvel;
		strcpy(pd->name,"maxvel");
		break;
	case 1:
		pd->type='f';
		pd->data=&accel;
		strcpy(pd->name,"accel");
		break;
	case 2:
		pd->type='v';
		pd->data=&veldamp;
		strcpy(pd->name,"veldamp");
		break;
	case 3:
		pd->type='f';
		pd->data=&carwheelrot;
		strcpy(pd->name,"carwheelrot");
		break;
	case 4:
		pd->type='f';
		pd->data=&carheight;
		strcpy(pd->name,"carheight");
		break;
	case 5:
		pd->type='f';
		pd->data=&wheelmaxrot;
		strcpy(pd->name,"wheelmaxrot");
		break;
	case 6:
		pd->type='f';
		pd->data=&wheelrotvel;
		strcpy(pd->name,"wheelrotvel");
		break;
	case 7:
		pd->type='f';
		pd->data=&wheelrotdamp;
		strcpy(pd->name,"wheelrotdamp");
		break;
	case 8:
		pd->type='f';
		pd->data=&wheelradius;
		strcpy(pd->name,"wheelradius");
		break;
	case 9:
		pd->type='f';
		pd->data=&gravity;
		strcpy(pd->name,"gravity");
		break;
	case 10:
		pd->type='3';
		pd->data=&carmesh;
		strcpy(pd->name,"carmesh");
		break;
	case 11:
		pd->type='3';
		pd->data=&wheelmesh;
		strcpy(pd->name,"wheelmesh");
		break;
	case 12:
		pd->type='v';
		pd->data=&wheelposft;
		strcpy(pd->name,"wheelposft");
		break;
	case 13:
		pd->type='v';
		pd->data=&wheelposbk;
		strcpy(pd->name,"wheelposbk");
		break;
	case 14:
		pd->type='z';
		pd->data=&track;
		strcpy(pd->name,"track");
		break;
	case 15:
		pd->type=TYPE_SHADOW;
		pd->data=&carshadow;
		strcpy(pd->name,"carshadow");
		break;
	}
	return 16;
}

void car::init()
{
	static vector delta(0,0,0);
	if (source)
		{
		pos=source->pos+delta;
		delta.z+=1000;
		}
	align_z(vector(0,0,1));
	rotate(rot);

	if (track)
		totaltracktime=(int)(track->length()/maxvel);

	if (wheelmesh && wheelmesh->edges==0)
		wheelmesh->compute_normals(MESH_EDGES);
	if (carmesh && carmesh->edges==0)
		carmesh->compute_normals(MESH_EDGES);
}

void car::draw()
{
	static light_vertex lights;
	static vector viewpos,color,lightpos,v;

	sun *s=0;
	if (flyengine->cam->type==TYPE_CAMERA)
		s=((camera *)flyengine->cam)->s;

	if(carshadow && flyengine->stencil==0)
		{
		carshadow->reposition(this);
		carshadow->draw();
		}

	if (carmesh && wheelmesh)
	{
		lights.nlights=0;
		if (s)
			{
			lightpos=(s->pos-pos)*mat_t;
			color=s->color;
			lights.add_light(lightpos,color,0);
			}
		else 
			{
			lightpos.null();
			color.vec(1,1,1);
			}

		static mat4x4 m1,m2;
		m1.set_rotation(-wheelroll,vector(1,0,0));
		m2.set_rotation(-wheelrot,vector(0,1,0));
		m2=m2*m1;

		viewpos=(flyengine->cam->pos-pos)*mat_t;
		float f=viewpos.length()/flyengine->viewmaxdist;
		if (f<1.0f)
			f=(1.0f-f)*flyengine->cartoonwidth;
		else f=0.0f;

		glPushMatrix();
		glTranslatef(pos.x,pos.y,pos.z);
		glMultMatrixf((float *)&mat);
		carmesh->draw_cartoon(viewpos,color,lights,f);

		v=viewpos*m1;
		lights.pos[0]=lightpos*m1;
		
		glPushMatrix();
		glTranslatef(wheelposbk.x,wheelposbk.y,wheelposbk.z);
		glRotatef(wheelroll,1,0,0);
		wheelmesh->draw_cartoon(v,color,lights,f);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-wheelposbk.x,wheelposbk.y,wheelposbk.z);
		glRotatef(wheelroll,1,0,0);
		wheelmesh->draw_cartoon(v,color,lights,f);
		glPopMatrix();

		v=viewpos*m2;
		lights.pos[0]=lightpos*m2;

		glPushMatrix();
		glTranslatef(wheelposft.x,wheelposft.y,wheelposft.z);
		glRotatef(wheelrot,0,1,0);
		glRotatef(wheelroll,1,0,0);
		wheelmesh->draw_cartoon(v,color,lights,f);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-wheelposft.x,wheelposft.y,wheelposft.z);
		glRotatef(wheelrot,0,1,0);
		glRotatef(wheelroll,1,0,0);
		wheelmesh->draw_cartoon(v,color,lights,f);
		glPopMatrix();

		glPopMatrix();
	}
	if (flyengine->stencil && s)
		draw_stencil_shadow(lightpos);
}

void car::draw_stencil_shadow(vector& lightpos)
{
	// compute light direction
	vector lightdir=lightpos-pos;
	lightdir.normalize();
	lightdir*=flyengine->shadowdepth;

	// set current car pos and rotation
	glPushMatrix();
	glTranslatef(pos.x,pos.y,pos.z);
	glMultMatrixf((float *)&mat);

	// draw body shadow
	carmesh->draw_shadow_volume(lightdir);

	// draw back right wheel shadow
	glPushMatrix();
	glTranslatef(wheelposbk.x,wheelposbk.y,wheelposbk.z);
	wheelmesh->draw_shadow_volume(lightdir);
	glPopMatrix();

	// draw back left wheel shadow
	glPushMatrix();
	glTranslatef(-wheelposbk.x,wheelposbk.y,wheelposbk.z);
	wheelmesh->draw_shadow_volume(lightdir);
	glPopMatrix();

	// compute front wheel rotation 
	static mat4x4 m;
	m.set_rotation(-wheelrot,vector(0,1,0));
	lightdir=lightdir*m;

	// draw front right wheel shadow
	glPushMatrix();
	glTranslatef(wheelposft.x,wheelposft.y,wheelposft.z);
	glRotatef(wheelrot,0,1,0);
	wheelmesh->draw_shadow_volume(lightdir);
	glPopMatrix();

	// draw front left wheel shadow
	glPushMatrix();
	glTranslatef(-wheelposft.x,wheelposft.y,wheelposft.z);
	glRotatef(wheelrot,0,1,0);
	wheelmesh->draw_shadow_volume(lightdir);
	glPopMatrix();

	glPopMatrix();
}

int car::step(int dt)
{
	static vector p,v;

	// if no contact, apply gravity
	if (!contactobj)
		vel.z-=gravity*dt;

	// apply damping to the steering
	if (wheelrot>=0.0f)
		{
		wheelrot-=wheelrotdamp*dt;
		if (wheelrot<0.0f)
			wheelrot=0.0f;
		if (wheelrot>wheelmaxrot)
			wheelrot=wheelmaxrot;
		}
	else
		{
		wheelrot+=wheelrotdamp*dt;
		if (wheelrot>0.0f)
			wheelrot=0.0f;
		if (wheelrot<-wheelmaxrot)
			wheelrot=-wheelmaxrot;
		}

	float len=vel.length();
	// if moving
	if (len>0.01f)
	{
		// normalize velocity
		vel/=len;
		if (len>maxvel)
			len=maxvel;
		
		// project velocity in car local axes
		v.x=vec_dot(vel,X)*len;
		v.y=vec_dot(vel,Y)*len;
		v.z=vec_dot(vel,Z)*len;

		// apply damping to individual axes
		// X for sliding and Z for breaking
		for( int i=0;i<3;i++ )
			if (v[i]>=0.0f)
				{
				v[i]-=veldamp[i]*dt;
				if (v[i]<0.0) v[i]=0.0f;
				}
			else
				{
				v[i]+=veldamp[i]*dt;
				if (v[i]>0.0) v[i]=0.0f;
				}
		
		// restore velocity vector from axes components
		vel=X*v.x + Y*v.y + Z*v.z;

		// compute wheel roll based on forward motion and wheel radius
		wheelroll+=v.z*dt/(M_2Pi*wheelradius)*360.0f;
		wheelroll=(float)fmod(wheelroll,360);
		
		// move by applying the car velocity
		p=pos+vel*(float)dt;
		flyengine->excludecollision=this;
		if (flyengine->collision_bsp(flyengine->bsp,pos,p))
		{
			contactobj=flyengine->hitmesh;
			contactfacenum=flyengine->hitface;
		}
		else contactobj=0;
		flyengine->excludecollision=0;
		if (contactobj)
			pos=flyengine->hitip+contactobj->faces[contactfacenum]->normal*carheight;
		else pos=p;
	} 
	else v.null();

	if (contactobj==0)
	{
		// ray intesect collision detection to check for ground contact
		p=pos-Y*carheight;
		flyengine->excludecollision=this;
		if (flyengine->collision_bsp(flyengine->bsp,pos,p))
		{
			contactobj=flyengine->hitmesh;
			contactfacenum=flyengine->hitface;
		} 
		else contactobj=0;
		flyengine->excludecollision=0;
	}
	
	// if in contact
	if (contactobj)
	{
		// position the car at a fixed distance from the ground
		pos=flyengine->hitip+Y*(carheight-0.1f);
		// align car with ground if no collision with wall
	 	if (contactobj->localfaces==0 && contactobj->faces[contactfacenum]->normal.z<0.5f)
		{
			rotate(Y,vector(0,0,1));
			v.z=-v.z;
			v.x=-v.x;
		}
		else rotate(Y,contactobj->faces[contactfacenum]->normal,0.1f*dt);
		// recompute velocity
		vel=X*v.x + Y*v.y + Z*v.z;
		// rotate car body based on forward motion and steering angle if in contact
		rotate(-wheelrot*v.z*dt/carwheelrot,Y);
	}

	return 1;
}

void car::check_keys(int dt)
{
	unsigned char *diks=directx->diks;
	
	if (diks[0xcb])	// left arrow
		wheelrot+=wheelrotvel*dt;

	if (diks[0xcd])	// right arrow
		wheelrot-=wheelrotvel*dt;

	if (contactobj)
	{
	if (diks[0xc8])	// up arrow
		vel-=Z*(accel*dt);

	if (diks[0xd0])	// down arrow
		vel+=Z*(accel*dt);
	}
}

void car::check_robot_keys(int dt)
{
	if (track==0)
		return;

	vector P,T,V;
	float len,dot;

	// get position of rabbit
	curtracktime=(curtracktime+dt)%totaltracktime;
	track->evaluate((float)curtracktime/totaltracktime,&P.x);
	P.z+=track->pivot.z-50;
	T=P-pos;
	len=T.length();
	T/=len;
	dot=vec_dot(T,Z);
	if (dot<0.996)   // 0.996=cosd(8)
		{
		V.cross(T,Z);
		if (vec_dot(V,Y)>0)
			wheelrot+=wheelrotvel*dt; // rotate right
		else
			wheelrot-=wheelrotvel*dt; // rotate left
		}

	if (contactobj)
	if (len>500)
		vel-=Z*(accel*dt); // move forward
}

void car::mp_send_pos(int msgtype,int msgflag)
{
	static struct mp_data data;
	
	data.type=msgtype;
	data.dpid=directx->players[player].dpid;
	data.flag=msgflag;
	data.pos=pos;
	data.vel=vel;
	data.Y=Y;
	data.Z=Z;
	data.wheelrot=wheelrot;

	directx->send_message((mp_msg *)&data,sizeof(struct mp_data));
}

void mp_message(int from,mp_msg *msg)
{	
	switch( msg->type )
		{
		case FLYMP_MSG_POS:
			{
				mp_data *data=(mp_data *)&msg->type;
				car *c=(car *)directx->players[from].data;
				if (from>0)
					{
					c->remove_from_bsp();
					c->pos=data->pos;
					c->vel=data->vel;
					c->Y=data->Y;
					c->Z=data->Z;
					c->X.cross(c->Y,c->Z);
					c->wheelrot=data->wheelrot;
					c->update_mat();
					c->add_to_bsp();
					}
			}
			break;
		case FLYMP_MSG_JOIN:
			{
				player_data *data=(player_data *)&msg->type;
				car *c=(car *)flyengine->player->clone();
				c->player=directx->add_player(data->name,data->dpid,c);
				flyengine->set_status_msg("%s HAS JOINED THE GAME",data->name);
				flyengine->activate(c,(directx->mpmode==FLYMP_SERVER));
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
						((car *)directx->players[i].data)->player=i;
					if (obj) obj->life=-1;
					}
			}
			break;
		}
}

bsp_object *camera::clone()
{
	camera *tmp=new camera;
	*tmp=*this;
	tmp->source=this;
	return tmp;
}

int camera::get_custom_param_desc(int i,param_desc *pd)
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
		pd->data=&dist;
		strcpy(pd->name,"dist");
		break;
	case 2:
		pd->type='d';
		pd->data=&target;
		strcpy(pd->name,"target");
		break;
	case 3:
		pd->type='f';
		pd->data=&maxvel;
		strcpy(pd->name,"maxvel");
		break;
	case 4:
		pd->type=TYPE_SUN;
		pd->data=&s;
		strcpy(pd->name,"sun");
		break;
	}
	return 5;
}

void camera::init()
{
	if (target)
	{
	lp=target->pos;
	pos=target->source->pos;
	}
}

int camera::step(int dt)
{
	vector dir,p;

	if (target)
		{
		dir.x=target->pos.x-pos.x;
		dir.y=target->pos.y-pos.y;
		dir.z=0;
		dir.normalize();

		p.x=target->pos.x-dir.x*dist;
		p.y=target->pos.y-dir.y*dist;
		p.z=target->pos.z+height;

		float dist;
		dir=p-pos;
		dist=dir.length();
		if (dist>0.01f)
			{
			dir/=dist;
			if (dist>maxvel*dt)
				dist=maxvel*dt;
			pos+=dir*dist;		
			}
		
		if (flyengine->collision_bsp(flyengine->bsp,pos,vector(pos.x,pos.y,pos.z-flyengine->viewmindist*2)))
			pos.vec(flyengine->hitip.x,flyengine->hitip.y,flyengine->hitip.z+flyengine->viewmindist*2);

		dir=target->pos-lp;
		dist=dir.length();
		if (dist>0.01f)
			{
			dir/=dist;
			if (dist>maxvel*dt)
				dist=maxvel*dt;
			lp+=dir*dist;		
			}

		dir=pos-lp;
		dir.normalize();
		align_z(dir);
		}

	return 1;
}

bsp_object *sun::clone()
{
	sun *tmp=new sun;
	*tmp=*this;
	tmp->source=this;
	return tmp;
}

int sun::get_custom_param_desc(int i,param_desc *pd)
{
	if (pd!=0)
	switch(i)
	{
	case 0:
		pd->type='3';
		pd->data=&objmesh;
		strcpy(pd->name,"objmesh");
		break;
	case 1:
		pd->type='c';
		pd->data=&color;
		strcpy(pd->name,"color");
		break;
	case 2:
		pd->type='f';
		pd->data=&color.w;
		strcpy(pd->name,"transp");
		break;
	case 3:
		pd->type='p';
		pd->data=&halopic;
		strcpy(pd->name,"halopic");
		break;
	case 4:
		pd->type='f';
		pd->data=&halosize;
		strcpy(pd->name,"halosize");
		break;
	}
	return 5;
}

void sun::init()
{
	if (objmesh)
		pos=objmesh->pivotpos;
}

void sun::draw()
{
	static vector x,y;

	int d=(int)(pos-flyengine->cam->pos).length()/10*10;
	glMatrixMode( GL_PROJECTION );
	glPushMatrix();
	glLoadIdentity();
	gluPerspective( flyengine->camangle, flyengine->aspect, d/2,2*d);
	glMatrixMode( GL_MODELVIEW );

	glDisable(GL_FOG);
	glDisable(GL_DEPTH_TEST);

	glPushMatrix();
	glTranslatef(pos.x,pos.y,pos.z);
	if (objmesh)
		objmesh->draw();

	x=flyengine->cam->X*halosize;
	y=flyengine->cam->Y*halosize;

	glBlendFunc(GL_ONE,GL_ONE);
	glDepthMask(GL_FALSE);
	
	glColor3f(color.x*color.w,color.y*color.w,color.z*color.w);

	tc->use(halopic);

	glBegin(GL_QUADS);

	glTexCoord2f(1,0);
	glVertex3f(x.x-y.x, x.y-y.y, x.z-y.z);

	glTexCoord2f(1,1);
	glVertex3f(x.x+y.x, x.y+y.y, x.z+y.z);

	glTexCoord2f(0,1);
	glVertex3f(y.x-x.x, y.y-x.y, y.z-x.z);

	glTexCoord2f(0,0);
	glVertex3f(-x.x-y.x, -x.y-y.y, -x.z-y.z);

	glEnd();
	glPopMatrix();

	glDepthMask(GL_TRUE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	if (flyengine->fog) glEnable(GL_FOG);

	glMatrixMode( GL_PROJECTION );
	glPopMatrix();
	glMatrixMode( GL_MODELVIEW );
}
