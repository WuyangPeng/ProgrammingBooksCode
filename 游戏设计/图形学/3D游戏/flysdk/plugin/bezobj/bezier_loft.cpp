#include "..\..\lib\Fly3D.h"
#include "bezobj.h"

void bezier_loft::init()
{
	patch.reset();
	if (sfmesh) 
		delete sfmesh;
	sfmesh=0;
	if (shape && path && source)
	{
		pos=path->pivot;
		patch.build_loft(shape,path,texpic,lm,tileu,tilev);
		build_stripfan();
	}
}

bsp_object *bezier_loft::clone()
{
	bezier_loft *tmp=new bezier_loft;
	*tmp=*this;
	tmp->source=this;
	return tmp;
}

int bezier_loft::get_custom_param_desc(int i,param_desc *pd)
{
	if (pd!=0)
	switch(i)
	{
	case 0:
		pd->type='z';
		pd->data=&shape;
		strcpy(pd->name,"shape");
		break;
	case 1:
		pd->type='z';
		pd->data=&path;
		strcpy(pd->name,"path");
		break;
	case 2:
		pd->type='p';
		pd->data=&texpic;
		strcpy(pd->name,"texpic");
		break;
	case 3:
		pd->type='i';
		pd->data=&lm;
		strcpy(pd->name,"lm");
		break;
	case 4:
		pd->type='f';
		pd->data=&tileu;
		strcpy(pd->name,"tileu");
		break;
	case 5:
		pd->type='f';
		pd->data=&tilev;
		strcpy(pd->name,"tilev");
		break;
	}
	return 6;
}

void bezier_loft::draw()
{
	if (sfmesh)
	{
		glPushMatrix();
		glTranslatef(pos.x,pos.y,pos.z);
		glMultMatrixf((float *)&mat);

		glColor3ub(255,255,255);
		sfmesh->draw(7);

		glPopMatrix();
	}
}

void bezier_loft::build_stripfan()
{
	// allocate new stripfan mesh
	if (sfmesh) delete sfmesh;
	sfmesh=new stripfan_mesh;

	int i,j,k,ns;
	float u,v;
	vector z[2];

	if (flyengine->appid==FLYAPPID_LIGHTBSP)
	{
		// create lightmap for patch
		int lightmapsx=(int)(shape->length()/flyengine->lmpxsize);
		int lightmapsy=(int)(path->length()/flyengine->lmpxsize);
		if (lightmapsx>MAX_CURVE_LMPIXELS)
			lightmapsx=MAX_CURVE_LMPIXELS;
		if (lightmapsy>MAX_CURVE_LMPIXELS)
			lightmapsy=MAX_CURVE_LMPIXELS;
		((bezier_loft *)source)->lm=lm=flyengine->add_lightmap(lightmapsx,lightmapsy);
		memset(flyengine->lm[lm]->bmp,flyengine->amblight,flyengine->lm[lm]->bytesxy);
	}

	// compute number of vertices in u and v base on curveerr
	// to setup an LOD mesh where each point in the mesh lies in the patch surface
	float *pointsu=new float[MAX_CURVE_VERTS];
	int nvu=shape->adaptative_subdiv(flyengine->curveerr,pointsu,MAX_CURVE_VERTS);
	float *pointsv=new float[MAX_CURVE_VERTS];
	int nvv=path->adaptative_subdiv(flyengine->curveerr,pointsv,MAX_CURVE_VERTS);

	// compute number of strips
	ns=nvu-1;

	// for each strip
	k=0;
	for( i=0;i<ns;i++ )
	{
		// create strip
		sfmesh->add_stripfan(nvv*2,texpic,lm);

		// for each pair of vertices
		for( j=0;j<nvv;j++ )
		{
			// evaluate vertex position, texture and lightmap coordinates

			u=pointsu[i+1];
			v=pointsv[j];
			patch.evaluate(PATCH_EVAL_POINT|PATCH_EVAL_TEXTCOORD,u,v,z);
			sfmesh->vertdata[k].pos=z[0];
			sfmesh->vertdata[k].u=z[1].x;
			sfmesh->vertdata[k].v=z[1].y;
			sfmesh->vertdata[k].ul=z[1].z;
			sfmesh->vertdata[k].vl=z[1].w;
			k++;

			u=pointsu[i];
			patch.evaluate(PATCH_EVAL_POINT|PATCH_EVAL_TEXTCOORD,u,v,z);
			sfmesh->vertdata[k].pos=z[0];
			sfmesh->vertdata[k].u=z[1].x;
			sfmesh->vertdata[k].v=z[1].y;
			sfmesh->vertdata[k].ul=z[1].z;
			sfmesh->vertdata[k].vl=z[1].w;
			k++;
		}
	}

	delete pointsu;
	delete pointsv;

	if (objmesh) delete objmesh;
	objmesh=sfmesh->build_mesh();
	objmesh->pivotpos=pos;
}

void bezier_loft::illuminate_patch(vector& p,float rad,vector& color,int shadows)
{
	int i,j,k;
	float dist,u,v;

	// get lightmap applied to patch
	light_map *l=flyengine->lm[lm];
	unsigned char *uc;
	
	// get light position in patch local coordinates
	vector center=(p-pos)*mat_t,point,dir;
	rad*=rad;

	// for each lightmap pixel in y
	for( j=0;j<l->sizey;j++ )
	{
		uc=&l->bmp[j*l->bytesx];
		v=(j+0.5f)/l->sizey;
		// for each lightmap pixel in x
		for( i=0;i<l->sizex;i++ )
		{
		u=(i+0.5f)/l->sizex;

		// get lightmap pixel position in the patch surface
		patch.evaluate(PATCH_EVAL_POINT,u,v,&point);
		
		// check if point is inside light radius
		dir=point-center;
		dist=dir.x*dir.x+dir.y*dir.y+dir.z*dir.z;
		if (dist>rad)
			uc+=3;
		else 
			{
			// compute lighting factor based on light radius and pixel distance
			dist=(1.0f-dist/rad)*255.0f;

			// if shadows required, multiply dot product of patch normal and 
			// light direction and check for collision
			if (shadows==2)
				{
				vector normal;
				dir.normalize();
				patch.evaluate(PATCH_EVAL_NORMAL,u,v,&normal);
				float dot=-vec_dot(dir,normal);
				flyengine->excludecollision=this;
				if (dot<0.0f ||
					flyengine->collision_test(flyengine->bsp,center,point))
					{
					uc+=3;
					flyengine->excludecollision=0;
					continue;
					}
				flyengine->excludecollision=0;
				dist*=dot;
				}

			// apply colors to lightmap

			k=(int)(color.x*dist)+(int)(*uc);
			*(uc++)=k>255?255:k;

			k=(int)(color.y*dist)+(int)(*uc);
			*(uc++)=k>255?255:k;

			k=(int)(color.z*dist)+(int)(*uc);
			*(uc++)=k>255?255:k;
			}
		}
	}
	
	l->lastupdate=flyengine->cur_step;
}

int bezier_loft::message(vector& p,float rad,int msg,int param,void *data)
{
	if (msg==FLYOBJM_ILLUM && (flyengine->mapmode&MAPPING_LIGHTMAP))
	{
		if (lm>=0 && lm<flyengine->nlm)
			illuminate_patch(p,rad,*((vector *)data),param);
	}
	else if (msg==FLYOBJM_CHANGEPARAM)
			if (param>=0 || 
				((param_desc *)data)->data==&flyengine->curveerr)
				init();
	return 0;
}
