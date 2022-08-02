#include "../../lib/Fly3D.h"
#include "lightengine.h"
#include "Commctrl.h"
#include <malloc.h>
#include <search.h>
#include <assert.h>

#define LIGHT_FACTOR 5000
#define ANGLE_THRESHOLD 0.99f
#define PLANE_THRESHOLD 0.1f

extern int lightvalue, mapsize;
extern int ambient,connectivity;
extern HDC hdc;
extern float lightradius,lmpixelsize;
extern HWND hWndHC,hWndProgress,hWndStatus;
void HC_CreateWindow();

static_mesh *lightEngine::get_object(bsp_node *n)
{
	bsp_object *e=n->elem;
	while(e)
		{
		if (e->type==TYPE_STATIC_MESH)
			break;
		e=e->next_elem;
		}
	return (static_mesh *)e;
}

void lightEngine::light(char *f)
{
	char str[256],file[256];
	strcpy(file,f);
	strlwr(file);

	GetPrivateProfileString("fly","bspfile","",bspfile,255,f);
	strcpy(flydatapath,f);
	if (strrchr(flydatapath,'/'))
		*(strrchr(flydatapath,'/')+1)=0;
	else if (strrchr(flydatapath,'\\'))
		*(strrchr(flydatapath,'\\')+1)=0;

	SetWindowText(hWndStatus,"Loading bsp...");
	strcpy(str,flydatapath);
	strcat(str,bspfile);
	strcat(str,".bsp");
	load_bsp(str);
	if (bsp)
	{
	SetWindowText(hWndStatus,"Sorting bsp faces...");
	sort_faces(bsp);

	SetWindowText(hWndStatus,"Saving bsp ...");
	save_bsp(str);

	SetWindowText(hWndStatus,"Creating lightmaps...");
	create_lightmaps();
	
	SetWindowText(hWndStatus,"Saving lightmaps...");
	strcpy(str,flydatapath);
	strcat(str,bspfile);
	strcat(str,".lmp");
	save_lightmaps(str);
	
	sprintf(str, "%i", ambient);
	WritePrivateProfileString("fly", "amblight", str, f);
	sprintf(str, "%f", lmpixelsize);
	WritePrivateProfileString("fly", "lmpxsize", str, f);
	sprintf(str, "%i", shadows);
	WritePrivateProfileString("fly", "shadows", str, f);
	sprintf(str, "%i", mapsize);
	WritePrivateProfileString("fly", "mapsize", str, f);

	strcpy(str,flyengine->flysdkpath);
	strcat(str,"data\\");
	int len=strlen(str);
	if (strncmp(file,str,len)==0)
		{
		SetWindowText(hWndStatus,"Loading level...");
		open_fly_file(&file[len]);
		}
	if (flyfile[0]!=0)
	{
	SetWindowText(hWndStatus,"Lighting level...");
	light_lightmaps();

	SetWindowText(hWndStatus,"Saving lightmaps ...");
	strcpy(str,flydatapath);
	strcat(str,bspfile);
	strcat(str,".lmp");
	save_lightmaps(str);

	SetWindowText(hWndStatus,"Saving level script ...");
	strcpy(str,flyfile);
	save_fly_file(str);

	SetWindowText(hWndStatus,"Done.");
	}
	else
	SetWindowText(hWndStatus,"Error loading level.");
	}
	else
		SetWindowText(hWndStatus,"Error loading bsp.");
	SendMessage(hWndProgress,PBM_SETPOS,0,0);
}

void lightEngine::clear_lightmaps(unsigned char pixel_light)
{
	int i;
	for( i=0;i<nlmpic;i++ )
		memset(lmpic[i]->bmp,0,lmpic[i]->bytesxy);

	for( i=0;i<nlm;i++ )
	{
		memset(lm[i]->bmp,pixel_light,lm[i]->bytesxy);
		lm[i]->save(lmpic[lm[i]->pic]);
	}
}

int lightEngine::compute_facelist(int facenum,int *facelist)
{
	int i,j,n=0,p=1;
	for( i=0;i<nfaces;i++ )
		if (faces[i].indx &&
			faces[i].lm==-1 &&
			faces[i].texpic!=-1 &&
			fabs(faces[i].d0-faces[facenum].d0)<PLANE_THRESHOLD &&
			vec_dot(faces[i].normal,faces[facenum].normal)>ANGLE_THRESHOLD)
			facelist[n++]=i;

	if (connectivity==0)
		return n;

	for( i=0;i<n;i++ )
		{
		if (i>=p || p>=n)
			break;
		for( j=p;j<n;j++ )
			{
			if (faces[facelist[j]].vert[0]==faces[facelist[i]].vert[0] ||
				faces[facelist[j]].vert[0]==faces[facelist[i]].vert[1] ||
				faces[facelist[j]].vert[0]==faces[facelist[i]].vert[2] ||
				faces[facelist[j]].vert[1]==faces[facelist[i]].vert[0] ||
				faces[facelist[j]].vert[1]==faces[facelist[i]].vert[1] ||
				faces[facelist[j]].vert[1]==faces[facelist[i]].vert[2] ||
				faces[facelist[j]].vert[2]==faces[facelist[i]].vert[0] ||
				faces[facelist[j]].vert[2]==faces[facelist[i]].vert[1] ||
				faces[facelist[j]].vert[2]==faces[facelist[i]].vert[2])
					{
					int swap=facelist[p];
					facelist[p]=facelist[j];
					facelist[j]=swap;
					p++;
					}
			}
		}

	return p;
}

boundbox lightEngine::compute_bbox(int *facelist,int nf)
{
	int i,j;
	boundbox bb;

	bb.reset();

	for( i=0;i<nf;i++ )
		for( j=0;j<3;j++ )
			bb.add_point(*faces[facelist[i]].vert[j]);

	return bb;
}

void lightEngine::compute_lightmaps()
{
	if (nfaces==0)
		return;

	int i,j,l,nf;
	boundbox bb;

	for( i=0;i<nfaces;i++ )
		faces[i].lm=-1;

	SetWindowText(hWndStatus,"Computing lightmaps ...");
	SendMessage(hWndProgress,PBM_SETRANGE,0,MAKELPARAM(0,nfaces));
	SendMessage(hWndProgress,PBM_SETPOS,0,0);

	int *facelist=new int[nfaces];
	
	for( i=0;i<nfaces;i++,SendMessage(hWndProgress,PBM_SETPOS,i,0) )
		if (faces[i].indx &&
			 faces[i].lm==-1 &&
			 faces[i].texpic!=-1)
		{
			nf=compute_facelist(i,facelist);
			bb=compute_bbox(facelist,nf);
			l=compute_lightmap_uv(bb,facelist,nf);
			for( j=0;j<nf;j++ )
				faces[facelist[j]].lm=l;

		}

	delete facelist;

	retb r;

	struct reta *rl=new struct reta[nlm];

	for(i=0;i<nlm; i++)
	{
		rl[i].sizex=lm[i]->sizex;
		rl[i].sizey=lm[i]->sizey;
		r.add(&rl[i]);
	}

	nlmpic=r.calc(mapsize, mapsize);

	for(i=0; i<nlm; i++)
	{
		lm[i]->offsetx=rl[i].offsetx;
		lm[i]->offsety=rl[i].offsety;
		lm[i]->pic=rl[i].offsetz;
	}

	delete rl;

	for(i=0; i<nlmpic; i++) lmpic[i]=new light_map_pic(mapsize, mapsize);

	for(i=0; i<nfaces; i++)
	{
		l=faces[i].lm;
		if(l!=-1)
			for(j=0; j<3; j++)
			{
				faces[i].lmuv[j][0]=(faces[i].lmuv[j][0]*lm[l]->sizex+lm[l]->offsetx)/mapsize;
				faces[i].lmuv[j][1]=(faces[i].lmuv[j][1]*lm[l]->sizey+lm[l]->offsety)/mapsize;
			}
	}

	for(i=0;i<nlm; i++)
		lm[i]->set_base(&faces[lm[i]->facenum],lmpic[lm[i]->pic]);

}

int lightEngine::compute_lightmap_uv(boundbox bb,int *facelist,int nf)
{
	int ui,vi,i,j;
	vector v,diag;
	float uv;
	int l;
	int sizex, sizey;

	diag=faces[facelist[0]].normal;

	i=(fabs(diag[0])>fabs(diag[1]))?0:1;
	i=(fabs(diag[i])>fabs(diag[2]))?i:2;

	if (i==0)
		{ ui=1;	vi=2; }
	else if (i==1)
		{ ui=0;	vi=2; }
	else { ui=0; vi=1; }

	diag=bb.max-bb.min;

	l=nlm++;
	sizex=(int)(diag[ui]/lmpixelsize);
	sizey=(int)(diag[vi]/lmpixelsize);

	lm[l]=new light_map(-1, -1, 0, 0, sizex<=mapsize?sizex:mapsize, sizey<=mapsize?sizey:mapsize);
	
	for( i=0;i<nf;i++ )
		for( j=0;j<3;j++ )
		{
		v=*faces[facelist[i]].vert[j] - bb.min;
		
		uv=v[ui]/diag[ui];
		if (lm[l]->sizex>1)
			uv=uv*(lm[l]->sizex-1)/lm[l]->sizex+1.0f/(lm[l]->sizex*2);
		
		faces[facelist[i]].lmuv[j][0]=uv;

		uv=v[vi]/diag[vi];
		if (lm[l]->sizey>1)
			uv=uv*(lm[l]->sizey-1)/lm[l]->sizey+1.0f/(lm[l]->sizey*2);

		faces[facelist[i]].lmuv[j][1]=uv;
		}
	
	lm[l]->facenum=facelist[0];

	return l;
}

void lightEngine::apply_light(bsp_node *n,vector& pos,vector& color,float rad)
{
	if (n->child[0]==0 && n->child[1]==0)
		{
		static_mesh *o=get_object(n);
		if (o)
			{
			int i;
			for( i=0;i<o->objmesh->nf;i++ )
				if (o->objmesh->faces[i]->lm!=-1)
				{
				if (lm[o->objmesh->faces[i]->lm]->lastupdate==0)
					lm[o->objmesh->faces[i]->lm]->illum(pos,color,rad,shadows);
				lm[o->objmesh->faces[i]->lm]->lastupdate=1;
				}
			}
		return;
		}

	static float dist;
	dist=n->distance(pos);
	if (fabs(dist)<rad)
		{
		if (n->child[0])
			apply_light(n->child[0],pos,color,rad);
		if (n->child[1])
			apply_light(n->child[1],pos,color,rad);
		}
	else
	if (dist>0)
		if (n->child[0])
			apply_light(n->child[0],pos,color,rad);
		else ;
	else if (n->child[1])
			apply_light(n->child[1],pos,color,rad);
}

void lightEngine::mark_used_bsp_faces(bsp_node *n)
{
	if (n->child[0]==0 && n->child[1]==0)
		{
		static_mesh *o=get_object(n);
		if (o)
			{
			int i;
			for( i=0;i<o->objmesh->nf;i++ )
				o->objmesh->faces[i]->indx=1;
			}
		}
	else 
	{
		if (n->child[0])
			mark_used_bsp_faces(n->child[0]);
		if (n->child[1])
			mark_used_bsp_faces(n->child[1]);
	}
}

void lightEngine::create_lightmaps()
{
	SendMessage(hWndProgress,PBM_SETPOS,0,0);
	SetWindowText(hWndStatus,"Creating ligthmaps ...");

	int i;
	for( i=0;i<nfaces;i++ )
		faces[i].indx=0;
	mark_used_bsp_faces(bsp);

	compute_lightmaps();
	clear_lightmaps(ambient);
}

void lightEngine::light_lightmaps()
{
	int i,j,k,n;
	vector v1,v2,c,pos,color;

	int nlmp=0;
	for( i=0;i<nlm;i++ )
		nlmp+=lm[i]->sizex*lm[i]->sizey;

	SendMessage(hWndProgress,PBM_SETRANGE,0,MAKELPARAM(0,nfaces));
	SendMessage(hWndProgress,PBM_SETPOS,0,0);
	char str[256];
	sprintf(str,"Rendering level lights ( %i lm / %i pixels ) ...",nlm,nlmp);
	SetWindowText(hWndStatus,str);

	for( i=0;i<nfaces;i++,SendMessage(hWndProgress,PBM_SETPOS,i,0) )
		if (faces[i].indx)
		if (faces[i].emmradius)
		{
			color=faces[i].color;
			if (lightvalue!=-1)
				{
				color.normalize();
				color*=lightvalue/255.0f;
				}

			v1=*faces[i].vert[1]-*faces[i].vert[0];
			v2=*faces[i].vert[2]-*faces[i].vert[0];
			c.cross(v1,v2);
		
			n=(int)(c.length()/LIGHT_FACTOR)+1;

			for( k=0;k<n;k++ )
			{
				for( j=0;j<nlm;j++ )
					lm[j]->lastupdate=0;
				float r1=(rand()%10000)/10000.0f;
				float r2=(rand()%10000)/10000.0f;
				pos = 
					*faces[i].vert[0] + v1*r1 + v2*r2 +
					faces[i].normal*10;
				if (lightradius)
					apply_light(bsp,pos,color,(float)lightradius);
				else apply_light(bsp,pos,color,faces[i].emmradius);
			}
		}
	bsp_object *obj=active_obj0;
	i=0;
	while(obj)
	{
		i++;
		obj=(bsp_object *)obj->next_obj;
	}
	sprintf(str,"Rendering object lights ( %i lm / %i pixels ) ...",nlm,nlmp);
	SendMessage(hWndProgress,PBM_SETRANGE,0,MAKELPARAM(0,i));
	SendMessage(hWndProgress,PBM_SETPOS,0,0);
	obj=active_obj0;
	i=0;
	while(obj)
	{
		obj->message(vector(0,0,0),0,FLYOBJM_STATICILLUM,0,0);
		SendMessage(hWndProgress,PBM_SETPOS,++i,0);
		obj=(bsp_object *)obj->next_obj;
	}

	for( i=0;i<nlm;i++ )
		lm[i]->save(lmpic[lm[i]->pic]);
}

void lightEngine::sort_faces(bsp_node *n)
{
	if (n->child[0]==0 && n->child[1]==0)
		{
		static_mesh *o=get_object(n);
		if (o)
			{
			int i=0,j;
			while(i<o->objmesh->nf)
				{
				for( j=i+1;j<o->objmesh->nf;j++ )
					if (o->objmesh->faces[i]->texpic==o->objmesh->faces[j]->texpic)
					{
						face *f=o->objmesh->faces[j];
						o->objmesh->faces[j]=o->objmesh->faces[i+1];
						o->objmesh->faces[i+1]=f;
						i++;
					}
				i++;
				}
			}
		return;
		}

	if (n->child[0])
		sort_faces(n->child[0]);
	if (n->child[1])
		sort_faces(n->child[1]);
}

int ordenar_por_area_desc(const void *elem1, const void *elem2)
{
	struct reta *r1, *r2;

	r1=*(struct reta **)elem1;
	r2=*(struct reta **)elem2;

	return r2->sizex*r2->sizey-r1->sizex*r1->sizey;
}

retb::retb()
{
	nl=0;
	l=(struct reta **)malloc(0);
}

retb::~retb()
{
	free(l);
}

void retb::add(struct reta *r)
{
	l=(struct reta **)realloc(l, (++nl)*sizeof(struct reta *));
	l[nl-1]=r;
}

int retb::calc(int max_sx, int max_sy)
{
	struct reta r;

	r.sizex=max_sx;
	r.sizey=max_sy;
	r.offsetx=0;
	r.offsety=0;
	r.offsetz=0;

	for(int i=0; i<nl; i++) l[i]->offsetz=-1;

	qsort((void *)l, (size_t)nl, sizeof(struct reta *), ordenar_por_area_desc);

	while(arrumar(&r)) r.offsetz++;

	return r.offsetz;
}

bool retb::arrumar(struct reta *rp)
{
	int i, dsx, dsy;
	struct reta r[2];
	
	if((i=procura(rp->sizex, rp->sizey))==nl) return false; 

	l[i]->offsetx=rp->offsetx;
	l[i]->offsety=rp->offsety;
	l[i]->offsetz=rp->offsetz;

	dsx=rp->sizex-l[i]->sizex;
	dsy=rp->sizey-l[i]->sizey;

	if(dsx*rp->sizey>dsy*rp->sizex)
	{
		r[0].sizex=dsx;
		r[0].sizey=rp->sizey;
		r[0].offsetx=rp->offsetx+l[i]->sizex;
		r[0].offsety=rp->offsety;
		r[0].offsetz=rp->offsetz;
		r[1].sizex=l[i]->sizex;
		r[1].sizey=dsy;
		r[1].offsetx=rp->offsetx;
		r[1].offsety=rp->offsety+l[i]->sizey;
		r[1].offsetz=rp->offsetz;
	}
	else
	{
		r[0].sizex=rp->sizex;
		r[0].sizey=dsy;
		r[0].offsetx=rp->offsetx;
		r[0].offsety=rp->offsety+l[i]->sizey;
		r[0].offsetz=rp->offsetz;
		r[1].sizex=dsx;
		r[1].sizey=l[i]->sizey;
		r[1].offsetx=rp->offsetx+l[i]->sizex;
		r[1].offsety=rp->offsety;
		r[1].offsetz=rp->offsetz;
	}

	for(i=0; i<2; i++) arrumar(&r[i]);

	return true;
}

int retb::procura(int sx, int sy)
{
	int i;

	for(i=0;i<nl;i++)
		if(l[i]->offsetz==-1 &&
			l[i]->sizex<=sx && l[i]->sizey<=sy)
			break;

	return i;
}