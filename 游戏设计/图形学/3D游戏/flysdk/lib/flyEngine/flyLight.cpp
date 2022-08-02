#include "..\Fly3D.h"

void light_vertex::add_light(vector& p,vector& c,float r)
{
	if (nlights<MAX_HWLIGHTS)
	{
		pos[nlights]=p;
		pos[nlights].w=1.0f;
		color[nlights]=c;
		color[nlights].w=1.0f;
		radius[nlights]=r;
		nlights++;
	}
}

void light_vertex::init_draw(bsp_object *obj)
{
	glEnable(GL_LIGHTING);
	for( int i=0;i<nhwlights;i++ )
	{
		if (i>=nlights)
			glDisable(GL_LIGHT0+i);
		else 
		{
			flyengine->excludecollision=obj;
			if (flyengine->collision_test(flyengine->bsp,pos[i],obj->pos))
				{
				flyengine->excludecollision=0;
				glDisable(GL_LIGHT0+i);
				}
			else
				{
				flyengine->excludecollision=0;
				glEnable(GL_LIGHT0+i);
				glLightfv(GL_LIGHT0+i,GL_POSITION,&pos[i].x);
				glLightf(GL_LIGHT0+i,GL_LINEAR_ATTENUATION,1.0f/radius[i]);
				glLightfv(GL_LIGHT0+i,GL_DIFFUSE,&color[i].x);
				glLightfv(GL_LIGHT0+i,GL_SPECULAR,&color[i].x);
				}
		}
	}	
	if (obj && obj->node)
	{
		vector ambient=obj->node->color*0.75f;
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT,&ambient.x);
	}
}

void light_vertex::end_draw()
{
	glDisable(GL_LIGHTING);
	nlights=0;
}

void light_map::set_base(face *f,light_map_pic *lmp,vector& pos)
{
	v0 = *f->vert[0] + pos;
	v1 = *f->vert[1] - *f->vert[0];
	v2 = *f->vert[2] - *f->vert[0];
	uv[0][0]=f->lmuv[0][0];
	uv[0][1]=f->lmuv[0][1];
	uv[1][0]=f->lmuv[1][0]-f->lmuv[0][0];
	uv[1][1]=f->lmuv[1][1]-f->lmuv[0][1];
	uv[2][0]=f->lmuv[2][0]-f->lmuv[0][0];
	uv[2][1]=f->lmuv[2][1]-f->lmuv[0][1];
	det=uv[1][0]*uv[2][1]-uv[2][0]*uv[1][1];
	normal=f->normal;
	vector p1,p2;
	map_point((float)offsetx/lmp->sizex,(float)offsety/lmp->sizey,d0);
	map_point((float)(offsetx+sizex)/lmp->sizex,(float)offsety/lmp->sizey,p1);
	map_point((float)offsetx/lmp->sizex,(float)(offsety+sizey)/lmp->sizey,p2);
	d1=p1-d0;
	d2=p2-d0;
}

void light_map::illum(vector& pos,vector& color,float rad,int shadows)
{
	static vector point,dir;
	int i,j,k;
	float dist,fi=1.0f/sizex,fj=1.0f/sizey,fy=fj*0.5f;
	vector v1=d0+d1*(fi*0.5f),v2=d1*fi;
	unsigned char *uc;
	
	rad *= rad;

	for( j=0;j<sizey;j++,fy+=fj )
	{
	uc=&bmp[j*bytesx];
	point.x = v1.x + d2.x*fy;
	point.y = v1.y + d2.y*fy;
	point.z = v1.z + d2.z*fy;
	for( i=0;i<sizex;i++,point+=v2 )
		{
		dist=
			(pos.x-point.x)*(pos.x-point.x)+
			(pos.y-point.y)*(pos.y-point.y)+
			(pos.z-point.z)*(pos.z-point.z);
		if (dist>rad)
			uc+=3;
		else 
			{
			dist=(1.0f-dist/rad)*255.0f;
			dir=point-pos;
			switch(shadows)
				{
				case 1:
					if (flyengine->shadow_obj)
						if (flyengine->shadow_obj->ray_intersect_test(pos,dir))
						{
						uc+=3;
						continue;
						}
					break;
				case 2:
					dir.normalize();
					float dot=-vec_dot(dir,normal);
					if (dot<0.0f ||
						flyengine->collision_test(flyengine->bsp,pos,point))
						{
						uc+=3;
						continue;
						}
//					dist*=dot;
					break;
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
}

void light_map::map_point(float u, float v, vector &point)
{
	u-=uv[0][0];
	v-=uv[0][1];
	point=
		v0+
		v1*((u*uv[2][1]-uv[2][0]*v)/det)+
		v2*((uv[1][0]*v-u*uv[1][1])/det);
}

void light_map::load(light_map_pic *lmp)
{
	int i;
	for( i=0;i<sizey;i++ )
		memcpy(
			&bmp[i*bytesx],
			&lmp->bmp[(i+offsety)*lmp->bytesx+offsetx*lmp->bytespixel],
			sizex*bytespixel);
}

void light_map::save(light_map_pic *lmp)
{
	int i;
	for( i=0;i<sizey;i++ )
		memcpy(
			&lmp->bmp[(i+offsety)*lmp->bytesx+offsetx*lmp->bytespixel],
			&bmp[i*bytesx],
			sizex*bytespixel);
}
