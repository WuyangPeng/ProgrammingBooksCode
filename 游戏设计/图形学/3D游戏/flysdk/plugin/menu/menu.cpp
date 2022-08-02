#include "..\..\lib\Fly3D.h"
#include "..\gamelib\gamelib.h"
#include "menu.h"

menugroup_desc cd_menugroup;
menuitem_desc cd_menuitem;
menucamera_desc cd_menucamera;

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
		return &cd_menugroup;
	case 1:
		return &cd_menuitem;
	case 2:
		return &cd_menucamera;
	default: return 0;
	}
}

__declspec( dllexport )
int fly_message(int msg,int param,void *data)
{
	switch(msg)
	{
	case FLYM_DRAWSCENE:
		flyengine->set_camera(flyengine->cam);
		flyengine->draw_bsp();
		directx->set_listener(
			&flyengine->cam->pos.x,0,
			&flyengine->cam->Y.x,&flyengine->cam->Z.x);
		break;
	}
	return 1;
}

void menugroup::draw()
{
	int i;
	for( i=0;i<nitem;i++ )
		if (item[i])
		{
			if (i==selitem)
				item[i]->color.w=1.0f;
			else item[i]->color.w=0.4f;
			glPushMatrix();
			glTranslatef(pos.x,pos.y,pos.z+height/2-height*i/(nitem-1));
			glMultMatrixf((float *)&mat);
			item[i]->draw();
			glPopMatrix();
		}
}

bsp_object *menugroup::clone()
{
	menugroup *tmp=new menugroup;
	*tmp=*this;
	tmp->source=this;
	return tmp;
}

int menugroup::get_custom_param_desc(int i,param_desc *pd)
{
	if (pd!=0)
	switch(i)
	{
	case 0:
		pd->type='i';
		pd->data=&nitem;
		strcpy(pd->name,"nitem");
		break;
	case 1:
		pd->type=TYPE_MENUITEM;
		pd->data=&item[0];
		strcpy(pd->name,"item1");
		break;
	case 2:
		pd->type=TYPE_MENUITEM;
		pd->data=&item[1];
		strcpy(pd->name,"item2");
		break;
	case 3:
		pd->type=TYPE_MENUITEM;
		pd->data=&item[2];
		strcpy(pd->name,"item3");
		break;
	case 4:
		pd->type=TYPE_MENUITEM;
		pd->data=&item[3];
		strcpy(pd->name,"item4");
		break;
	case 5:
		pd->type=TYPE_MENUITEM;
		pd->data=&item[4];
		strcpy(pd->name,"item5");
		break;
	case 6:
		pd->type=TYPE_MENUITEM;
		pd->data=&item[5];
		strcpy(pd->name,"item6");
		break;
	case 7:
		pd->type=TYPE_MENUITEM;
		pd->data=&item[6];
		strcpy(pd->name,"item7");
		break;
	case 8:
		pd->type=TYPE_MENUITEM;
		pd->data=&item[7];
		strcpy(pd->name,"item8");
		break;
	case 9:
		pd->type='f';
		pd->data=&height;
		strcpy(pd->name,"height");
		break;
	}
	return 10;
}

void menuitem::draw()
{
	static vector x,y,c,v;

	glDepthMask(GL_FALSE);
	glBlendFunc(GL_ONE, GL_ONE);
	glDisable(GL_FOG);

	tc->use(texture);

	glColor3f(color.w,color.w,color.w);
	
	x=flyengine->cam->X*width;
	y=flyengine->cam->Y*height;

	glBegin(GL_QUADS);

	v.x=pos.x+x.x-y.x;
	v.y=pos.y+x.y-y.y;
	v.z=pos.z+x.z-y.z;
	glTexCoord2f(1,1);
	glVertex3fv((float *)&v);

	v.x=pos.x+x.x+y.x;
	v.y=pos.y+x.y+y.y;
	v.z=pos.z+x.z+y.z;
	glTexCoord2f(1,0);
	glVertex3fv((float *)&v);

	v.x=pos.x-x.x+y.x;
	v.y=pos.y-x.y+y.y;
	v.z=pos.z-x.z+y.z;
	glTexCoord2f(0,0);
	glVertex3fv((float *)&v);

	v.x=pos.x-x.x-y.x;
	v.y=pos.y-x.y-y.y;
	v.z=pos.z-x.z-y.z;
	glTexCoord2f(0,1);
	glVertex3fv((float *)&v);

	glEnd();

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	if (flyengine->fog) glEnable(GL_FOG);
	glDepthMask(GL_TRUE);
}

bsp_object *menuitem::clone()
{
	menuitem *tmp=new menuitem;
	*tmp=*this;
	tmp->source=this;
	return tmp;
}

int menuitem::get_custom_param_desc(int i,param_desc *pd)
{
	if (pd!=0)
	switch(i)
	{
	case 0:
		pd->type='f';
		pd->data=&width;
		strcpy(pd->name,"width");
		break;
	case 1:
		pd->type='f';
		pd->data=&height;
		strcpy(pd->name,"height");
		break;
	case 2:
		pd->type='p';
		pd->data=&texture;
		strcpy(pd->name,"texture");
		break;
	case 3:
		pd->type='c';
		pd->data=&color;
		strcpy(pd->name,"color");
		break;
	case 4:
		pd->type='f';
		pd->data=&color.w;
		strcpy(pd->name,"transp");
		break;
	case 5:
		pd->type='s';
		pd->data=command;
		strcpy(pd->name,"command");
		break;
	}
	return 6;
}

int menucamera::step(int dt)
{
	if (target)
	{
	menugroup *m=(menugroup *)target;

	if (l)
		{
		l->pos=m->pos;
		l->color=m->item[m->selitem]->color;
		l->pos.z+=m->height/2-m->height*m->selitem/(m->nitem-1);
		l->step(dt);
		}

	vector dir;
	dir=pos-target->pos;
	dir.normalize();
	float dot=vec_dot(dir,Z);
	float ang=(float)acos(dot)*180.0f/M_Pi;
	if (ang<1.0f)
		align_z(dir);
	else
		{
		if (ang>179.0f)
			rotate(dt*rotvel,Y);
		else
			{
			if (ang>dt*rotvel)
				ang=dt*rotvel;
			if (ang>0)
				{
				dir.negate();
				rotate(dir,Z,ang);
				}
			}
		}

	if (directx->diks[0xc8]&0x80) // up
		if ((keystatus&0x100)==0 && m->selitem>0)
		{
		m->selitem--;
		keystatus|=0x100;
		if (sndchangesel)
			sndchangesel->add_sound_clone(&m->pos,0);
		}
		else ;
	else if (keystatus&0x100)
			keystatus&=0x011;

	if (directx->diks[0xd0]&0x80) // down
		if ((keystatus&0x010)==0 && m->selitem<m->nitem-1)
		{
		m->selitem++;
		keystatus|=0x010;
		if (sndchangesel)
			sndchangesel->add_sound_clone(&m->pos,0);
		}
		else ;
	else if (keystatus&0x010)
			keystatus&=0x101;

	if (directx->diks[0x1c]&0x80) // enter
		if ((keystatus&0x001)==0 && m->selitem<m->nitem)
		{
		strcpy(flyengine->console_command,m->item[m->selitem]->command);
		keystatus|=0x001;
		if (sndselect)
			sndselect->add_sound_clone(&m->pos,0);
		}
		else ;
	else if (keystatus&0x001)
			keystatus&=0x110;
	}
		
	return 1;
}

bsp_object *menucamera::clone()
{
	menucamera *tmp=new menucamera;
	*tmp=*this;
	tmp->source=this;
	return tmp;
}

int menucamera::get_custom_param_desc(int i,param_desc *pd)
{
	if (pd!=0)
	switch(i)
	{
	case 0:
		pd->type='d';
		pd->data=&target;
		strcpy(pd->name,"target");
		break;
	case 1:
		pd->type='f';
		pd->data=&rotvel;
		strcpy(pd->name,"rotvel");
		break;
	case 2:
		pd->type=TYPE_LIGHT;
		pd->data=&l;
		strcpy(pd->name,"light");
		break;
	case 3:
		pd->type=TYPE_SOUND;
		pd->data=&sndselect;
		strcpy(pd->name,"sndselect");
		break;
	case 4:
		pd->type=TYPE_SOUND;
		pd->data=&sndchangesel;
		strcpy(pd->name,"sndchangesel");
		break;
	}
	return 5;
}
