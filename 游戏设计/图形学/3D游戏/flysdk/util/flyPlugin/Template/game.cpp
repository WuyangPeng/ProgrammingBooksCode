#include "Fly3D.h"
#include "$$root$$.h"

$$CLASS_DESC$$
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

$$NUM_CLASSES$$
$$GET_CLASS_DESC$$
$$FLY_MESSAGE$$
$$CLASSES_CPP$$
