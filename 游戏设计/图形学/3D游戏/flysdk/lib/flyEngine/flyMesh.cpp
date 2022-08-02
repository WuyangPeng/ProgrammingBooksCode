#include "../Fly3D.h"

#define INCHE_TO_DECIMETER 0.254f

class import_3ds_mesh : private import3ds
{
	mesh *obj;
	int v,f,t,basev,basef;
	float *tx;

	void object3d(char *name,int nv,int nf,int ntc,float *local_axis);
	void vertex3(float *vec);
	void text_coord(float *uv);
	void face3(unsigned short *fa);
	void face_material(material *mat,int nf,unsigned short *faces);
public:
	import_3ds_mesh(char *file,mesh *m);
};

void mesh::reset()
{
	if (vert)
		delete vert;
	if (vertnorm)
		delete vertnorm;
	if (faces)
		delete faces;
	if (localfaces)
		delete localfaces;
	if (edges)
		delete edges;
	vert=0;
	vertnorm=0;
	faces=0;
	nv=0;
	nf=0;
	localfaces=0;
	edges=0;
	nedges=0;
	color.vec(0.0f,0.0f,0.0f);
}

mesh *mesh::clone()
{
	mesh *m=new mesh;
	*m=*this;
	
	m->vert=new vector[nv];
	m->vertnorm=new vector[nv];
	m->edges=new int[nedges*4];
	memcpy(m->vert,vert,sizeof(vector)*nv);
	memcpy(m->vertnorm,vertnorm,sizeof(vector)*nv);
	memcpy(m->edges,edges,sizeof(int)*nedges*4);

	m->faces=new face *[nf];
	m->localfaces=new face[nf];
	for( int i=0;i<nf;i++ )
	{
		m->faces[i]=&m->localfaces[i];
		m->localfaces[i]=localfaces[i];
		m->localfaces[i].vert[0]=&m->vert[localfaces[i].vert[0]-vert];
		m->localfaces[i].vert[1]=&m->vert[localfaces[i].vert[1]-vert];
		m->localfaces[i].vert[2]=&m->vert[localfaces[i].vert[2]-vert];
	}
	return m;
}

int mesh::get_edge(int v1,int v2)
{
	int i,j;
	for( i=j=0;i<nedges;i++,j+=4 )
		if ((v1==edges[j] && v2==edges[j+1]) ||
			(v1==edges[j+1] && v2==edges[j]))
			return i;
	return -1;
}

void mesh::compute_normals(int flag)
{
	int i,j;
	vector v1,v2;

	if (flag&MESH_IMPLODE)
		implode();

	if (flag&MESH_FACENORM)
	for( i=0;i<nf;i++ )
	{
		v1=*faces[i]->vert[1]-*faces[i]->vert[0];
		v2=*faces[i]->vert[2]-*faces[i]->vert[0];
		faces[i]->normal.cross(v1,v2);
		faces[i]->normal.normalize();
		faces[i]->d0=-vec_dot(faces[i]->normal,*faces[i]->vert[0]);
		for( j=0;j<3;j++ )
		{
			faces[i]->edgenormal[j].cross(
				*faces[i]->vert[(j+1)%3]-*faces[i]->vert[j],
				faces[i]->normal);
			faces[i]->edgenormal[j].normalize();
		}
	}

	if ((flag&MESH_VERTNORM) && vert)
	{
	if (vertnorm)
		delete vertnorm;
	vertnorm=new vector[nv];
	memset(vertnorm,0,sizeof(vector)*nv);
	for( j=0;j<nf;j++ )
	{
		vertnorm[faces[j]->vert[0]-vert]+=faces[j]->normal;
		vertnorm[faces[j]->vert[1]-vert]+=faces[j]->normal;
		vertnorm[faces[j]->vert[2]-vert]+=faces[j]->normal;
	}
	for( j=0;j<nv;j++ )
		vertnorm[j].normalize();
	for( i=0;i<nf;i++ )
		for( j=0;j<3;j++ )
			faces[i]->vertnormal[j]=vertnorm[faces[i]->vert[j]-vert];
	}

	if (flag&MESH_BBOX)
	{
	bbox.reset();
	for( i=0;i<nf;i++ )
		for( j=0;j<3;j++ )
			bbox.add_point(*faces[i]->vert[j]);
	}

	if (flag&MESH_EDGES)
	{
		if (edges)
			delete edges;
		edges=new int[nf*3*4];
		nedges=0;
		int e,i1,i2;
		// for each face
		for( i=0;i<nf;i++ )
			// for each face edge
			for( j=0;j<3;j++ )
			{
				i1=faces[i]->vert[j]-vert;
				i2=faces[i]->vert[(j+1)%3]-vert;
				e=get_edge(i1,i2);
				// if edge is not in edge list
				if (e==-1)
				{
					// add a new edge to the list
					edges[nedges*4]=i1;
					edges[nedges*4+1]=i2;
					edges[nedges*4+2]=i;
					edges[nedges*4+3]=-1;
					nedges++;
				}
				else 
				if ((faces[i]->color-faces[edges[e*4+2]]->color).length()<0.1f)
					edges[e*4+3]=i;
			}
	}
}

int mesh::load_3ds(char *name)
{
	import_3ds_mesh i(name,this);

	compute_normals(MESH_IMPLODE|MESH_FACENORM|MESH_VERTNORM|MESH_BBOX);

	return nf>0;
}

import_3ds_mesh::import_3ds_mesh(char *file,mesh *m)
{
	obj=m;
	basev=0;
	basef=0;
	tx=0;
	t=0;
	if (obj && file && file[0])
		import(file,INCHE_TO_DECIMETER);
	int i;
	for( i=0;i<obj->nf;i++ )
	{
		obj->faces[i]->vert[0]=&obj->vert[(int)obj->faces[i]->vert[0]];
		obj->faces[i]->vert[1]=&obj->vert[(int)obj->faces[i]->vert[1]];
		obj->faces[i]->vert[2]=&obj->vert[(int)obj->faces[i]->vert[2]];
	}
	if (tx)	delete tx;
}

void import_3ds_mesh::object3d(char *name,int nv,int nf,int ntc,float *local_axis)
{
	v=f=0;
	
	basev=obj->nv;
	basef=obj->nf;

	obj->pivotpos.x=local_axis[9];
	obj->pivotpos.y=local_axis[10];
	obj->pivotpos.z=local_axis[11];

	face *tf;
	tf=new face[nf+obj->nf];
	if (obj->localfaces)
	{
		memcpy(tf,obj->localfaces,sizeof(face)*obj->nf);
		delete obj->localfaces;
	}
	obj->localfaces=tf;

	vector *tv=new vector[nv+obj->nv];
	if (obj->vert)
	{
		memcpy(tv,obj->vert,sizeof(vector)*obj->nv);
		delete obj->vert;
	}
	obj->vert=tv;

	float *ttx=new float[2*(obj->nv+nv)];
	if (tx)
	{
		memcpy(ttx,tx,sizeof(float)*2*obj->nv);
		delete tx;
	}
	tx=ttx;

	obj->nv+=nv;
	obj->nf+=nf;

	if (obj->faces)
		delete obj->faces;
	obj->faces=new face *[obj->nf];
	int i;
	for( i=0;i<obj->nf;i++ )
		obj->faces[i]=&obj->localfaces[i];
}

void import_3ds_mesh::vertex3(float *vec)
{
	obj->vert[basev+v].x=vec[0];
	obj->vert[basev+v].y=vec[1];
	obj->vert[basev+v].z=vec[2];
	v++;
}

void import_3ds_mesh::text_coord(float *uv)
{
	tx[t*2]=uv[0];
	tx[t*2+1]=uv[1];
	t++;
}

void import_3ds_mesh::face3(unsigned short *fa)
{
	obj->faces[basef+f]->vert[0]=((vector *)(fa[0]+basev));
	obj->faces[basef+f]->vert[1]=((vector *)(fa[1]+basev));
	obj->faces[basef+f]->vert[2]=((vector *)(fa[2]+basev));
	obj->faces[basef+f]->uv[0][0]=tx[(fa[0]+basev)*2];
	obj->faces[basef+f]->uv[0][1]=tx[(fa[0]+basev)*2+1];
	obj->faces[basef+f]->uv[1][0]=tx[(fa[1]+basev)*2];
	obj->faces[basef+f]->uv[1][1]=tx[(fa[1]+basev)*2+1];
	obj->faces[basef+f]->uv[2][0]=tx[(fa[2]+basev)*2];
	obj->faces[basef+f]->uv[2][1]=tx[(fa[2]+basev)*2+1];
	obj->faces[basef+f]->texpic=-1;
	obj->faces[basef+f]->lm=-1;
	obj->faces[basef+f]->color.vec(0.5f,0.5f,0.5f,0.5f);
	obj->faces[basef+f]->emmradius=0.0f;
	obj->faces[basef+f]->lastdraw=0;
	f++;
}

void import_3ds_mesh::face_material(material *mat,int nf,unsigned short *faces)
{
	int i,pic;

	if (mat->map_texture1.filename[0])
		pic=flyengine->get_picture(mat->map_texture1.filename);
	else pic=-1;

	for( i=0;i<nf;i++ )
		{
		obj->faces[faces[i]+basef]->texpic=pic;
		obj->faces[faces[i]+basef]->color.x=mat->diffuse[0];
		obj->faces[faces[i]+basef]->color.y=mat->diffuse[1];
		obj->faces[faces[i]+basef]->color.z=mat->diffuse[2];
		obj->faces[faces[i]+basef]->color.w=1-mat->transparency;
		}
}

int face::ray_intersect(vector& ro,vector& rd,vector& ip,float& dist,float rad)
{
	if (rad==0.0f)
	{
		float x=vec_dot(normal,rd);
		if (x>-SMALL || *((int *)&color.w)==0)
			return 0;
		dist=(vec_dot(normal,*vert[0])-vec_dot(normal,ro))/x;
		if (dist<0)
			return 0;

		ip.x=ro.x+rd.x*dist;
		ip.y=ro.y+rd.y*dist;
		ip.z=ro.z+rd.z*dist;

		int i;
		for( i=0;i<3;i++ )
			if ((ip.x-vert[i]->x)*edgenormal[i].x+
				(ip.y-vert[i]->y)*edgenormal[i].y+
				(ip.z-vert[i]->z)*edgenormal[i].z > 0)
				return 0;

		return 1;
	}
	else
	{
		static vector v[3],n;

		v[0].x=vert[0]->x+vertnormal[0].x*rad;
		v[0].y=vert[0]->y+vertnormal[0].y*rad;
		v[0].z=vert[0]->z+vertnormal[0].z*rad;
		
		v[1].x=vert[1]->x+vertnormal[1].x*rad;
		v[1].y=vert[1]->y+vertnormal[1].y*rad;
		v[1].z=vert[1]->z+vertnormal[1].z*rad;
		
		v[2].x=vert[2]->x+vertnormal[2].x*rad;
		v[2].y=vert[2]->y+vertnormal[2].y*rad;
		v[2].z=vert[2]->z+vertnormal[2].z*rad;

		n.cross(v[1]-v[0],v[2]-v[0]);
		n.normalize();
	
		float x=vec_dot(n,rd);
		if (x>-SMALL || *((int *)&color.w)==0)
			return 0;
		dist=(vec_dot(n,v[0])-vec_dot(n,ro))/x;
		if (dist<0)
			return 0;

		ip.x=ro.x+rd.x*dist;
		ip.y=ro.y+rd.y*dist;
		ip.z=ro.z+rd.z*dist;

		int i,j,crossings=0,u0,u1;
		n.x=(float)fabs(n.x);
		n.y=(float)fabs(n.y);
		n.z=(float)fabs(n.z);
		if (n.x>n.y && n.x>n.z)
			{ u0=1; u1=2; }
		else 
		if (n.y>n.x && n.y>n.z)
			{ u0=0; u1=2; }
		else 
			{ u0=0; u1=1; }

		v[0][u0]-=ip[u0];
		v[1][u0]-=ip[u0];
		v[2][u0]-=ip[u0];
		v[0][u1]-=ip[u1];
		v[1][u1]-=ip[u1];
		v[2][u1]-=ip[u1];
		
		for( i=0; i<3; i++ )
			{
			j=(i+1) % 3;
			if(((v[i][u1]<-SMALL) && (v[j][u1]>=0)) || ((v[j][u1]<-SMALL) && (v[i][u1]>=0.0)))
				if((v[i][u0]>=0.0) && (v[j][u0]>=0.0))
					++crossings;
				else
					if((v[i][u0]>=0.0) || (v[j][u0]>=0.0))
						if((v[i][u0]-v[i][u1]*(v[j][u0]-v[i][u0])/(v[j][u1]-v[i][u1]))>SMALL)
							++crossings;
			}
		if((crossings%2)==0)
			return 0;
		else
			return 1;
	}
}

int mesh::ray_intersect(vector& ro,vector& rd,vector& ip,float& dist,float rad)
{
	static vector tmp_ip;
	static float tmp_dist;
	int i,f=-1;
	dist=BIG;

	for( i=0;i<nf;i++ )
		if (faces[i]->ray_intersect(ro,rd,tmp_ip,tmp_dist,rad))
			if (tmp_dist<dist)
			{
			dist=tmp_dist;
			ip=tmp_ip;
			f=i;
			}

	return f;
}

int mesh::ray_intersect_test(vector& ro,vector& rd,float rad)
{
	static vector tmp_ip;
	static float tmp_dist;
	int i;

	for( i=0;i<nf;i++ )
		if (faces[i]->ray_intersect(ro,rd,tmp_ip,tmp_dist,rad))
			if (tmp_dist<0.99f)
				return 1;
	return 0;
}

void face::inverse_map(vector& p, float& u, float& v)
{
	vector v1=*vert[1]-*vert[0],
		v2=*vert[2]-*vert[0],
		ip=p-*vert[0];

	float det;

	det=v1.x*v2.y-v1.y*v2.x;
	if(det!=0.0f)
	{
		u=(ip.x*v2.y-ip.y*v2.x)/det;
		v=(v1.x*ip.y-v1.y*ip.x)/det;
		return;
	}

	det=v1.x*v2.z-v1.z*v2.x;
	if(det!=0.0f)
	{
		u=(ip.x*v2.z-ip.z*v2.x)/det;
		v=(v1.x*ip.z-v1.z*ip.x)/det;
		return;
	}

	det=v1.y*v2.z-v1.z*v2.y;
	u=(ip.y*v2.z-ip.z*v2.y)/det;
	v=(v1.y*ip.z-v1.z*ip.y)/det;
}

void face::forward_map(float& u,float& v,vector& p)
{
	p.x=vert[0]->x+
		(vert[1]->x-vert[0]->x)*u+
		(vert[2]->x-vert[0]->x)*v;
	p.y=vert[0]->y+
		(vert[1]->y-vert[0]->y)*u+
		(vert[2]->y-vert[0]->y)*v;
	p.z=vert[0]->z+
		(vert[1]->z-vert[0]->z)*u+
		(vert[2]->z-vert[0]->z)*v;
}

void mesh::illum_faces(vector& ip,float d_max,vector& c,int shadows)
{
	if (lastdraw<flyengine->cur_frame_base || (flyengine->mapmode&MAPPING_LIGHTMAP)==0)
		return;

	light_map *lm;
	int i;

	for( i=0;i<nf;i++ )
		if(faces[i]->lm!=-1)
			{
			lm=flyengine->lm[faces[i]->lm];
			if (lm->lastupdate!=flyengine->cur_step)
				if (fabs(faces[i]->distance(ip))<d_max)
					{
					lm->illum(ip,c,d_max,shadows);
					lm->lastupdate=flyengine->cur_step;
					}
			}
}

mesh *static_mesh::ray_intersect(vector& ro,vector& rd,vector& ip,float& dist,int &facenum,float rad)
{
	if (objmesh)
	{
		facenum=objmesh->ray_intersect(ro,rd,ip,dist,rad);
		if (facenum!=-1)
			return objmesh;
	}
	return 0;
}

int static_mesh::ray_intersect_test(vector& ro,vector& rd,float rad)
{
	if (objmesh)
		if (objmesh->ray_intersect_test(ro,rd,rad))
			return 1;
	return 0;
}

int static_mesh::message(vector& p,float rad,int msg,int param,void *data)
{
	if (msg==FLYOBJM_ILLUM)
		if (objmesh)
			objmesh->illum_faces(p,rad,*((vector *)data),param);
	return 0;
}

void anim_mesh::reset()
{
	if (ao_vert) delete ao_vert;
	if (ao_bbox) delete ao_bbox;
	if (stripfancount) delete stripfancount;
	if (stripfanvert) delete stripfanvert;
	if (vertdata) delete vertdata;
	nframes=0;
	ao_vert=0;
	ao_bbox=0;
	nstripfan=0;
	nstripfanvert=0;
	stripfancount=0;
	stripfanvert=0;
	vertdata=0;
}

void anim_mesh::compute_bbox()
{
	int i,j,k=nv;
	vector *v=ao_bbox;
	for( i=0;i<nframes;i++ )
	{
		v[0].vec(BIG,BIG,BIG);
		v[1].vec(-BIG,-BIG,-BIG);
		for( j=k-nv;j<k;j++ )
		{
			if (ao_vert[j].x<v[0].x)
				v[0].x=ao_vert[j].x;
			if (ao_vert[j].y<v[0].y)
				v[0].y=ao_vert[j].y;
			if (ao_vert[j].z<v[0].z)
				v[0].z=ao_vert[j].z;

			if (ao_vert[j].x>v[1].x)
				v[1].x=ao_vert[j].x;
			if (ao_vert[j].y>v[1].y)
				v[1].y=ao_vert[j].y;
			if (ao_vert[j].z>v[1].z)
				v[1].z=ao_vert[j].z;
		}
		v+=2;
		k+=nv;
	}
}

int anim_mesh::load_fao(char *name)
{
	reset();
	fly_pak fp;
	if (fp.open(name))
		{
		int i;
		char skin[256];
		float *ao_uv;
		short *ao_face;

		fp.read(&i,sizeof(int));
		if (i!=9171)
			{
			fp.close();
			return 0;
			}

		fp.read(&nf,sizeof(int));
		fp.read(&nv,sizeof(int));
		fp.read(&nframes,sizeof(int));
		fp.read(&pivotpos,3*sizeof(float));
		fp.read(skin,64);

		ao_vert=new vector[nv*nframes];
		ao_bbox=new vector[2*nframes];
		ao_uv=new float[6*nf];
		ao_face=new short[3*nf];

		fp.read(ao_face,nf*sizeof(short)*3);
		fp.read(ao_uv,nf*sizeof(float)*6);
		for( i=0;i<nv*nframes;i++ )
			fp.read(&ao_vert[i],sizeof(float)*3);

		fp.read(&nstripfan,sizeof(int));
		if (nstripfan)
		{
		stripfancount=new int[nstripfan];
		fp.read(stripfancount,nstripfan*sizeof(int));
		fp.read(&nstripfanvert,sizeof(int));
		stripfanvert=new int[nstripfanvert];
		vertdata=new vertex[nstripfanvert];
		for( i=0;i<nstripfanvert;i++ )
			{
			fp.read(&vertdata[i].u,sizeof(float));
			fp.read(&vertdata[i].v,sizeof(float));
			fp.read(&stripfanvert[i],sizeof(int));
			}
		}

		fp.close();

		texpic=flyengine->get_picture(skin);
		if (texpic==-1)
			{
			if (strrchr(name,'\\'))
				strcpy(skin,strrchr(name,'\\')+1);
			else if (strrchr(name,'/'))
				strcpy(skin,strrchr(name,'/')+1);
			else strcpy(skin,name);
			if (strrchr(skin,'.'))
				*strrchr(skin,'.')=0;
			strcat(skin,".tga");
			texpic=flyengine->get_picture(skin);
			if (texpic==-1)
				{
				if (strrchr(skin,'.'))
					*strrchr(skin,'.')=0;
				strcat(skin,".jpg");
				texpic=flyengine->get_picture(skin);
				}
			}

		vert=new vector[nv];
		localfaces=new face[nf];
		faces=new face *[nf];

		for( i=0;i<nf;i++ )
			{
			faces[i]=&localfaces[i];
			localfaces[i].vert[0]=&vert[ao_face[i*3]];
			localfaces[i].vert[1]=&vert[ao_face[i*3+1]];
			localfaces[i].vert[2]=&vert[ao_face[i*3+2]];
			localfaces[i].uv[0][0]=ao_uv[i*6];
			localfaces[i].uv[0][1]=ao_uv[i*6+1];
			localfaces[i].uv[1][0]=ao_uv[i*6+2];
			localfaces[i].uv[1][1]=ao_uv[i*6+3];
			localfaces[i].uv[2][0]=ao_uv[i*6+4];
			localfaces[i].uv[2][1]=ao_uv[i*6+5];
			localfaces[i].color.vec(1,1,1,1);
			localfaces[i].lastdraw=0;
			localfaces[i].normal.null();
			}
		
		delete ao_face;
		delete ao_uv;
		ao_face=0;
		ao_uv=0;

		set_key(0);
		compute_normals(MESH_FACENORM|MESH_VERTNORM|MESH_BBOX|MESH_EDGES);
		compute_bbox();

		return 1;
		}
	return 0;
}

void anim_mesh::set_key(float key)
{
	if (key>=0.0f && key<=1.0f)
	{
	int i,j,k;
	float s;
	vector *v,*v0,*v1;
	j=(int)(key*nframes);
	if (j==nframes)
		{ j=0; key=0.0f; }
	s=1.0f/nframes;
	key=(key-j*s)/s;
	v0=&ao_vert[j*nv];
	if (j==nframes-1)
		k=0;
	else k=j+1;
	v1=&ao_vert[k*nv];
	v=vert;
	for( i=0;i<nv;i++,v++,v0++,v1++ )
		*v=*v0+(*v1-*v0)*key;

	bbox.min=ao_bbox[j*2]+(ao_bbox[k*2]-ao_bbox[j*2])*key;
	bbox.max=ao_bbox[j*2+1]+(ao_bbox[k*2+1]-ao_bbox[j*2+1])*key;
//	compute_normals(MESH_FACENORM|MESH_VERTNORM);
	}
}

void anim_mesh::set_key(int key)
{
	if (key>=0 && key<nframes)
	{
	memcpy(vert,&ao_vert[key*nv],sizeof(vector)*nv);

	bbox.min=ao_bbox[key*2];
	bbox.max=ao_bbox[key*2+1];
	compute_normals(MESH_FACENORM|MESH_VERTNORM);
	}
}

void mesh::implode(float mindist)
{
	if (vert==0) 
		return;

	char *f=new char[nv];
	memset(f,1,nv);

	int i,j,k,v;
	for( i=0;i<nv;i++ )
	 if (f[i])
	 for( j=i+1;j<nv;j++ )
		if (f[j])
		if ((vert[i]-vert[j]).length()<mindist)
		{
		f[j]=0;
		for( k=0;k<nf;k++ )
		 for( v=0;v<3;v++ )
			if (localfaces[k].vert[v]==&vert[j])
				localfaces[k].vert[v]=&vert[i];
		}

	for( i=0;i<nv;i++ )
		if (f[i]==0)
		{
		for( k=0;k<nf;k++ )
			for( v=0;v<3;v++ )
				if (localfaces[k].vert[v]-vert>i)
					localfaces[k].vert[v]=localfaces[k].vert[v]-1;
		memcpy(&vert[i],&vert[i+1],sizeof(vector)*(nv-i-1));
		memcpy(&f[i],&f[i+1],nv-i-1);
		nv--;
		i--;
		}

	delete f;
}


void mesh::set_numverts(int nverts,int keep)
{
	vector *tmp=new vector[nverts];
	if(keep)
		if (nverts>=nv)
			memcpy(tmp,vert,sizeof(vector)*nv);
		else 
			memcpy(tmp,vert,sizeof(vector)*nverts);
	nv=nverts;
	if (vert)
		delete vert;
	vert=tmp;
}

void mesh::set_numfaces(int nfaces,int local,int keep)
{
	face **tmp1=new face *[nfaces];
	if(keep)
		if (nfaces>=nf)
			memcpy(tmp1,faces,sizeof(face *)*nf);
		else 
			memcpy(tmp1,faces,sizeof(face *)*nfaces);
	if (faces)
		delete faces;
	faces=tmp1;
	if (local)
	{
		face *tmp2=new face[nfaces];
		if(keep)
			if (nfaces>=nf)
				memcpy(tmp2,localfaces,sizeof(face)*nf);
			else 
				memcpy(tmp2,localfaces,sizeof(face)*nfaces);
		if (localfaces)
			delete localfaces;
		localfaces=tmp2;
	}
	nf=nfaces;
}
