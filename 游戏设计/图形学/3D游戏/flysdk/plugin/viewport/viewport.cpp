#include "..\..\lib\Fly3D.h"
#include "viewport.h"

viewport_desc cd_viewport;

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
		return &cd_viewport;
	default: return 0;
	}
}

void draw()
{
	int i,nvp=0;
	viewport *vp[16],*v=0;
	while(v=(viewport *)flyengine->get_next_stock_object(v,TYPE_VIEWPORT))
		vp[nvp++]=v;

	if (nvp==0) return;

	bsp_object *d=flyengine->cam;

	for( i=0;i<nvp;i++ )
		if (vp[i]->target && vp[i]->target->node && (vp[i]->on&0xf))
		{
		flyengine->cur_frame++;
		local_system ls=*((local_system *)vp[i]->target);

		int x=(int)(vp[i]->xf*screen_sx), 
			y=(int)(vp[i]->yf*screen_sy),
			wx=(int)(vp[i]->sxf*screen_sx),
			wy=(int)(vp[i]->syf*screen_sy);
		glViewport(x,y,wx,wy);
		glScissor(x,y,wx,wy);
		glEnable(GL_SCISSOR_TEST);
		glClear( GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT );
		glDisable(GL_SCISSOR_TEST);

		if (vp[i]->dirflag) vp[i]->target->rotate(180,vp[i]->target->Y);
		flyengine->set_camera(vp[i]->target);
		flyengine->draw_bsp();

		*((local_system *)vp[i]->target)=ls;
		}

	glViewport(0, 0, screen_sx, screen_sy);

	flyengine->set_camera(d);
	for( i=0;i<nvp;i++ )
		if (directx->diks[vp[i]->key]&0x80)
			if ((vp[i]->on&0xf0)==0)
				vp[i]->on=(int)(!vp[i]->on)|0xf0;
			else ;
		else if (vp[i]->on&0xf0) 
				vp[i]->on=(vp[i]->on&0xf);
}

__declspec( dllexport )
int fly_message(int msg,int param,void *data)
{
	switch(msg)
	{
	case FLYM_DRAWSCENE:
		if (directx->mpmode!=FLYMP_SERVER)
			draw();
		break;
	}
	return 1;
}

int viewport::get_custom_param_desc(int i,param_desc *pd)
{
	if (pd==0)
		return 7;
	else 
	switch(i)
	{
		case 0:
			pd->type='f';
			pd->data=&xf;
			strcpy(pd->name,"xf");
			break;
		case 1:
			pd->type='f';
			pd->data=&yf;
			strcpy(pd->name,"yf");
			break;
		case 2:
			pd->type='f';
			pd->data=&sxf;
			strcpy(pd->name,"sxf");
			break;
		case 3:
			pd->type='f';
			pd->data=&syf;
			strcpy(pd->name,"syf");
			break;
		case 4:
			pd->type='i';
			pd->data=&dirflag;
			strcpy(pd->name,"dirflag");
			break;
		case 5:
			pd->type='d';
			pd->data=&target;
			strcpy(pd->name,"target");
			break;
		case 6: 
			pd->type='i';
			pd->data=&key;
			strcpy(pd->name,"key");
			break;
	}
	return 0;
}
