#include "..\..\lib\Fly3D.h"
#include "observer.h"

observer_desc cd_observer;

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
	return 1;
}

__declspec( dllexport )
class_desc *get_class_desc(int i)
{
	switch(i)
	{
	case 0:
		return &cd_observer;
	default: return 0;
	}
}

__declspec( dllexport )
int fly_message(int msg,int param,void *data)
{
	switch(msg)
	{
	case FLYM_UPDATESCENE:
		// step plugin (dt in param)
		break;
	case FLYM_DRAWSCENE:
		flyengine->set_camera(flyengine->cam);
		flyengine->draw_bsp();
		break;
	case FLYM_DRAWTEXT:
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
	case FLYM_INITSCENE:
		// draw 2d plugin
		break;
	case FLYM_CLOSESCENE:
		// draw 2d plugin
		break;
	}
	return 1;
}

void observer::init()
{
	if (flyengine->get_random_point(pos,10)==0)
		pos.null();
}

int observer::step(int dt)
{
	if (node==0)
		add_to_bsp();

	check_keys(dt);

	float len=vel.length();
	if (len<0.01f)
		vel.null();
	else
	{
		vel/=len;
		len-=dt*veldamp;
		if (len>maxvel)
			len=maxvel;
		if (len<0.0f)
			len=0.0f;
		vel*=len;
	}

	life=dt;
	return particle::step(dt);
}


void observer::check_keys(int dt)
{
	unsigned char *diks=directx->diks;

	static int lastmouse[2][2]={ { 0,0 },{ 0,0 } },lm=0;
	float mousedx=(directx->dims.lX+lastmouse[0][0]+lastmouse[1][0])/3.0f;
	float mousedy=(directx->dims.lY+lastmouse[0][1]+lastmouse[1][1])/3.0f;
	lastmouse[lm][0]=directx->dims.lX;
	lastmouse[lm][1]=directx->dims.lY;
	lm=!lm;
	
	if (diks[0x38])	// ALT key
		{
		if (diks[0xcb])		// left arrow
			vel-=X*(moveforce*dt);

		if (diks[0xcd])		// right arrow
			vel+=X*(moveforce*dt);

		if (diks[0xc8])		// up arrow
			vel+=Y*(moveforce*dt);

		if (diks[0xd0])		// down arrow
			vel-=Y*(moveforce*dt);

		if (diks[0x1f])		// S key
			vel-=Z*(moveforce*dt);

		if (diks[0x2d])		// X key
			vel+=Z*(moveforce*dt);
		}
	else
		{
		if (diks[0xc8])	// up arrow
			rotate(-dt*rotvel,X);
		
		if (diks[0xd0])	// down arrow
			rotate(dt*rotvel,X);

		if (diks[0xcb])	// left arrow
			rotate(dt*rotvel,Y);

		if (diks[0xcd])	// right arrow
			rotate(-dt*rotvel,Y);

		if (diks[0x10])	// Q key
			vel-=X*(moveforce*dt);

		if (diks[0x12])	// E key
			vel+=X*(moveforce*dt);

		if (diks[0x1f])	// S key
			vel-=Z*(moveforce*dt);

		if (diks[0x2d])	// X key
			vel+=Z*(moveforce*dt);
		}

	if (diks[0x1e])		// A key
		rotate(dt*rotvel,Z);
	if (diks[0x20])		// D key
		rotate(-dt*rotvel,Z);

	if (mousedx)	// mouse X
		rotate(-mousedx*mousevel,Y);

	if (mousedy)	// mouse Y
		rotate(mousedy*mousevel,X);
}

void observer::draw()
{
}

bsp_object *observer::clone()
{
	observer *tmp=new observer;
	*tmp=*this;
	tmp->source=this;
	return tmp;
}

int observer::get_custom_param_desc(int i,param_desc *pd)
{
	if (pd!=0)
	switch(i)
	{
	case 0:
		pd->type='f';
		pd->data=&rotvel;
		strcpy(pd->name,"rotvel");
		break;
	case 1:
		pd->type='f';
		pd->data=&mousevel;
		strcpy(pd->name,"mousevel");
		break;
	case 2:
		pd->type='f';
		pd->data=&moveforce;
		strcpy(pd->name,"moveforce");
		break;
	case 3:
		pd->type='f';
		pd->data=&maxvel;
		strcpy(pd->name,"maxvel");
		break;
	case 4:
		pd->type='f';
		pd->data=&veldamp;
		strcpy(pd->name,"veldamp");
		break;
	}
	return 5;
}


