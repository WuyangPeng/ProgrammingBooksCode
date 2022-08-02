#include "expflybsp.h"
#include "../../../lib/Fly3D.h"
#include "scene_max.h"
#include "enum_scene.h"

#define SMALLF 0.001f

extern int lightradius,bspmode,planemode,maxdepth,savelog,cartoonlight;

void scene_max::build_bsptree()
{
	int i,j;

	bsp=new bsp_node_max;

	for( j=0,i=0;i<nfaces;i++ )
		if (faces[i].d0>0)
			{
			faces[i].indx=1;
			faces[i].d0=-vec_dot(*faces[i].vert[0],faces[i].normal);
			}
		else
			{
			faces[i].indx=0;
			j++;
			}

	static_mesh *o=new static_mesh;
	o->objmesh->nf=nfaces-j;
	o->objmesh->faces=new face *[o->objmesh->nf];
	for( j=0,i=0;i<nfaces;i++ )
		if (faces[i].indx)
			o->objmesh->faces[j++]=&faces[i];
	bsp->elem=o;

	((bsp_node_max *)bsp)->planeflags=new char[o->objmesh->nf];
	memset(((bsp_node_max *)bsp)->planeflags,1,o->objmesh->nf);

	for( i=0;i<o->objmesh->nf;i++ )
		((bsp_node_max *)bsp)->add_plane(o->objmesh->faces[i]->normal,o->objmesh->faces[i]->d0);

	if (bspmode==0)
		((bsp_node_max *)bsp)->split_faces_aligned();
	else 
		((bsp_node_max *)bsp)->split_axis_aligned(maxdepth);
}

void scene_max::save_map(char *name)
{
	FILE *fp;
	char *pic[512];
	int npic=0,i,j;

	for( i=0;i<nmatlib;i++ )
		if (matlib[i].map_texture1.filename[0]==0)
			matlib[i].map_texture1.piclibindx=-1;
		else
			{
			for( j=0;j<npic;j++ )
				if (!stricmp(pic[j],matlib[i].map_texture1.filename))
					break;
			if (j==npic)
				{
				pic[j]=new char[strlen(matlib[i].map_texture1.filename)+1];
				strcpy(pic[j],matlib[i].map_texture1.filename);
				npic++;
				}
			matlib[i].map_texture1.piclibindx=j;
			}

	fp=fopen(name,"wt");

	fprintf(fp,"%i\n",npic);
	for( i=0;i<npic;i++ )
		fprintf(fp,"%s\n",pic[i]);
	
	for( i=0;i<nfaces;i++ )
		if (faces[i].texpic!=-1)
			faces[i].texpic=matlib[faces[i].texpic].map_texture1.piclibindx;

	fclose(fp);

	for( i=0;i<npic;i++ )
		delete pic[i];
}

void bsp_node_max::split_faces_aligned()
{
	if (nplanes==0)
		return;

	int i,p,j;

	p=find_split_plane();
	if (p==-1) 
		return;	
	
	static_mesh *o=(static_mesh *)elem;
	side=-1;

	child[0]=new bsp_node_max;	
	child[1]=new bsp_node_max;
	child[0]->elem=new static_mesh;
	child[1]->elem=new static_mesh;

	float d1,d2,d3;

	for( i=0;i<o->objmesh->nf;i++ )		
		{
		d1=distance(*o->objmesh->faces[i]->vert[0]);
		d2=distance(*o->objmesh->faces[i]->vert[1]);
		d3=distance(*o->objmesh->faces[i]->vert[2]);

		j=find_plane(o->objmesh->faces[i]->normal,o->objmesh->faces[i]->d0);
		if (j==p)
			((bsp_node_max *)child[0])->add_face(o->objmesh->faces[i],0);
		else
		if (d1>-SMALLF && d2>-SMALLF && d3>-SMALLF) 
			((bsp_node_max *)child[0])->add_face(o->objmesh->faces[i],planeflags[i]);
		else 
		if (d1<SMALLF && d2<SMALLF && d3<SMALLF)
			((bsp_node_max *)child[1])->add_face(o->objmesh->faces[i],planeflags[i]);
		else 
			{ 
			((bsp_node_max *)child[0])->add_face(o->objmesh->faces[i],planeflags[i]);
			((bsp_node_max *)child[1])->add_face(o->objmesh->faces[i],planeflags[i]);
			}
		}

	delete o->objmesh->faces;
	o->objmesh->faces=0;
	delete elem;
	elem=0;
	if (planes) delete planes;
	nplanes=0;
	planes=0;
	if (planeflags) delete planeflags;
	planeflags=0;

	if (((static_mesh *)child[0]->elem)->objmesh->nf>0)
	{
		((bsp_node_max *)child[0])->side=0;
		((bsp_node_max *)child[0])->split_faces_aligned();
	}
	else
	{
		delete child[0]->elem;
		child[0]->elem=0;
		delete child[0];
		child[0]=0;
	}
	
//	if (((static_mesh *)child[1]->elem)->objmesh->nf>0)
	if (((bsp_node_max *)child[1])->nplanes)
	{
		((bsp_node_max *)child[1])->side=1;
		((bsp_node_max *)child[1])->split_faces_aligned();
	}
	else
	{
		delete child[1]->elem;
		child[1]->elem=0;
		delete child[1];
		child[1]=0;
	}
}

int bsp_node_max::find_split_plane()
{
	int i,k=-1;
	int n,dif,bestdif=100000,n1,n2,n3;
	float d1,d2,d3;
	static_mesh *o=(static_mesh *)elem;
	if (o==0) return -1;

	for( i=0;i<nplanes;i++ )
		{
		normal=planes[i].normal;
		d0=planes[i].d0;

		n1=n2=n3=0;
		for( n=0;n<o->objmesh->nf;n++ )
			{
			d1=distance(*o->objmesh->faces[n]->vert[0]);
			d2=distance(*o->objmesh->faces[n]->vert[1]);
			d3=distance(*o->objmesh->faces[n]->vert[2]);

			if (d1>-SMALLF && d2>-SMALLF && d3>-SMALLF)
				n1++;
			else 
			if (d1<SMALLF && d2<SMALLF && d3<SMALLF)
				n2++;
			else n3++;
			}

		dif=abs(n1-n2)+n3*2;
		if ((dif==bestdif && (rand()%1))||
			dif<bestdif)
			{
			bestdif=dif;
			k=i;
			}
		}

	if (k==-1)
		return -1;

	normal=planes[k].normal;
	d0=planes[k].d0;
	return k;
}

void bsp_node_max::add_face(face *f,int planeflag)
{
	static_mesh *o=(static_mesh *)elem;
	if (o==0) 
		return;
	
	face **tmp1;
	tmp1=new face *[o->objmesh->nf+1];
	memcpy(tmp1,o->objmesh->faces,sizeof(face *)*o->objmesh->nf);
	if (o->objmesh->faces) 
		delete o->objmesh->faces;
	o->objmesh->faces=tmp1;
	o->objmesh->faces[o->objmesh->nf]=f;

	char *tmp2;
	tmp2=new char[o->objmesh->nf+1];
	memcpy(tmp2,planeflags,o->objmesh->nf);
	if (planeflags)
		delete planeflags;
	planeflags=tmp2;
	planeflags[o->objmesh->nf]=planeflag;

	if (planeflag)
		add_plane(f->normal,f->d0);

	o->objmesh->nf++;
}

int bsp_node_max::find_plane(vector& normal,float d0)
{
	int i;
	for( i=0;i<nplanes;i++ )
		if (fabs(d0-planes[i].d0)<0.1 &&
			vec_dot(normal,planes[i].normal)>0.99f)
			break;
	if (i==nplanes)
		return -1;
	else return i;
}

int bsp_node_max::add_plane(vector& normal,float d0)
{
	int i=find_plane(normal,d0);

	if (i>=0)
		return i;

	plane *p=new plane[nplanes+1];
	memcpy(p,planes,sizeof(plane)*nplanes);
	if (planes) delete planes;
	planes=p;
	planes[nplanes].normal=normal;
	planes[nplanes].d0=d0;
	return nplanes++;
}

void bsp_node_max::split_axis_aligned(int depth)
{
	if (--depth==0)
		return;

	int i,k=-1;
	int n,dif,bestdif=100000,n1,n2,n3;
	float d1,d2,d3;
	static_mesh *o=(static_mesh *)elem;
	if (o==0) return;

	calc_bbox();
	vector pos(0,0,0);
	for( n=0;n<o->objmesh->nf;n++ )
		pos+=(*o->objmesh->faces[n]->vert[0]+
			*o->objmesh->faces[n]->vert[1]+
			*o->objmesh->faces[n]->vert[2])/3.0f;
	pos/=(float)o->objmesh->nf;

	for( i=0;i<planemode;i++ )
	{
		normal.vec(0,0,0);
		(&normal.x)[i]=1;
		d0=-vec_dot(pos,normal);

		n1=n2=n3=0;
		for( n=0;n<o->objmesh->nf;n++ )
			{
			d1=distance(*o->objmesh->faces[n]->vert[0]);
			d2=distance(*o->objmesh->faces[n]->vert[1]);
			d3=distance(*o->objmesh->faces[n]->vert[2]);

			if (d1>-SMALLF && d2>-SMALLF && d3>-SMALLF)
				n1++;
			else 
			if (d1<SMALLF && d2<SMALLF && d3<SMALLF)
				n2++;
			else n3++;
			}

		dif=abs(n1-n2)+n3*2;
		if (dif<bestdif || (dif==bestdif && (rand()&1)))
			{
			bestdif=dif;
			k=i;
			}
	}

	if (k==-1) return;

	normal.vec(0,0,0);
	(&normal.x)[k]=1;
	d0=-vec_dot(pos,normal);
	side=-1;
	child[0]=new bsp_node_max;	
	child[1]=new bsp_node_max;
	child[0]->elem=new static_mesh;
	child[1]->elem=new static_mesh;

	for( i=0;i<o->objmesh->nf;i++ )		
		{
		d1=distance(*o->objmesh->faces[i]->vert[0]);
		d2=distance(*o->objmesh->faces[i]->vert[1]);
		d3=distance(*o->objmesh->faces[i]->vert[2]);

		if (d1<SMALLF && d2<SMALLF && d3<SMALLF)
			((bsp_node_max *)child[1])->add_face(o->objmesh->faces[i],0);
		else 
		if (d1>-SMALLF && d2>-SMALLF && d3>-SMALLF) 
			((bsp_node_max *)child[0])->add_face(o->objmesh->faces[i],0);
		else 
			{ 
			((bsp_node_max *)child[0])->add_face(o->objmesh->faces[i],0);
			((bsp_node_max *)child[1])->add_face(o->objmesh->faces[i],0);
			}
		}

	delete o->objmesh->faces;
	o->objmesh->faces=0;
	delete elem;
	elem=0;

	((bsp_node_max *)child[0])->side=0;
	((bsp_node_max *)child[1])->side=1;

	((bsp_node_max *)child[0])->split_axis_aligned(depth);
	((bsp_node_max *)child[1])->split_axis_aligned(depth);
}

void scene_max::compute_scene_normals()
{
	int i, k;
	vector v1, v2;

	for( i=0;i<nfaces;i++ )
		for( k=0;k<3;k++ )
			faces[i].vert[k]=&vert[(int)faces[i].vert[k]];
	
	for(i=0; i<nfaces; i++)
	{
		v1=*faces[i].vert[1]-*faces[i].vert[0];
		v2=*faces[i].vert[2]-*faces[i].vert[0];
		faces[i].normal.cross(v1,v2);
		faces[i].d0=faces[i].normal.length();
		faces[i].normal.normalize();
	}
	
	compute_normals();
}

void scene_max::save(char *file)
{
	if (bsp)
	{
	if (bsp->child[0]!=0 || bsp->child[1]!=0)
		{
		strcpy(strrchr(file,'.'),".tex");
		save_map(file);
		
		strcpy(strrchr(file,'.'),".bsp");
		save_bsp(file);

		if (savelog)
			{
			strcpy(strrchr(file,'.'),".bsplog.txt");
			FILE *fp=fopen(file,"wt");
			int tot=0;
			fprintf(fp,"depth\tnfaces\tside\n");
			((bsp_node_max *)bsp)->print(fp,tot,0);
			fprintf(fp,"\nTotal: %i %i\n",nfaces,tot);
			fclose(fp);
			}
		}

	((bsp_node_max *)bsp)->free_faces();
	}
}

void bsp_node_max::free_faces()
{
	if (elem)
	{
		static_mesh *o=(static_mesh *)elem;
		delete o->objmesh->faces;
		o->objmesh->faces=0;
		delete elem;
		elem=0;
	}
	if (child[0])
		((bsp_node_max *)child[0])->free_faces();
	if (child[1])
		((bsp_node_max *)child[1])->free_faces();
}

void bsp_node_max::print(FILE *fp,int& tot,int depth)
{
	static_mesh *o=(static_mesh *)elem;

	if (side!=-1)
		{
		fprintf(fp,"%i\t%i\t%i\n",depth,o->objmesh->nf,side);
		tot+=o->objmesh->nf;
		}
	else
		{
		if (child[0])
			((bsp_node_max *)child[0])->print(fp,tot,depth+1);
		if (child[1])
			((bsp_node_max *)child[1])->print(fp,tot,depth+1);
		}
}

void bsp_node_max::calc_bbox()
{
	int i,j;
	static_mesh *o=(static_mesh *)elem;
	bbox.reset();
	if (o)
		for( i=0;i<o->objmesh->nf;i++ )
			for( j=0;j<3;j++ )
				bbox.add_point(*o->objmesh->faces[i]->vert[j]);
}

void scene_max::compute_light()
{
	if (nlights)
	{
		int i,j;
		float dot;
		if (cartoonlight)
		{
			vector lightdir;
			float *uv=new float[nvert];
			memset(uv,0,sizeof(float)*nvert);
			for( i=0;i<nlights;i++ )
			for( j=0;j<nvert;j++ )
				{
				lightdir=lightlib[i].pos-vert[j];
				lightdir.normalize();
				dot=vec_dot(lightdir,vertnormal[j]);
				if (dot>0)
					uv[j]+=dot;
				if (vertcolor)
					vertcolor[j]*=lightlib[i].color;
				}
			for( i=0;i<nfaces;i++ )
				for( j=0;j<3;j++ )
				{
					faces[i].uv[j][0]=uv[faces[i].vert[j]-vert];
					faces[i].uv[j][1]=0.0f;
				}
			delete uv;
		}
		else
		{
			if (vertcolor==0)
			{
				vertcolor=new vector[nvert];
				for( i=0;i<nvert;i++ )
					vertcolor[i].vec(1,1,1);
			}
			vector *col=new vector[nvert];
			memset(col,0,sizeof(vector)*nvert);
			for( i=0;i<nlights;i++ )
			{
				vector lightdir=lightlib[i].pos-vert[i];
				lightdir.normalize();
				for( j=0;j<nvert;j++ )
				{
					dot=vec_dot(vertnormal[j],lightdir);
					if (dot>=0)
						col[j]+=vertcolor[j]*lightlib[i].color*
								vec_dot(vertnormal[j],lightdir);
				}
			}
			delete vertcolor;
			vertcolor=col;
		}
	}
}

void scene_max::enum_leaf(bsp_node *n)
{
	if (n->child[0]==0 && n->child[1]==0)
	{
		n->leaf=nleaf++;
		return;
	}
	if (n->child[0])
		enum_leaf(n->child[0]);
	if (n->child[1])
		enum_leaf(n->child[1]);
}