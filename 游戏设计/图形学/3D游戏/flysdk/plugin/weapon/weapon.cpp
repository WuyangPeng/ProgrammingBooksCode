#include "..\..\lib\Fly3D.h"
#include "weapon.h"

gun_desc cd_gun;
hitmark_desc cd_hitmask;
mine_desc cd_mine;
laser_desc cd_laser;
missile_desc cd_missile;

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
	case 0:
		return &cd_gun;
	case 1:
		return &cd_hitmask;
	case 2:
		return &cd_mine;
	case 3:
		return &cd_laser;
	case 4:
		return &cd_missile;
	default: return 0;
	}
}

__declspec( dllexport )
int fly_message(int msg,int param,void *data)
{
	return 1;
}

