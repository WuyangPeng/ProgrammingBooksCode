#include "..\..\lib\Fly3D.h"
#include "bezobj.h"

bezier_extrude_desc cd_bezier_extrude;
bezier_loft_desc cd_bezier_loft;
bezier_surface_desc cd_bezier_surface;

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
		return &cd_bezier_extrude;
	case 1:
		return &cd_bezier_loft;
	case 2:
		return &cd_bezier_surface;
	default: return 0;
	}
}

__declspec( dllexport )
int fly_message(int msg,int param,void *data)
{
	return 1;
}

