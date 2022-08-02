#include "..\..\lib\Fly3D.h"
#include "tutorial.h"

blink_light_desc cd_blink_light;
bounce_mesh_desc cd_bounce_mesh;

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
	return 2;
}

__declspec( dllexport )
class_desc *get_class_desc(int i)
{
	switch(i)
	{
	case 0:
		return &cd_blink_light;
	case 1:
		return &cd_bounce_mesh;
	default: return 0;
	}
}

__declspec( dllexport )
int fly_message(int msg,int param,void *data)
{
	switch(msg)
	{
	case FLYM_UPDATESCENE:
		// step/draw plugin layer
		break;
	}
	return 1;
}

int blink_light::step(int dt)
{
  // compute current radius 
  float r=illumradius*
          ((flyengine->cur_time%blinktime)/1000.0f);

  // illuminate around
  flyengine->send_bsp_message( 
         flyengine->bsp, pos, r, FLYOBJM_ILLUM, 0, &color);

  // return 0 as we have not moved (changed pos)
   return 0;
} 

void blink_light::draw()
{
	// TODO: draw using opengl
}

bsp_object *blink_light::clone()
{
	blink_light *tmp=new blink_light;
	*tmp=*this;
	tmp->source=this;
	return tmp;
}

int blink_light::get_custom_param_desc(int i,param_desc *pd)
{
	if (pd!=0)
	switch(i)
	{
	case 0:
		pd->type='c';
		pd->data=&color;
		strcpy(pd->name,"color");
		break;
	case 1:
		pd->type='f';
		pd->data=&illumradius;
		strcpy(pd->name,"illumradius");
		break;
	case 2:
		pd->type='i';
		pd->data=&blinktime;
		strcpy(pd->name,"blinktime");
		break;
	}
	return 3;
}

bsp_object *bounce_mesh::clone()
{
	bounce_mesh *tmp=new bounce_mesh;
	*tmp=*this;
	tmp->source=this;
	return tmp;
}

int bounce_mesh::get_custom_param_desc(int i,param_desc *pd)
{
	if (pd!=0)
	switch(i)
	{
	case 0:
		pd->type='3';
		pd->data=&objmesh;
		strcpy(pd->name,"objmesh");
		break;
	}
	return 1;
}


