#include "..\..\lib\Fly3D.h"
#include "bezobj.h"

void bezier_extrude::init()
{
	if (sfmesh) 
		delete sfmesh;
	sfmesh=0;
	if (curve && source)
	{
		pos=curve->pivot;
		build_stripfan();
	}
}

bsp_object *bezier_extrude::clone()
{
	bezier_extrude *tmp=new bezier_extrude;
	*tmp=*this;
	tmp->source=this;
	return tmp;
}

int bezier_extrude::get_custom_param_desc(int i,param_desc *pd)
{
	if (pd!=0)
	switch(i)
	{
	case 0:
		pd->type='z';
		pd->data=&curve;
		strcpy(pd->name,"curve");
		break;
	case 1:
		pd->type='f';
		pd->data=&width;
		strcpy(pd->name,"width");
		break;
	case 2:
		pd->type='p';
		pd->data=&fanpic;
		strcpy(pd->name,"fanpic");
		break;
	case 3:
		pd->type='p';
		pd->data=&strippic;
		strcpy(pd->name,"strippic");
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
	case 6:
		pd->type='f';
		pd->data=&tilew;
		strcpy(pd->name,"tilew");
		break;
	case 7:
		pd->type='i';
		pd->data=&lm[0];
		strcpy(pd->name,"lm1");
		break;
	case 8:
		pd->type='i';
		pd->data=&lm[1];
		strcpy(pd->name,"lm2");
		break;
	case 9:
		pd->type='i';
		pd->data=&lm[2];
		strcpy(pd->name,"lm3");
		break;
	}
	return 10;
}

void bezier_extrude::build_stripfan()
{
	if (sfmesh) delete sfmesh;
	sfmesh=new stripfan_mesh;

	float *points=new float[MAX_CURVE_VERTS];
	int nv=curve->adaptative_subdiv(flyengine->curveerr,points,MAX_CURVE_VERTS);

	sfmesh->add_stripfan(-(nv+1),fanpic,-1);
	sfmesh->add_stripfan(-(nv+1),fanpic,-1);
	sfmesh->add_stripfan(nv*2,strippic,-1);
	
	sfmesh->vertdata[0].pos.vec(0,0,-width);
	sfmesh->vertdata[0].u=sfmesh->vertdata[0].v=0.0f;
	
	int i,j=(nv+1)*2,k=j;
	for( i=1;i<=nv;i++ )
		{
		curve->evaluate(points[i-1],&sfmesh->vertdata[i].pos.x);
		sfmesh->vertdata[j-i]=sfmesh->vertdata[i];
		sfmesh->vertdata[i].pos.z=-width;
		sfmesh->vertdata[j-i].pos.z=width;
		sfmesh->vertdata[j-i].u=sfmesh->vertdata[i].u=sfmesh->vertdata[i].pos.x/tileu;
		sfmesh->vertdata[j-i].v=sfmesh->vertdata[i].v=sfmesh->vertdata[i].pos.y/tilev;
		}

	sfmesh->vertdata[i].pos.vec(0,0,width);
	sfmesh->vertdata[i].u=sfmesh->vertdata[i].v=0.0f;
	delete points;

	float u=0.0f;
	for( i=0;i<nv;i++ )
	{
	if (i>0)
		u+=(sfmesh->vertdata[i].pos-sfmesh->vertdata[i-1].pos).length();
	
	sfmesh->vertdata[j].pos=sfmesh->vertdata[i+1].pos;
	sfmesh->vertdata[j].u=u/tilew;
	sfmesh->vertdata[j].v=0.0f;
	sfmesh->vertdata[j].ul=(float)i/(nv-1);
	sfmesh->vertdata[j].vl=0.0f;
	j++;

	sfmesh->vertdata[j].pos=sfmesh->vertdata[--k].pos;
	sfmesh->vertdata[j].u=sfmesh->vertdata[j-1].u;
	sfmesh->vertdata[j].v=1.0f;
	sfmesh->vertdata[j].ul=sfmesh->vertdata[j-1].ul;
	sfmesh->vertdata[j].vl=1.0f;
	j++;
	}

	boundbox bbox;
	bbox.reset();
	for( i=1;i<=nv;i++ )
		bbox.add_point(sfmesh->vertdata[i].pos.x,sfmesh->vertdata[i].pos.y,sfmesh->vertdata[i].pos.z);
	float dx=bbox.max.x-bbox.min.x;
	float dy=bbox.max.y-bbox.min.y;
	int sx,sy,sz;

	if (flyengine->appid==FLYAPPID_LIGHTBSP)
	{
		sx=(int)(dx/flyengine->lmpxsize);
		sy=(int)(dy/flyengine->lmpxsize);
		sz=(int)(u/flyengine->lmpxsize);
		if (sx>MAX_CURVE_LMPIXELS)
			sx=MAX_CURVE_LMPIXELS;
		if (sy>MAX_CURVE_LMPIXELS)
			sy=MAX_CURVE_LMPIXELS;
		if (sz>MAX_CURVE_LMPIXELS)
			sz=MAX_CURVE_LMPIXELS;

		((bezier_extrude *)source)->lm[0]=lm[0]=flyengine->add_lightmap(sx,sy);
		((bezier_extrude *)source)->lm[1]=lm[1]=flyengine->add_lightmap(sx,sy);
		((bezier_extrude *)source)->lm[2]=lm[2]=flyengine->add_lightmap(sz,1);
		
		memset(flyengine->lm[lm[0]]->bmp,flyengine->amblight,flyengine->lm[lm[0]]->bytesxy);
		memset(flyengine->lm[lm[1]]->bmp,flyengine->amblight,flyengine->lm[lm[1]]->bytesxy);
		memset(flyengine->lm[lm[2]]->bmp,flyengine->amblight,flyengine->lm[lm[2]]->bytesxy);
	}

	sfmesh->stripfandata[2]=lm[0];
	sfmesh->stripfandata[5]=lm[1];
	sfmesh->stripfandata[8]=lm[2];

	if (lm[0]>0 && lm[0]<flyengine->nlm)
		{
		sx=flyengine->lm[lm[0]]->sizex;
		sy=flyengine->lm[lm[0]]->sizey;
		}
	else sx=sy=1;

	j=(nv+1)*2;
	for( i=0;i<j;i++ )
	{
	sfmesh->vertdata[i].ul=(sfmesh->vertdata[i].pos.x-bbox.min.x)/dx;
	sfmesh->vertdata[i].vl=(sfmesh->vertdata[i].pos.y-bbox.min.y)/dy;
	sfmesh->vertdata[i].ul=(sfmesh->vertdata[i].ul*(sx-1)+0.5f)/sx;
	sfmesh->vertdata[i].vl=(sfmesh->vertdata[i].vl*(sy-1)+0.5f)/sy;
	}

	if (objmesh) delete objmesh;
	objmesh=sfmesh->build_mesh();
	objmesh->pivotpos=pos;

	if (lm[0]>0 && lm[0]<flyengine->nlm)
		flyengine->lm[lm[0]]->set_base(&objmesh->localfaces[0],flyengine->lmpic[flyengine->lm[lm[0]]->pic],pos);
	if (lm[1]>0 && lm[1]<flyengine->nlm)
		flyengine->lm[lm[1]]->set_base(&objmesh->localfaces[nv-1],flyengine->lmpic[flyengine->lm[lm[1]]->pic],pos);
}

int bezier_extrude::message(vector& p,float rad,int msg,int param,void *data)
{
	if (msg==FLYOBJM_ILLUM && (flyengine->mapmode&MAPPING_LIGHTMAP))
	{
		light_map *l;
		if (lm[0]>=0 && lm[0]<flyengine->nlm)
			{
			l=flyengine->lm[lm[0]];
			l->illum(p,*((vector *)data),rad,param);
			l->lastupdate=flyengine->cur_step;
			}
		if (lm[1]>=0 && lm[1]<flyengine->nlm)
			{
			l=flyengine->lm[lm[1]];
			l->illum(p,*((vector *)data),rad,param);
			l->lastupdate=flyengine->cur_step;
			}
		if (lm[2]>=0 && lm[2]<flyengine->nlm)
			{
			l=flyengine->lm[lm[2]];
			illuminate_edge(p,rad,*((vector *)data),param);
			l->lastupdate=flyengine->cur_step;
			}
	}
	else 
		if (msg==FLYOBJM_CHANGEPARAM)
			if (param>=0 || 
				((param_desc *)data)->data==&flyengine->curveerr)
				init();
	return 0;
}

void bezier_extrude::draw()
{
	if (sfmesh)
	glPushMatrix();
	glTranslatef(pos.x,pos.y,pos.z);
	glMultMatrixf((float *)&mat);

	glColor3ub(255,255,255);
	sfmesh->draw(7);

	glPopMatrix();
}

void bezier_extrude::illuminate_edge(vector& p,float rad,vector& color,int shadows)
{
	int i,k;
	float dist,u;

	light_map *l=flyengine->lm[lm[2]];
	unsigned char *uc=l->bmp;
	
	vector center=(p-pos)*mat_t,point,dir;
	rad*=rad;

	for( i=0;i<l->sizex;i++ )
	{
		u=(i+0.5f)/l->sizex;
		curve->evaluate(u,&point.x);
		dir=point-center;
		dist=dir.x*dir.x+dir.y*dir.y+dir.z*dir.z;
		if (dist>rad)
			uc+=3;
		else 
			{
			dist=(1.0f-dist/rad)*255.0f;

			if (shadows==2)
				{
				vector tangent,normal;
				curve->evaluate_tangent(u,&tangent.x);
				tangent.normalize();
				dir.normalize();
				normal.cross(vector(0,0,1),tangent);
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

			k=(int)(color.x*dist)+(int)(*uc);
			*(uc++)=k>255?255:k;

			k=(int)(color.y*dist)+(int)(*uc);
			*(uc++)=k>255?255:k;

			k=(int)(color.z*dist)+(int)(*uc);
			*(uc++)=k>255?255:k;
			}
	}
}
