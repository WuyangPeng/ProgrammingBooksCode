#include "../Fly3D.h"

float bezier_curve::distance(float *p,float *p1,float *p2)
{
	// returns distance from point p to line defined by p1,p2

	float dot=0,len1=0,len2=0;
	int i;

	// alloc two vectors
	float *v1=new float [nd];
	float *v2=new float [nd];
	
	// compute length from (p1,p) and (p1,p2)
	for( i=0;i<nd;i++ )
	{
		v1[i]= p[i]-p1[i];
		v2[i]=p2[i]-p1[i];
		len1+=v1[i]*v1[i];
		len2+=v2[i]*v2[i];
	}
	len1=(float)sqrt(len1);
	len2=(float)sqrt(len2);
	
	// normalize 
	if (len1>0)
		for( i=0;i<nd;i++ )
			v1[i]/=len1;
	if (len2>0)
		for( i=0;i<nd;i++ )
			v2[i]/=len2;
	
	// compute dot product
	for( i=0;i<nd;i++ )
		dot+=v1[i]*v2[i];

	// free vectors
	delete v1; 
	delete v2;

	// return distance
	return (float)sqrt(len1*len1*(1.0f-dot*dot));
}

int bezier_curve::adaptative_subdiv(float maxerror,float *points,int maxpoints)
{
	if (maxpoints<2) return 0;

	int npoints,i,j;
	float tmp;

	// start points list with two points (the curve edges)
	points[0]=0.0f;
	points[1]=1.0f;
	npoints=2;

	// subdiv curve recursevily
	subdiv(0,1,&p[0],&p[nd*(np-1)],points,npoints,maxerror,maxpoints);

	// sort points
	for( i=1;i<npoints;i++ )
		for( j=i+1;j<npoints;j++ )
			if (points[j]<points[i])
			{
				tmp=points[i];
				points[i]=points[j];
				points[j]=tmp;
			}

	// sort number of points
	return npoints;
}

void bezier_curve::subdiv(float u1,float u2,float *p1,float *p2,float *points,int& npoints,float maxerror,int maxpoints)
{
	// if points list is not full
	if (npoints<maxpoints)
	{
	// alloc a new point
	float *p=new float[nd];
	
	// compute segment midpoint coordinate
	float u=(u1+u2)*0.5f;

	// evaluate curve at the segment midpoint
	evaluate(u,p);

	// if error is bigger then maxerror
	if (distance(p,p1,p2)>maxerror)
		{
		// add point to points list
		points[npoints++]=u;
		// subdiv each segment recursevily
		subdiv(u1,u,p1,p,points,npoints,maxerror,maxpoints);
		subdiv(u,u2,p,p2,points,npoints,maxerror,maxpoints);
		}
	
	// delete allocated point
	delete p;
	}
}

void bezier_curve::reset()
{
	if (p) 
		delete p;
	p=0;
	ns=0;
	np=0;
}

void bezier_curve::set_dim(int ndim)
{
	reset();
	nd=ndim;
}

void bezier_curve::add_point(float *f)
{
	// adds a new point to the curve
	// f must point to nd floats

	if (nd==0) return;
    float *t=new float[(np+1)*nd];
    if (p!=0)
        {
         memcpy(t,p,sizeof(float)*np*nd);
		 delete p;
        }
    p=t;
	memcpy(&p[np*nd],f,sizeof(float)*nd);
	np++;
    if (((np-4)%3)==0 && np>1)
       ns++;
}

void bezier_curve::evaluate_tangent(float u,float *f)
{	
	// evaluate the curve tangent at position u
	// f must point to nd floats

	if (p==0) return;

	static float B[4];
	float u1,u2;
	int s,a,b,c;

	if (u==1.0f)
		s=np-4;
	else s=(int)(u*(np-1))/3*3;
	u1=(u-(float)s/(np-1))*ns;

	u2=u1*u1;
	B[0] =-3.0f +  6.0f*u1 - 3.0f*u2;
	B[1] = 3.0f - 12.0f*u1 + 9.0f*u2;
	B[2] = 6.0f*u1 - 9.0f*u2;
	B[3] = 3.0f*u2;

	memset(f,0,sizeof(float)*nd);

	c=s*nd;
	for( a=0;a<4;a++ )
		for( b=0;b<nd;b++ )
			f[b]+=p[c++]*B[a];
}

void bezier_curve::evaluate(float u,float *f)
{
	// evaluate the curve point at position u
	// f must point to nd floats

	if (p==0) return;

	static float B[4];
	float u1,u2;
	int s,a,b,c;

	if (u==1.0f)
		s=np-4;
	else s=(int)(u*(np-1))/3*3;
	u1=(u-(float)s/(np-1))*ns;

	u2=1.0f-u1;
	B[0]=u2*u2*u2;
	B[1]=3.0f*u1*u2*u2;
	B[2]=3.0f*u1*u1*u2;
	B[3]=u1*u1*u1;

	memset(f,0,sizeof(float)*nd);

	c=s*nd;
	for( a=0;a<4;a++ )
		for( b=0;b<nd;b++ )
			f[b]+=p[c++]*B[a];
}

int bezier_curve::load_bez(char *file)
{
	// loads the curve from a .bez text file

	fly_pak fp;
	if (!fp.open(file))
		return 0;

	reset();
	int i,j,n,d;
	float *f;
	
	pivot.x=fp.get_float();
	pivot.y=fp.get_float();
	pivot.z=fp.get_float();
	d=fp.get_int();
	n=fp.get_int();
	set_dim(d);
	f=new float[d];
	for( i=0;i<n;i++ )
		{
		for( j=0;j<d;j++ )
			f[j]=fp.get_float();
		add_point(f);
		}
	delete f;
	fp.close();
	return 1;
}

float bezier_curve::length()
{
	if (ns==0 || nd==0) return 0;

	int i,j=ns*8,k,vv=1;
	float *v[2],len=0.0f,f;
	v[0]=new float[nd];
	v[1]=new float[nd];
	evaluate(0.0f,v[0]);
	for( i=1;i<j;i++ )
	{
		evaluate((float)i/(j-1),v[vv]);
		f=0.0f;
		for( k=0;k<nd;k++ )
			f+=(v[0][k]-v[1][k])*(v[0][k]-v[1][k]);
		len+=(float)sqrt(f);
		vv=!vv;
	}

	delete v[0];
	delete v[1];

	return len;
}

void bezier_patch::build_loft(bezier_curve *shape,bezier_curve *path,int texture,int lightmap,float tileu,float tilev)
{
	reset();
	if (shape && path && shape->nd==3 && path->nd==3)
	{
	mode=4;
	texpic=texture;
	lm=lightmap;
	npu=shape->np;
	npv=path->np;
	np=npu*npv;
	nsu=shape->ns;
	nsv=path->ns;
	p=new vector[np];
	t=new vector[np];
	vector v;
	local_system ls;
	int i,j,k=0;
	ls.align_z(vector(0,0,1));
	for( j=0;j<npv;j++ )
		{
		path->evaluate_tangent((float)j/(npv-1),&v.x);
		v.normalize();
		ls.rotate(ls.Z,v);
		v=*((vector *)&path->p[j*3]);
		for( i=0;i<npu;i++ )
			{
			p[k]=v+(*((vector *)&shape->p[i*3])*ls.mat);
			t[k].x=(float)i/(npu-1)*tileu;
			t[k].y=(float)j/(npv-1)*tilev;
			t[k].z=(float)i/(npu-1);
			t[k].w=(float)j/(npv-1);
			k++;
			}
		}
	}
}

void bezier_patch::evaluate(int evaltype,float u,float v,vector *dest)
{
	if (p==0 || t==0) 
		return;

	static float Bu[4],Bv[4],Bdu[4],Bdv[4];
	float u1,u2,v1,v2,f;
	int i,j,k,su,sv;

	vector point(0,0,0);
	vector textcoord(0,0,0,0);
	vector du(0,0,0),dv(0,0,0);

	switch(mode)
	{
	case 3:
		if (FP_BITS(u)==FP_ONE_BITS)
			su=npu-3;
		else su=(int)(u*(npu-1))/2*2;
		u1=(u-(float)su/(npu-1))*nsu;

		if (FP_BITS(v)==FP_ONE_BITS)
			sv=npv-3;
		else sv=(int)(v*(npv-1))/2*2;
		v1=(v-(float)sv/(npv-1))*nsv;

		u2=1.0f-u1;
		Bu[0]=u2*u2;
		Bu[1]=2.0f*u1*u2;
		Bu[2]=u1*u1;

		v2=1.0f-v1;
		Bv[0]=v2*v2;
		Bv[1]=2.0f*v1*v2;
		Bv[2]=v1*v1;

		if (evaltype&PATCH_EVAL_NORMAL)
			{
			Bdu[0]= 2.0f*u1-2.0f;
			Bdu[1]= 2.0f-4.0f*u1;
			Bdu[2]= 2.0f*u1;

			Bdv[0]= 2.0f*v1-2.0f;
			Bdv[1]= 2.0f-4.0f*v1;
			Bdv[2]= 2.0f*v1;
			}
		break;
	case 4:
		if (FP_BITS(u)==FP_ONE_BITS)
			su=npu-4;
		else su=(int)(u*(npu-1))/3*3;
		u1=(u-(float)su/(npu-1))*nsu;

		if (FP_BITS(v)==FP_ONE_BITS)
			sv=npv-4;
		else sv=(int)(v*(npv-1))/3*3;
		v1=(v-(float)sv/(npv-1))*nsv;

		u2=1.0f-u1;
		Bu[0]=u2*u2*u2;
		Bu[1]=3.0f*u1*u2*u2;
		Bu[2]=3.0f*u1*u1*u2;
		Bu[3]=u1*u1*u1;

		v2=1.0f-v1;
		Bv[0]=v2*v2*v2;
		Bv[1]=3.0f*v1*v2*v2;
		Bv[2]=3.0f*v1*v1*v2;
		Bv[3]=v1*v1*v1;

		if (evaltype&PATCH_EVAL_NORMAL)
			{
			u2=u1*u1;
			Bdu[0]=-3.0f +  6.0f*u1 - 3.0f*u2;
			Bdu[1]= 3.0f - 12.0f*u1 + 9.0f*u2;
			Bdu[2]= 6.0f*u1 - 9.0f*u2;
			Bdu[3]= 3.0f*u2;

			v2=v1*v1;
			Bdv[0]=-3.0f +  6.0f*v1 - 3.0f*v2;
			Bdv[1]= 3.0f - 12.0f*v1 + 9.0f*v2;
			Bdv[2]= 6.0f*v1 - 9.0f*v2;
			Bdv[3]= 3.0f*v2;
			}
	}

	for( i=0;i<mode;i++ )
		for( j=0;j<mode;j++ )
		{
			k=(sv+j)*npu+su+i;
			f=Bu[i]*Bv[j];
			if (evaltype&PATCH_EVAL_POINT)
				{
				point.x+=f*p[k].x;
				point.y+=f*p[k].y;
				point.z+=f*p[k].z;
				}
			if (evaltype&PATCH_EVAL_TEXTCOORD)
				{
				textcoord.x+=f*t[k].x;
				textcoord.y+=f*t[k].y;
				textcoord.z+=f*t[k].z;
				textcoord.w+=f*t[k].w;
				}
			if (evaltype&PATCH_EVAL_NORMAL)
				{
				du+=p[k]*(Bdu[i]*Bv[j]);
				dv+=p[k]*(Bu[i]*Bdv[j]);
				}
		}

	if (evaltype&PATCH_EVAL_POINT)
		*(dest++)=point;
	if (evaltype&PATCH_EVAL_TEXTCOORD)
		*(dest++)=textcoord;
	if (evaltype&PATCH_EVAL_NORMAL)
		{
		dest->cross(dv,du);
		dest->normalize();
		}
}

void bezier_patch::reset()
{
	if (p) 
		delete p;
	p=0;
	if (t)
		delete t;
	t=0;
	if (surf)
		delete surf;
	surf=0;
	np=npu=npv=nsu=nsv=0;
	mode=0;
	levelu=0;
	levelv=0;
	nvertu=0;
	nvertv=0;
}

int bezier_patch::load_pch(char *file)
{
	reset();

	fly_pak fp;
	if (!fp.open(file))
		return 0;

	mode=3;

	char texture[256];
	fp.get_string(texture);
	texpic=flyengine->get_picture(texture);

	int lm_pic=fp.get_int();
	int lm_offsetx=fp.get_int();
	int lm_offsety=fp.get_int();
	int lm_sizex=fp.get_int();
	int lm_sizey=fp.get_int();
	lm=-1;
	if (lm_pic<flyengine->nlmpic)
		{
		flyengine->lm[flyengine->nlm]=new light_map(-1,lm_pic,lm_offsetx,lm_offsety,lm_sizex,lm_sizey,3);
		flyengine->fm[flyengine->nlm]=new light_map(-1,lm_pic,lm_offsetx,lm_offsety,lm_sizex,lm_sizey,4);
		lm=flyengine->nlm++;
		}

	npu=fp.get_int();
	npv=fp.get_int();

	pivot.x=fp.get_float();
	pivot.y=fp.get_float();
	pivot.z=fp.get_float();

	np=npu*npv;
	nsu=(npu-1)/2;
	nsv=(npv-1)/2;

	p=new vector[np];
	t=new vector[np];
	
	int i;
	for( i=0;i<np;i++ )
	{
		p[i].x=fp.get_float();
		p[i].y=fp.get_float();
		p[i].z=fp.get_float();

		t[i].x=fp.get_float();
		t[i].y=fp.get_float();
		t[i].z=fp.get_float();
		t[i].w=fp.get_float();
	}

	fp.close();
	return 1;
}

int find_subdiv_level(vector v0,vector v1,vector v2)
{
    int level;
    vector a, b, dist;
	
	float factor=flyengine->curveerr*flyengine->curveerr;

    for (level=0;level<8;level++)
    {
	a=(v0+v1)*0.5f;
	b=(v1+v2)*0.5f;
	v2=(a+b)*0.5f;

	dist=v2-v1;
	if (vec_dot(dist,dist)<factor)
	    break;
	v1=a;
    }

    return level;
}



void bezier_patch::build_surface()
{
	if (mode!=3 || p==0 || t==0)
		return;
	int i,j,k,a;
	vector normal;

	levelu=0;
	levelv=0;
	k=0;
	for( j=0;j<=nsv;j++,k+=npu-1 )
	for( i=0;i<=nsu;i++,k+=2 )
	{
		if (i<nsu)
		{
			a=find_subdiv_level(p[k],p[k+1],p[k+2]);
			if (a>levelu)
				levelu=a;
		}
		if (j<nsv)
		{
			a=find_subdiv_level(p[k],p[k+npu],p[k+2*npu]);
			if (a>levelv)
				levelv=a;
		}
	}

	nvertu=(1<<levelu)*nsu+1;
	nvertv=(1<<levelv)*nsv+1;
	if (nvertu<2) nvertu=2;
	if (nvertv<2) nvertv=2;

	if (surf) delete surf;
	surf=new vector[nvertu*nvertv*2];

	k=0;
	for( j=0;j<nvertv;j++ )
		for( i=0;i<nvertu;i++,k+=2 )
			evaluate(PATCH_EVAL_POINT|PATCH_EVAL_TEXTCOORD,
				(float)i/(nvertu-1),(float)j/(nvertv-1),&surf[k]);
}

void bezier_patch::illuminate(vector& p,float rad,vector& color,int shadows)
{
	if (lm==-1)
		return;

	int i,j,k;
	float dist,u,v;
	vector point,dir;

	// get lightmap applied to patch
	light_map *l=flyengine->lm[lm];
	unsigned char *uc;

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
		evaluate(PATCH_EVAL_POINT,u,v,&point);
		
		// check if point is inside light radius
		dir=p-point;
		dist=vec_dot(dir,dir);
		if (dist>rad)
			uc+=3;
		else 
			{
			// compute lighting factor based on light radius and pixel distance
			dist=(1.0f-dist/rad)*255.0f;

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

void bezier_patch::draw(int nleveldrop)
{
	if (surf==0)
		return;

	int i,j,k,l,mapcount=0;
	float *f1,*f2;
	int dropu,dropv,numstrips;

	if (levelu>=nleveldrop)
		dropu=nleveldrop;
	else dropu=levelu;
	if (levelv>=nleveldrop)
		dropv=nleveldrop;
	else dropv=levelv;
	numstrips=(1<<(levelv-dropv))*nsv;
	dropu=(1<<dropu);
	dropv=(1<<dropv);
	k=dropu*8;
	l=dropv*nvertu*2;

	glColor3ub(255,255,255);

	if (flyengine->multitexture && ntextureunits>1 && flyengine->nlm)
		{
		tc->use(texpic);
		if (lm!=-1)
			tc->use(flyengine->lm[lm]->pic+flyengine->lmbase,1);
		for( j=0;j<numstrips;j++ )
			{
			f1=(float * )&surf[j*l]; f2=f1+(l<<2);
			glBegin(GL_TRIANGLE_STRIP);
			for( i=0;i<nvertu;i+=dropu,f1+=k,f2+=k)
				{
				glMultiTexCoord2fvARB(GL_TEXTURE0_ARB,f2+4);
				glMultiTexCoord2fvARB(GL_TEXTURE1_ARB,f2+6);
				glVertex3fv(f2);
				glMultiTexCoord2fvARB(GL_TEXTURE0_ARB,f1+4);
				glMultiTexCoord2fvARB(GL_TEXTURE1_ARB,f1+6);
				glVertex3fv(f1);
				}
			glEnd();
			}
		tc->use(-1,1);
		tc->use(-1,0);
		mapcount+=2;
		}
	else
	{
	if (flyengine->mapmode&MAPPING_TEXTURE)
		{
		tc->use(texpic);
		for( j=0;j<numstrips;j++ )
			{
			f1=(float * )&surf[j*l]; f2=f1+(l<<2);
			glBegin(GL_TRIANGLE_STRIP);
			for( i=0;i<nvertu;i+=dropu,f1+=k,f2+=k)
				{
				glTexCoord2fv(f2+4);
				glVertex3fv(f2);
				glTexCoord2fv(f1+4);
				glVertex3fv(f1);
				}
			glEnd();
			}
		mapcount++;
		}

	if (flyengine->mapmode&MAPPING_DETAIL &&
		flyengine->detailpic!=-1)
		{
		if (mapcount)
			{
			glBlendFunc(GL_ZERO,GL_SRC_COLOR);
			glDepthMask(GL_FALSE);
			glDepthFunc(GL_EQUAL);
			}
		tc->use(flyengine->detailpic);
		for( j=0;j<numstrips;j++ )
			{
			f1=(float * )&surf[j*l]; f2=f1+(l<<2);
			glBegin(GL_TRIANGLE_STRIP);
			for( i=0;i<nvertu;i+=dropu,f1+=k,f2+=k)
				{
				glTexCoord2f(f2[4]*flyengine->detailtile,f2[5]*flyengine->detailtile);
				glVertex3fv(f2);
				glTexCoord2f(f1[4]*flyengine->detailtile,f1[5]*flyengine->detailtile);
				glVertex3fv(f1);
				}
			glEnd();
			}
		mapcount++;
		}

	if (flyengine->mapmode&MAPPING_LIGHTMAP &&
		flyengine->nlm!=0)
		{
		if (mapcount)
			{
			glBlendFunc(GL_ZERO,GL_SRC_COLOR);
			glDepthMask(GL_FALSE);
			glDepthFunc(GL_EQUAL);
			}
		tc->use(flyengine->lm[lm]->pic+flyengine->lmbase);
		for( j=0;j<numstrips;j++ )
			{
			f1=(float * )&surf[j*l]; f2=f1+(l<<2);
			glBegin(GL_TRIANGLE_STRIP);
			for( i=0;i<nvertu;i+=dropu,f1+=k,f2+=k)
				{
				glTexCoord2fv(f2+6);
				glVertex3fv(f2);
				glTexCoord2fv(f1+6);
				glVertex3fv(f1);
				}
			glEnd();
			}
		mapcount++;
		}
	}

	if (flyengine->mapmode&MAPPING_FOGMAP)
	if (flyengine->nlm!=0)
		{
		if (mapcount)
			{
			glDepthMask(GL_FALSE);
			glDepthFunc(GL_EQUAL);
			glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
			}
		tc->use(flyengine->lm[lm]->pic+flyengine->fmbase);
		for( j=0;j<numstrips;j++ )
			{
			f1=(float * )&surf[j*l]; f2=f1+(l<<2);
			glBegin(GL_TRIANGLE_STRIP);
			for( i=0;i<nvertu;i+=dropu,f1+=k,f2+=k)
				{
				glTexCoord2fv(f2+6);
				glVertex3fv(f2);
				glTexCoord2fv(f1+6);
				glVertex3fv(f1);
				}
			glEnd();
			}
		mapcount++;
		}

	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LESS);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

mesh *bezier_patch::build_mesh()
{
	int i,j,k;
	
	mesh *m=new mesh;
	
	m->nv=nvertu*nvertv;
	m->vert=new vector[m->nv];
	k=0;
	for( i=0;i<m->nv;i++,k+=2 )
		m->vert[i]=surf[k];

	m->nf=(nvertu-1)*(nvertv-1)*2;
	m->localfaces=new face[m->nf];
	m->faces=new face *[m->nf];
	k=0;
	for( j=0;j<nvertv-1;j++ )
	for( i=0;i<nvertu-1;i++ )
	{
		m->localfaces[k].color.vec(1,1,1,1);
		m->localfaces[k].vert[0]=&m->vert[j*nvertu+i];
		m->localfaces[k].vert[1]=&m->vert[j*nvertu+i+1];
		m->localfaces[k].vert[2]=&m->vert[(j+1)*nvertu+i+1];
		m->faces[k]=&m->localfaces[k];
		k++;
		m->localfaces[k].color.vec(1,1,1,1);
		m->localfaces[k].vert[0]=&m->vert[j*nvertu+i];
		m->localfaces[k].vert[1]=&m->vert[(j+1)*nvertu+i+1];
		m->localfaces[k].vert[2]=&m->vert[(j+1)*nvertu+i];
		m->faces[k]=&m->localfaces[k];
		k++;
	}

	m->compute_normals(MESH_FACENORM|MESH_VERTNORM|MESH_BBOX);

	return m;
}