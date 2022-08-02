#include "../../lib/Fly3D.h"
#include "volfog.h"

fogsphere_desc cd_fogsphere;
fogbox_desc cd_fogbox;

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
		return &cd_fogsphere;
	case 1:
		return &cd_fogbox;
	default: return 0;
	}
}

__declspec( dllexport )
int fly_message(int msg,int param,void *data)
{
	return 1;
}

void apply_fog_sphere(void *data,bsp_object *e)
{
	fogsphere *fs=(fogsphere *)data;
	if (e->type==TYPE_STATIC_MESH)
	{
		static_mesh *so=(static_mesh *)e;
		if (so->objmesh->lastdraw<flyengine->cur_frame_base)
			return;
		int i;
		for( i=0;i<so->objmesh->nf;i++ )
			if(so->objmesh->faces[i]->lm!=-1)
			{
			light_map *fm=flyengine->fm[so->objmesh->faces[i]->lm];
			if (fm->lastupdate!=flyengine->cur_step)
				{
				fs->fog_map(fm);
				fm->lastupdate=flyengine->cur_step;
				}
			}
	}
}

void fogsphere::fog_map(light_map *fm)
{
	vector point;
	int i,j;
	unsigned char *uc,factor;
	float fi=1.0f/fm->sizex,fj=1.0f/fm->sizey,fy=fj*0.5f;
	vector v1=fm->d0+fm->d1*(fi*0.5f),v2=fm->d1*fi;
	
	for( j=0;j<fm->sizey;j++,fy+=fj )
	{
	uc=&fm->bmp[j*fm->bytesx];
	point.x = v1.x + fm->d2.x*fy;
	point.y = v1.y + fm->d2.y*fy;
	point.z = v1.z + fm->d2.z*fy;
	for( i=0;i<fm->sizex;i++,point+=v2 )
		{
		if (fogmode==0)
			if (fog_intersect(point,factor))
				{
				*(uc++)=(unsigned char)(fogcolor.x*255.0f);
				*(uc++)=(unsigned char)(fogcolor.y*255.0f);
				*(uc++)=(unsigned char)(fogcolor.z*255.0f);
				*(uc++)=factor;
				}
			else uc+=4;
		else if (fogmode==1)
			{
			vector d=point-pos;
			if (d.length()<fogradius)
				{
				*(uc++)=(unsigned char)(fogcolor.x*255.0f);
				*(uc++)=(unsigned char)(fogcolor.y*255.0f);
				*(uc++)=(unsigned char)(fogcolor.z*255.0f);
				*(uc++)=127;
				}
			else uc+=4;
			}
		else 
			{
			*(uc++)=(unsigned char)(fogcolor.x*255.0f);
			*(uc++)=(unsigned char)(fogcolor.y*255.0f);
			*(uc++)=(unsigned char)(fogcolor.z*255.0f);
			*(uc++)=127;
			}
		}
	}
}

int fogsphere::fog_intersect(vector& point,unsigned char& factor)
{
	float a,b,c,d,z,x1,x2;
	
	vector ro=flyengine->cam->pos-pos;
	vector rd=point-flyengine->cam->pos;
	
	d=rd.length();
	rd/=d;

    a=rd.x*rd.x + rd.y*rd.y + rd.z*rd.z;
    b=2.0f*(ro.x*rd.x + ro.y*rd.y + ro.z*rd.z);
    c=ro.x*ro.x + ro.y*ro.y + ro.z*ro.z - fogradius*fogradius;

	a*=2.0f;
    z=b*b-2.0f*a*c;
    if (z<=0.0f)
       return 0;
    z=(float)sqrt(z);
    x1=(-b+z)/a;
    x2=(-b-z)/a;

	if (x1>d) x1=d;
	else if (x1<0.0f) x1=0.0f;
	if (x2>d) x2=d;
	else if (x2<0.0f) x2=0.0f;

	z=(float)fabs(x2-x1)*254.0f/fogdepth;
	if (z>255.0f) 
		factor=255;
	else factor=(unsigned char)z;

	return 1;
}

int fogsphere::step(int dt)
{
	if (directx->mpmode!=FLYMP_SERVER && flyengine->cam)
		flyengine->apply_bsp(flyengine->bsp,pos,fogrange,this,apply_fog_sphere);
	return 0;
}

void apply_fog_box(void *data,bsp_object *e)
{
	fogbox *fb=(fogbox *)data;
	if (e->type==TYPE_STATIC_MESH)
	{
		static_mesh *so=(static_mesh *)e;
		if (so->objmesh->lastdraw<flyengine->cur_frame_base)
			return;
		int i;
		for( i=0;i<so->objmesh->nf;i++ )
			if(so->objmesh->faces[i]->lm!=-1)
			{
			light_map *fm=flyengine->fm[so->objmesh->faces[i]->lm];
			if (fm->lastupdate!=flyengine->cur_step)
				{
				fb->fog_map(fm);
				fm->lastupdate=flyengine->cur_step;
				}
			}
	}
}

void fogbox::fog_map(light_map *fm)
{
	vector point;
	int i,j;
	unsigned char *uc,factor;
	float fi=1.0f/fm->sizex,fj=1.0f/fm->sizey,fy=fj*0.5f;
	vector v1=fm->d0+fm->d1*(fi*0.5f),v2=fm->d1*fi;
	
	for( j=0;j<fm->sizey;j++,fy+=fj )
	{
	uc=&fm->bmp[j*fm->bytesx];
	point.x = v1.x + fm->d2.x*fy;
	point.y = v1.y + fm->d2.y*fy;
	point.z = v1.z + fm->d2.z*fy;
	for( i=0;i<fm->sizex;i++,point+=v2 )
		{
		if (fogmode==0)
			if (fog_intersect(point,factor))
				{
				*(uc++)=(unsigned char)(fogcolor.x*255.0f);
				*(uc++)=(unsigned char)(fogcolor.y*255.0f);
				*(uc++)=(unsigned char)(fogcolor.z*255.0f);
				*(uc++)=factor;
				}
			else uc+=4;
		else if (fogmode==1)
			{
			vector d=point-pos;
			if (fabs(d.x)<fogsizex &&
				fabs(d.y)<fogsizey &&
				fabs(d.z)<fogsizez )
				{
				*(uc++)=(unsigned char)(fogcolor.x*255.0f);
				*(uc++)=(unsigned char)(fogcolor.y*255.0f);
				*(uc++)=(unsigned char)(fogcolor.z*255.0f);
				*(uc++)=127;
				}
			else uc+=4;
			}
		else 
			{
			*(uc++)=(unsigned char)(fogcolor.x*255.0f);
			*(uc++)=(unsigned char)(fogcolor.y*255.0f);
			*(uc++)=(unsigned char)(fogcolor.z*255.0f);
			*(uc++)=127;
			}
		}
	}
}

int fogbox::fog_intersect(vector& point,unsigned char& factor)
{
	vector rd=point-flyengine->cam->pos;
	float d=rd.length();
	rd/=d;
	float x1,x2;

	if (bb.ray_intersect(flyengine->cam->pos,rd,x1,x2)==0)
		return 0;

	if (x1>d) x1=d;
	else if (x1<0.0f) x1=0.0f;
	if (x2>d) x2=d;
	else if (x2<0.0f) x2=0.0f;

	d=(float)fabs(x2-x1)*255.0f/fogdepth;
	if (d>255.0f) 
		factor=255;
	else factor=(unsigned char)d;
/*
	static vector p1,p2,v;
	p1=flyengine->cam->pos+rd*x1,
	p2=flyengine->cam->pos+rd*x2;
	v=p2-p1;
	factor=
		(float)sqrt(v.x*v.x+v.y*v.y) *
		(bb.max.z-(p1.z+p2.z)/2.0f) /
		(fogsizez * fogdepth) * 510.0f; 
	if (factor>255.0f) factor=255.0f;
*/
	return 1;
}

int fogbox::step(int dt)
{
	if (directx->mpmode!=FLYMP_SERVER && flyengine->cam)
	{
		bb.min=bb.max=pos;
		bb.min.x-=fogsizex;
		bb.min.y-=fogsizey;
		bb.min.z-=fogsizez;
		bb.max.x+=fogsizex;
		bb.max.y+=fogsizey;
		bb.max.z+=fogsizez;
		bbdiag=(bb.max-bb.min).length();
		flyengine->apply_bsp(flyengine->bsp,pos,fogrange,this,apply_fog_box);
	}
	return 0;
}

bsp_object *fogsphere::clone()
{
	fogsphere *tmp=new fogsphere;
	*tmp=*this;
	tmp->source=this;
	return tmp;
}

int fogsphere::get_custom_param_desc(int i,param_desc *pd)
{
	if (pd!=0)
	switch(i)
	{
	case 0:
		pd->type='f';
		pd->data=&fogradius;
		strcpy(pd->name,"fogradius");
		break;
	case 1:
		pd->type='f';
		pd->data=&fogrange;
		strcpy(pd->name,"fogrange");
		break;
	case 2:
		pd->type='f';
		pd->data=&fogdepth;
		strcpy(pd->name,"fogdepth");
		break;
	case 3:
		pd->type='c';
		pd->data=&fogcolor;
		strcpy(pd->name,"fogcolor");
		break;
	case 4:
		pd->type='i';
		pd->data=&fogmode;
		strcpy(pd->name,"fogmode");
		break;
	}
	return 5;
}

bsp_object *fogbox::clone()
{
	fogbox *tmp=new fogbox;
	*tmp=*this;
	tmp->source=this;
	return tmp;
}

int fogbox::get_custom_param_desc(int i,param_desc *pd)
{
	if (pd!=0)
	switch(i)
	{
	case 0:
		pd->type='f';
		pd->data=&fogsizex;
		strcpy(pd->name,"fogsizex");
		break;
	case 1:
		pd->type='f';
		pd->data=&fogsizey;
		strcpy(pd->name,"fogsizey");
		break;
	case 2:
		pd->type='f';
		pd->data=&fogsizez;
		strcpy(pd->name,"fogsizez");
		break;
	case 3:
		pd->type='c';
		pd->data=&fogcolor;
		strcpy(pd->name,"fogcolor");
		break;
	case 4:
		pd->type='f';
		pd->data=&fogrange;
		strcpy(pd->name,"fogrange");
		break;
	case 5:
		pd->type='f';
		pd->data=&fogdepth;
		strcpy(pd->name,"fogdepth");
		break;
	case 6:
		pd->type='i';
		pd->data=&fogmode;
		strcpy(pd->name,"fogmode");
		break;
	}
	return 7;
}



