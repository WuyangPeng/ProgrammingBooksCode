#include "..\..\lib\Fly3D.h"
#include "gamelib.h"

dyn_sound_desc cd_sound;
ps_desc cd_ps;
explode_desc cd_explode;
exp_sphere_desc cd_exp_sphere;
shadow_desc cd_shadow;
fao_mesh_desc cd_fao_mesh;
subdiv_mesh_desc cd_subdiv_mesh;
cartoon_mesh_desc cd_cartoon_mesh;
dpblend_sphere_desc cd_dpblend_sphere;

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
	return 9;
}

__declspec( dllexport ) 
class_desc *get_class_desc(int i) 
{
	switch(i) 
	{
	case 0:
		return &cd_sound;
	case 1:
		return &cd_ps;
	case 2:
		return &cd_explode;
	case 3:
		return &cd_exp_sphere;
	case 4:
		return &cd_shadow;
	case 5:
		return &cd_fao_mesh;
	case 6:
		return &cd_subdiv_mesh;
	case 7:
		return &cd_cartoon_mesh;
	case 8:
		return &cd_dpblend_sphere;
	default: return 0;
	}
}

__declspec( dllexport )
int fly_message(int msg,int param,void *data)
{
	return 1;
}
