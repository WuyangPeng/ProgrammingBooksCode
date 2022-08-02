#include "../Fly3D.h"

FLY_API render *rend=0;

FLY_API PIXELFORMATDESCRIPTOR rendermodes[256];
FLY_API int rendermodesindx[256];
FLY_API DEVMODE videomodes[256];
FLY_API int numvideomodes=0;
FLY_API int numrendermodes=0;
FLY_API int selvideomode=0;
FLY_API int selrendermode=0;

FLY_API int ntextureunits=1;
FLY_API int nhwlights=4;
FLY_API int nregcomb=0;
FLY_API int screen_sx=0,screen_sy=0;
FLY_API int fullscreen=0;
FLY_API int colorbits=0;
FLY_API int stencilbits=0;
FLY_API int depthbits=0;
FLY_API int accumbits=0;
FLY_API int alphabits=0;
FLY_API float brightness=1.0f;
FLY_API RECT winrect;

void FlyGetProfile(LPTSTR section, LPTSTR key, LPBYTE lpData, DWORD cbData)
{
	HKEY key1,key2,key3,key4;

	if (ERROR_SUCCESS==RegOpenKeyEx(HKEY_CURRENT_USER,"Software",0,KEY_READ,&key1))
	{
		if (ERROR_SUCCESS==RegOpenKeyEx(key1,"Paralelo",0,KEY_READ,&key2))
		{
			if (ERROR_SUCCESS==RegOpenKeyEx(key2,"Fly3D",0,KEY_READ,&key3))
			{
				if (ERROR_SUCCESS==RegOpenKeyEx(key3,section,0,KEY_READ,&key4))
				{
					RegQueryValueEx(key4, key, 0, 0, lpData, &cbData);
					RegCloseKey(key4);
				}
				RegCloseKey(key3);
			}
			RegCloseKey(key2);
		}
		RegCloseKey(key1);
	}
}

FLY_API void init_render(int type)
{
	free_render();
	
	FlyGetProfile("Settings","videomode", (unsigned char *)&selvideomode, sizeof(int));
	FlyGetProfile("Settings","rendermode", (unsigned char *)&selrendermode, sizeof(int));
	FlyGetProfile("Settings","brightness", (unsigned char *)&brightness, sizeof(float));

	switch(type)
	{
	case FLY_RENDER_OPENGL:
		rend=new renderGL();
		break;
	}

	if (rend)
	{
		rend->CreateView();
		rend->InitView();
	}
}

FLY_API void free_render()
{
	if (fullscreen)
		ChangeDisplaySettings(NULL,CDS_FULLSCREEN);

	if (rend)
	{
		rend->DeleteView();
		delete rend;
		rend=0;
	}

	numvideomodes=0;
	selvideomode=0;
	numrendermodes=0;
	selrendermode=0;
}
