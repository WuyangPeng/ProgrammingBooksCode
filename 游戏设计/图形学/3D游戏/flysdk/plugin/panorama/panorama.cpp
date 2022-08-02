#include "..\..\lib\Fly3D.h"
#include "panorama.h"

panorama_desc cd_panorama;

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
		return &cd_panorama;
	default: return 0;
	}
}

__declspec( dllexport )
int fly_message(int msg,int param,void *data)
{
	switch(msg)
	{
	case FLYM_DRAWSCENE:
		{
		panorama *pan=0;
		while( pan=(panorama *)flyengine->get_next_stock_object(pan,TYPE_PANORAMA))
			pan->draw();
		}
		return 1;
	}
	return 1;
}

void panorama::draw()
{
	if (flyengine->cam==0) return;

	vector min,max;
	min.vec(-size,-size,-size);
	max.vec(size,size,size);

	rotate(rot*(float)flyengine->cur_dt);

	glColor4f(color.x,color.y,color.z,color.w);
	glDisable(GL_FOG);
	glDisable(GL_DEPTH_TEST);
	glDepthMask(GL_FALSE);

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective( flyengine->camangle, flyengine->aspect, size/10, size*2);
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	glMultMatrixf((float *)&flyengine->cam->mat_t);
	glMultMatrixf((float *)&mat_t);

	tc->use(img[0]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f,0.0f);
	glVertex3f(min.x,min.y,max.z);
	glTexCoord2f(1.0f,0.0f);
	glVertex3f(min.x,max.y,max.z);
	glTexCoord2f(1.0f,1.0f);
	glVertex3f(max.x,max.y,max.z);
	glTexCoord2f(0.0f,1.0f);
	glVertex3f(max.x,min.y,max.z);
	glEnd();

	tc->use(img[1]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f,0.0f);
	glVertex3f(min.x,max.y,min.z);
	glTexCoord2f(0.0f,1.0f);
	glVertex3f(min.x,min.y,min.z);
	glTexCoord2f(1.0f,1.0f);
	glVertex3f(max.x,min.y,min.z);
	glTexCoord2f(1.0f,0.0f);
	glVertex3f(max.x,max.y,min.z);
	glEnd();

	tc->use(img[2]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f,1.0f);
	glVertex3f(min.x,max.y,min.z);
	glTexCoord2f(0.0f,0.0f);
	glVertex3f(min.x,max.y,max.z);
	glTexCoord2f(1.0f,0.0f);
	glVertex3f(min.x,min.y,max.z);
	glTexCoord2f(1.0f,1.0f);
	glVertex3f(min.x,min.y,min.z);
	glEnd();

	tc->use(img[3]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f,1.0f);
	glVertex3f(max.x,min.y,min.z);
	glTexCoord2f(0.0f,0.0f);
	glVertex3f(max.x,min.y,max.z);
	glTexCoord2f(1.0f,0.0f);
	glVertex3f(max.x,max.y,max.z);
	glTexCoord2f(1.0f,1.0f);
	glVertex3f(max.x,max.y,min.z);
	glEnd();

	tc->use(img[4]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f,1.0f);
	glVertex3f(max.x,max.y,min.z);
	glTexCoord2f(0.0f,0.0f);
	glVertex3f(max.x,max.y,max.z);
	glTexCoord2f(1.0f,0.0f);
	glVertex3f(min.x,max.y,max.z);
	glTexCoord2f(1.0f,1.0f);
	glVertex3f(min.x,max.y,min.z);
	glEnd();

	tc->use(img[5]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f,1.0f);
	glVertex3f(min.x,min.y,min.z);
	glTexCoord2f(0.0f,0.0f);
	glVertex3f(min.x,min.y,max.z);
	glTexCoord2f(1.0f,0.0f);
	glVertex3f(max.x,min.y,max.z);
	glTexCoord2f(1.0f,1.0f);
	glVertex3f(max.x,min.y,min.z);
	glEnd();

	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	if (flyengine->fog) glEnable(GL_FOG);
}

int panorama::get_custom_param_desc(int i,param_desc *pd)
{
	if (pd!=0)
	switch(i)
	{
		case 0:
			pd->type='f';
			pd->data=&size;
			strcpy(pd->name,"size");
			break;
		case 1:
			pd->type='p';
			pd->data=&img[0];
			strcpy(pd->name,"up");
			break;
		case 2:
			pd->type='p';
			pd->data=&img[1];
			strcpy(pd->name,"down");
			break;
		case 3:
			pd->type='p';
			pd->data=&img[2];
			strcpy(pd->name,"left");
			break;
		case 4:
			pd->type='p';
			pd->data=&img[3];
			strcpy(pd->name,"right");
			break;
		case 5:
			pd->type='p';
			pd->data=&img[4];
			strcpy(pd->name,"front");
			break;
		case 6:
			pd->type='p';
			pd->data=&img[5];
			strcpy(pd->name,"back");
			break;
		case 7:
			pd->type='c';
			pd->data=&color;
			strcpy(pd->name,"color");
			break;
		case 8:
			pd->type='f';
			pd->data=&color.w;
			strcpy(pd->name,"transp");
			break;
	}
	return 9;
}
