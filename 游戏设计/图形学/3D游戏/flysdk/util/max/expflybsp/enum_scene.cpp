#include "expflybsp.h"
#include "../../../lib/Fly3D.h"
#include "scene_max.h"
#include "enum_scene.h"
#include "stdmat.h"
#include <stdio.h>
#include "../flyfao/flyfao.h"
#include "shape.h"

#define OBTYPE_MESH 0
#define OBTYPE_CAMERA 1
#define OBTYPE_OMNILIGHT 2
#define OBTYPE_SPOTLIGHT 3
#define OBTYPE_DUMMY 5
#define OBTYPE_CTARGET 6
#define OBTYPE_LTARGET 7

#define cc(a) ((a)>1.0f?1.0f:(a))
extern int saveobj,savebsp;
extern int lightradius;
extern int tot_vert,tot_face;

void enum_scene::AddLight(GenLight* ob, Matrix3 mat3)
{
	Point3 colorVal = ob->GetRGBColor(0), pos;
	float fac=(float)GetMasterScale(UNITS_CENTIMETERS)/10;

	if(nlights)
	{
		light_max *tmp=new light_max[nlights+1];
		memcpy(tmp, lightlib, sizeof(light_max)*nlights);
		delete lightlib;
		lightlib=tmp;
	}
	else lightlib=new light_max;
	 
	pos=mat3.GetRow(3);

	lightlib[nlights].type=0;
	lightlib[nlights].pos.vec(pos.x*fac, pos.y*fac, pos.z*fac);
	lightlib[nlights].color.vec(colorVal.x,colorVal.y,colorVal.z);
	nlights++;
}

int enum_scene::AddMtl(Mtl *m)
{
	Color c;
	int i, k, l;
	char m_name[128], m_name_base[128];
	StdMat* std;

	if(!m) return 0;

	strcpy(m_name_base, m->GetName());
	
	strcpy(m_name, m_name_base);
	if(m->ClassID()==Class_ID(MULTI_CLASS_ID,0))
	{
		strcat(m_name, m->GetSubMtl(0)->GetName());
		l=m->NumSubMtls();
	}
	else
		l=1;
			
	if((i=FindMtl(m_name))>0) return i;

	for(k=0; k<l; k++)
	{
		material *temp=new material[nmatlib+1];
		memcpy(temp, matlib, nmatlib*sizeof(material));
		delete matlib;
		matlib=temp;

		strcpy(m_name, m_name_base);
		
		if(m->ClassID()==Class_ID(MULTI_CLASS_ID,0))
		{
			std = (StdMat *)m->GetSubMtl(k);
			strcat(m_name, std->GetName());
			matlib[nmatlib].l=l;
		}
		else
		{
			std = (StdMat *)m;
			matlib[nmatlib].l=0;
		}

		strcpy(matlib[nmatlib].name, m_name);

		c=std->GetAmbient(0);
		matlib[nmatlib].ambient[0]=c.r;
		matlib[nmatlib].ambient[1]=c.g;
		matlib[nmatlib].ambient[2]=c.b;

		c=std->GetDiffuse(0);
		matlib[nmatlib].diffuse[0]=c.r;
		matlib[nmatlib].diffuse[1]=c.g;
		matlib[nmatlib].diffuse[2]=c.b;

		matlib[nmatlib].transparency=std->GetXParency();
		matlib[nmatlib].self_illum=std->GetSelfIllum(0);

		Texmap *tx;
		tx=std->GetSubTexmap(ID_DI);
		if(tx!=NULL && tx->ClassID()==Class_ID(BMTEX_CLASS_ID,0))
		{
			BitmapTex *bmt = (BitmapTex*)tx;
			StdUVGen *uv = bmt->GetUVGen();
			matlib[nmatlib].map_texture1.u_scale=uv->GetUScl(0);
			matlib[nmatlib].map_texture1.v_scale=uv->GetVScl(0);
			matlib[nmatlib].map_texture1.u_offset=uv->GetUOffs(0);
			matlib[nmatlib].map_texture1.v_offset=uv->GetVOffs(0);
			matlib[nmatlib].map_texture1.rotation=uv->GetAng(0);
			strcpy(matlib[nmatlib].map_texture1.filename, bmt->GetMapName());
			if (strrchr(matlib[nmatlib].map_texture1.filename,'/'))
				strcpy(matlib[nmatlib].map_texture1.filename,strrchr(matlib[nmatlib].map_texture1.filename,'/')+1);
			else if (strrchr(matlib[nmatlib].map_texture1.filename,'\\'))
				strcpy(matlib[nmatlib].map_texture1.filename,strrchr(matlib[nmatlib].map_texture1.filename,'\\')+1);
		}
		nmatlib++;
	}

	return nmatlib-k;
}

int enum_scene::FindMtl(char *name)
{
	for(int i=1; i<nmatlib; i++)
		if(stricmp(matlib[i].name, name)==0)
			return i;

	return 0;
}

void enum_scene::Save3DS(Mesh *m, char *name, int mat, Matrix3 tm,Point3 pos, Matrix3 piv)
{
	char filename[256];
	float *v,*t,local_axis[12]={ 1,0,0, 0,1,0, 0,0,1, 0,0,0 };
	unsigned short nv,*f,nf,*mf,nmf;
	int a,i,j,k;
	Point3 pt;

	pt.x=0; pt.y=0; pt.z=0;
	pt=pt*Inverse(piv);
	pt=pt*tm;
	local_axis[9]=pt.x;
	local_axis[10]=pt.y;
	local_axis[11]=pt.z;	

	nf=m->numFaces;
	nv=m->numVerts;
	v=new float[nv*3];
	f=new unsigned short[nf*3];
	mf=new unsigned short[nf*3];
	t=new float[nv*2];
	for( a=0;a<nv;a++ )
		{
		pt=m->verts[a]*piv;
		pt=pt*tm;
		pt=pt-pos;

		v[a*3]   = pt.x;
		v[a*3+1] = pt.y;
		v[a*3+2] = pt.z;
		}
	for( a=0;a<nf;a++ )
		for(i=0;i<3;i++)
		{
			f[a*3+i]=(unsigned short)m->faces[a].v[i];
			if (m->tvFace)
				{
				t[f[a*3+i]*2]=m->tVerts[m->tvFace[a].t[i]].x;
				t[f[a*3+i]*2+1]=-m->tVerts[m->tvFace[a].t[i]].y;
				}
			else 
				{
				t[f[a*3+i]*2]=
				t[f[a*3+i]*2+1]=0;
				}
		}

	if(matlib[mat].l>0)
		{
		j=0;
		for( i=0;i<matlib[mat].l;i++ )
			{
			mf[j++]=i;
			k=j;
			mf[j++]=0;
			for( a=0;a<nf;a++ )
				if ((m->faces[a].getMatID()%matlib[mat].l)==i)
					mf[j++]=a;
			mf[k]=j-k-1;
			}
		nmf=j;
		}
	else
		{
		mf[0]=0;
		mf[1]=nf;
		for( i=0;i<nf;i++ )
			mf[2+i]=i;
		nmf=nf+2;
		}

	strcpy(filename,"objects/");
	strcat(filename,name);
	strcat(filename,".3ds");
	export3ds e(filename,(float)GetMasterScale(UNITS_INCHES),&matlib[mat],matlib[mat].l==0?1:matlib[mat].l);

	e.WriteNamedObject(	name, v, t,	nv, f, nf, mf, nmf, &matlib[mat],local_axis);
	e.close();

	delete v;
	delete f;
	delete mf;
	delete t;
}

void enum_scene::AddMesh(Mesh *m, char *name, int mat, Matrix3 mat3)
{
	Point3 pt;
	Interval valid;
	float fac=(float)GetMasterScale(UNITS_CENTIMETERS)/10;
	int a, i;

	for( a=0;a<m->numVerts;a++ )
	{
		pt = m->verts[a] * mat3;
		vert[a+nvert].vec(pt.x*fac, pt.y*fac, pt.z*fac);
	}

	for( a=0;a<m->numFaces;a++ )
	{
		for(i=0;i<3;i++)
		{
			faces[a+nfaces].vert[i]=(vector *)(m->faces[a].v[i]+nvert);
			if (m->tvFace)
				{
				faces[a+nfaces].uv[i][0]=m->tVerts[m->tvFace[a].t[i]].x;
				faces[a+nfaces].uv[i][1]=-m->tVerts[m->tvFace[a].t[i]].y;
				}
			else 
				faces[a+nfaces].uv[i][0]=faces[a+nfaces].uv[i][1]=0;
		}

		if(matlib[mat].l>0)
			faces[a+nfaces].texpic=mat+(m->faces[a].getMatID()%matlib[mat].l);
		else
			faces[a+nfaces].texpic=mat;

		faces[a+nfaces].color=*((vector *)&matlib[faces[a+nfaces].texpic].diffuse);
		faces[a+nfaces].color.w=1-matlib[faces[a+nfaces].texpic].transparency;
		faces[a+nfaces].emmradius=lightradius*matlib[faces[a+nfaces].texpic].self_illum;
	}

	if (m->vertCol)
	{
		if (vertcolor==0)
		{
			vertcolor=new vector[tot_vert];
			for( i=0;i<tot_vert;i++ )
				vertcolor[i].vec(1,1,1);
		}
		for( i=0;i<m->numCVerts;i++ )
		{
			vertcolor[i+nvert].x=m->vertCol[i].x;
			vertcolor[i+nvert].y=m->vertCol[i].y;
			vertcolor[i+nvert].z=m->vertCol[i].z;
		}
	}

	nfaces+=m->numFaces;
	nvert+=m->numVerts;	
}

int enum_scene::callback(INode *node)
{
	Object *obj = node->EvalWorldState(time).obj;

	if(obj->ClassID()==Class_ID(SPLINE3D_CLASS_ID,0))
	{
		if (saveobj)
		{
		char *name=node->GetName();
		char filename[256];
		ShapeObject *s=(ShapeObject *)obj;
		if (s->CanMakeBezier())
			{
			Matrix3 piv(1);
			piv.PreTranslate(node->GetObjOffsetPos());
			PreRotateMatrix(piv, node->GetObjOffsetRot());
			ApplyScaling(piv, node->GetObjOffsetScale());
			Matrix3 tm=node->GetObjectTM(time);
			Point3 pos=tm.GetTrans();
			float fac=(float)GetMasterScale(UNITS_CENTIMETERS)/10;

			BezierShape shape;
			s->MakeBezier(time,shape);
			strcpy(filename,"objects/");
			strcat(filename,name);
			strcat(filename,".bez");
			int i,j;
			Point3 p;
			FILE *fp=fopen(filename,"wt");
			if (fp)
				{
				p.x=0; p.y=0; p.z=0;
				p=((p*Inverse(piv))*tm)*fac;
				fprintf(fp,"%f %f %f\n\n",p.x,p.y,p.z);
				shape.splines[0]->ComputeBezPoints();
				j=shape.splines[0]->KnotCount();
				fprintf(fp,"3 %i\n\n",j*3-2);
				for( i=0;i<j;i++ )
					{
					if (i>0)
						{
						p=shape.splines[0]->GetVert(i*3);
						p=((p*piv)*tm-pos)*fac;
						fprintf(fp,"\t%f\t%f\t%f\n",p.x,p.y,p.z);
						}
					p=shape.splines[0]->GetVert(i*3+1);
					p=((p*piv)*tm-pos)*fac;
					fprintf(fp,"\t%f\t%f\t%f\n",p.x,p.y,p.z);
					if (i<j-1)
						{
						p=shape.splines[0]->GetVert(i*3+2);
						p=((p*piv)*tm-pos)*fac;
						fprintf(fp,"\t%f\t%f\t%f\n",p.x,p.y,p.z);
						}
					}
				fclose(fp);
				}
			}
		}
	}
	else
	if (obj->CanConvertToType(FLYFAO_CLASS_ID))
	{
		if (saveobj)
		{
		Flyfao *ff=(Flyfao *)obj;
		char *name=node->GetName();
		char filename[256];
		char skin[256]="";
		strcpy(filename,"objects/");
		strcat(filename,name);
		strcat(filename,".fao");

		Matrix3 piv(1);
		piv.PreTranslate(node->GetObjOffsetPos());
		PreRotateMatrix(piv, node->GetObjOffsetRot());
		ApplyScaling(piv, node->GetObjOffsetScale());
		Matrix3 tm=node->GetObjectTM(time);
		Point3 pos=tm.GetTrans();
/*
		int i,j=ff->nverts*ff->nkeys;
		float *tmp=new float[j*3],*t;
		Point3 *p1=(Point3 *)tmp,p2;
		memcpy(tmp,ff->verts,sizeof(float)*j*3);
		for( i=0;i<j;i++,p1++ )
			{
			p2=*p1*piv;
			p2=p2*tm;
			p2=p2-pos;
			*p1=p2;
			}
		t=ff->verts;
		ff->verts=tmp;
*/
		Mtl *m=node->GetMtl();
		if(m && m->ClassID()==Class_ID(DMTL_CLASS_ID,0))
			{
			StdMat *std=(StdMat *)m;
			Texmap *tx=std->GetSubTexmap(ID_DI);
			if(tx!=NULL && tx->ClassID()==Class_ID(BMTEX_CLASS_ID,0))
				{
				BitmapTex *bmt=(BitmapTex*)tx;
				char str[256];
				strcpy(str,bmt->GetMapName());
				if (strrchr(str,'\\'))
					strcpy(skin,strrchr(str,'\\')+1);
				else if (strrchr(str,'/'))
					strcpy(skin,strrchr(str,'/')+1);
				else strcpy(skin,str);
				}
			}
		ff->save_fao(filename,skin,pos);
/*		
		ff->verts=t;
		delete tmp;
*/		}
	}
	else
	if(obj->CanConvertToType(triObjectClassID))
	{
		char *name=node->GetName();
		if (name[0]=='#')
		{
			if (saveobj)
			{
			Matrix3 piv(1);
			piv.PreTranslate(node->GetObjOffsetPos());
			PreRotateMatrix(piv, node->GetObjOffsetRot());
			ApplyScaling(piv, node->GetObjOffsetScale());

			Matrix3 tm=node->GetObjectTM(time);
			Point3 pos=tm.GetTrans();

			Save3DS(&((TriObject *)obj->ConvertToType(time, triObjectClassID))->mesh,
				&name[1],
				AddMtl(node->GetMtl()),
				tm,pos,piv);
			}
		}
		else if (savebsp)
		{
			TriObject *obj3=(TriObject *)obj->ConvertToType(time, triObjectClassID);
			if (obj3)
			AddMesh(
				&obj3->mesh,
				name,
				AddMtl(node->GetMtl()),
				node->GetNodeTM(time));
		}

		return TREE_CONTINUE;
	}
	
	if(!node->IsTarget())
	{
		switch(obj->SuperClassID())
		{ 
		case LIGHT_CLASS_ID:
			if(obj->ClassID()==Class_ID(OMNI_LIGHT_CLASS_ID,0))
				AddLight(
					(GenLight *)obj,
					node->GetNodeTM(0));
			break;
		}
	}
	return TREE_CONTINUE;
}

int enum_scene_count::callback(INode *node)
{
	Object *obj = node->EvalWorldState(time).obj;

	if(obj->CanConvertToType(triObjectClassID))
	{
		char *name=node->GetName();
		if (name[0]!='#')
		{
			TriObject *obj3=(TriObject *)obj->ConvertToType(time, triObjectClassID);
			if (obj3)
			{
				tot_vert+=obj3->mesh.numVerts;
				tot_face+=obj3->mesh.numFaces;
			}
		}
	}
	
	return TREE_CONTINUE;
}
