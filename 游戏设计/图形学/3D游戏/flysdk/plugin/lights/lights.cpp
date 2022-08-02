#include "../../lib/Fly3D.h"
#include "lights.h"

light_desc cd_light;
spot_light_desc cd_spot_light;
sprite_light_desc cd_sprite_light;
mesh_light_desc cd_mesh_light;

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
	return 4;
}

__declspec( dllexport )
class_desc *get_class_desc(int i)
{
	switch(i)
	{
	case 0:
		return &cd_light;
	case 1:
		return &cd_spot_light;
	case 2:
		return &cd_sprite_light;
	case 3:
		return &cd_mesh_light;
	default: return 0;
	}
}

__declspec( dllexport )
int fly_message(int msg,int param,void *data)
{
	return 1;
}






