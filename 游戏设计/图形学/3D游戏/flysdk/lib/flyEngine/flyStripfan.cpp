#include "..\..\lib\Fly3D.h"

void stripfan_mesh::reset()
{
	if (stripfandata) delete stripfandata;
	if (vertdata) delete vertdata;
	nstripfan=0;
	stripfandata=0;
	vertdata=0;
	nvert=0;
}

void stripfan_mesh::draw(int mode)
{
	int i,j,k,n,mapcount=0;
	if (nstripfan)
	if (flyengine->multitexture && ntextureunits>1 && flyengine->nlm)
		{
		k=0;
		for( i=0;i<nstripfan;i+=3 )
			{
			tc->use(stripfandata[i+1]);
			if (stripfandata[i+2]!=-1)
				tc->use(flyengine->lm[stripfandata[i+2]]->pic+flyengine->lmbase,1);
			else 
				tc->use(-1,1);
			n=abs(stripfandata[i]);
			if (stripfandata[i]>0)
				glBegin(GL_TRIANGLE_STRIP);
			else 
				glBegin(GL_TRIANGLE_FAN);
			for( j=0;j<n;j++,k++ )
				{
				glMultiTexCoord2fvARB(GL_TEXTURE0_ARB,&vertdata[k].u);
				glMultiTexCoord2fvARB(GL_TEXTURE1_ARB,&vertdata[k].ul);
				glVertex3fv(&vertdata[k].pos.x);
				}
			glEnd();
			}
		tc->use(-1,1);
		tc->use(-1,0);
		mapcount+=2;
		}
	else
		{
		if (mode&MAPPING_TEXTURE &&
			flyengine->mapmode&MAPPING_TEXTURE)
			{
			k=0;
			for( i=0;i<nstripfan;i+=3 )
				{
				tc->use(stripfandata[i+1]);
				n=abs(stripfandata[i]);
				if (stripfandata[i]>0)
					glBegin(GL_TRIANGLE_STRIP);
				else 
					glBegin(GL_TRIANGLE_FAN);
				for( j=0;j<n;j++,k++ )
					{
					glTexCoord2fv(&vertdata[k].u);
					glVertex3fv(&vertdata[k].pos.x);
					}
				glEnd();
				}
			mapcount++;
			}

		if (mode&MAPPING_DETAIL &&
			flyengine->mapmode&MAPPING_DETAIL &&
			flyengine->detailpic!=-1)
			{
			if (mapcount)
				{
				glBlendFunc(GL_ZERO,GL_SRC_COLOR);
				glDepthMask(GL_FALSE);
				glDepthFunc(GL_EQUAL);
				}
			k=0;
			tc->use(flyengine->detailpic);
			for( i=0;i<nstripfan;i+=3 )
				{
				n=abs(stripfandata[i]);
				if (stripfandata[i]>0)
					glBegin(GL_TRIANGLE_STRIP);
				else 
					glBegin(GL_TRIANGLE_FAN);
				for( j=0;j<n;j++,k++ )
					{
					glTexCoord2f(
						vertdata[k].u*flyengine->detailtile,
						vertdata[k].v*flyengine->detailtile);
					glVertex3fv(&vertdata[k].pos.x);
					}
				glEnd();
				}
			mapcount++;
			}

		if (mode&MAPPING_LIGHTMAP &&
			flyengine->mapmode&MAPPING_LIGHTMAP &&
			flyengine->nlm!=0)
			{
			if (mapcount)
				{
				glBlendFunc(GL_ZERO,GL_SRC_COLOR);
				glDepthMask(GL_FALSE);
				glDepthFunc(GL_EQUAL);
				}
			k=0;
			for( i=0;i<nstripfan;i+=3 )
				{
				if (stripfandata[i+2]==-1)
					{
					k+=n;
					continue;
					}
				else tc->use(flyengine->lm[stripfandata[i+2]]->pic+flyengine->lmbase);
				n=abs(stripfandata[i]);
				if (stripfandata[i]>0)
					glBegin(GL_TRIANGLE_STRIP);
				else 
					glBegin(GL_TRIANGLE_FAN);
				for( j=0;j<n;j++,k++ )
					{
					glTexCoord2fv(&vertdata[k].ul);
					glVertex3fv(&vertdata[k].pos.x);
					}
				glEnd();
				}
			mapcount++;
			}
		}

	if (mode&MAPPING_FOGMAP &&
		flyengine->mapmode&MAPPING_FOGMAP &&
		flyengine->nlm!=0)
		{
		if (mapcount)
			{
			glDepthMask(GL_FALSE);
			glDepthFunc(GL_EQUAL);
			glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
			}
		k=0;
		for( i=0;i<nstripfan;i+=3 )
			{
			if (stripfandata[i+2]==-1)
				{
				k+=n;
				continue;
				}
			else tc->use(stripfandata[i+2]+flyengine->fmbase);
			n=abs(stripfandata[i]);
			if (stripfandata[i]>0)
				glBegin(GL_TRIANGLE_STRIP);
			else 
				glBegin(GL_TRIANGLE_FAN);
			for( j=0;j<n;j++,k++ )
				{
				glTexCoord2fv(&vertdata[k].ul);
				glVertex3fv(&vertdata[k].pos.x);
				}
			glEnd();
			}
		mapcount++;
		}

	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LESS);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

mesh *stripfan_mesh::build_mesh()
{
	int i,j,k=0,v=0,f=0,n;
	mesh *objmesh=new mesh;
	for( i=0;i<nstripfan;i+=3 )
	{
		objmesh->nf+=abs(stripfandata[i])-2;
		objmesh->nv+=abs(stripfandata[i]);
	}
	objmesh->faces=new face *[objmesh->nf];
	objmesh->localfaces=new face [objmesh->nf];
	objmesh->vert=new vector[objmesh->nv];
	objmesh->color.vec(1.0f,1.0f,1.0f);
	for( i=0;i<objmesh->nf;i++ )
		objmesh->faces[i]=&objmesh->localfaces[i];
	for( i=0;i<nstripfan;i+=3 )
	{
		n=abs(stripfandata[i]);
		if (stripfandata[i]>0)
		{
			for( j=2;j<n;j++ )
			{
				objmesh->localfaces[f].color.vec(1.0f,1.0f,1.0f,1.0f);
				objmesh->localfaces[f].texpic=stripfandata[i+1];
				objmesh->localfaces[f].lm=stripfandata[i+2];
				if (j&1)
					{
					objmesh->localfaces[f].vert[0]=&objmesh->vert[v+j-1];
					objmesh->localfaces[f].vert[1]=&objmesh->vert[v+j-2];
					objmesh->localfaces[f].lmuv[0][0]=vertdata[k+j-1].ul;
					objmesh->localfaces[f].lmuv[0][1]=vertdata[k+j-1].vl;
					objmesh->localfaces[f].lmuv[1][0]=vertdata[k+j-2].ul;
					objmesh->localfaces[f].lmuv[1][1]=vertdata[k+j-2].vl;
					}
				else
					{
					objmesh->localfaces[f].vert[0]=&objmesh->vert[v+j-2];
					objmesh->localfaces[f].vert[1]=&objmesh->vert[v+j-1];
					objmesh->localfaces[f].lmuv[0][0]=vertdata[k+j-2].ul;
					objmesh->localfaces[f].lmuv[0][1]=vertdata[k+j-2].vl;
					objmesh->localfaces[f].lmuv[1][0]=vertdata[k+j-1].ul;
					objmesh->localfaces[f].lmuv[1][1]=vertdata[k+j-1].vl;
					}
				objmesh->localfaces[f].vert[2]=&objmesh->vert[v+j];
				objmesh->localfaces[f].lmuv[2][0]=vertdata[k+j].ul;
				objmesh->localfaces[f].lmuv[2][1]=vertdata[k+j].vl;
				f++;
			}
		}
		else
		{
			for( j=2;j<n;j++ )
			{
				objmesh->localfaces[f].color.vec(1.0f,1.0f,1.0f,1.0f);
				objmesh->localfaces[f].texpic=stripfandata[i+1];
				objmesh->localfaces[f].lm=stripfandata[i+2];
				objmesh->localfaces[f].vert[0]=&objmesh->vert[v];
				objmesh->localfaces[f].vert[1]=&objmesh->vert[v+j-1];
				objmesh->localfaces[f].vert[2]=&objmesh->vert[v+j];
				objmesh->localfaces[f].lmuv[0][0]=vertdata[k].ul;
				objmesh->localfaces[f].lmuv[0][1]=vertdata[k].vl;
				objmesh->localfaces[f].lmuv[1][0]=vertdata[k+j-1].ul;
				objmesh->localfaces[f].lmuv[1][1]=vertdata[k+j-1].vl;
				objmesh->localfaces[f].lmuv[2][0]=vertdata[k+j].ul;
				objmesh->localfaces[f].lmuv[2][1]=vertdata[k+j].vl;
				f++;
			}
		}
		for( j=0;j<n;j++ )
		{
			objmesh->vert[v].x=vertdata[k].pos.x;
			objmesh->vert[v].y=vertdata[k].pos.y;
			objmesh->vert[v].z=vertdata[k].pos.z;
			v++; k++;
		}
	}
	objmesh->compute_normals(MESH_FACENORM|MESH_VERTNORM|MESH_BBOX);
	return objmesh;
}

vertex *stripfan_mesh::add_stripfan(int nv,int texpic,int lmpic)
{
	int *tmp1=new int[nstripfan+3];
	if (stripfandata)
	{
		memcpy(tmp1,stripfandata,sizeof(int)*nstripfan);
		delete stripfandata;
	}
	stripfandata=tmp1;

	stripfandata[nstripfan++]=nv;
	stripfandata[nstripfan++]=texpic;
	stripfandata[nstripfan++]=lmpic;

	nv=abs(nv);
	vertex *tmp2=new vertex[nvert+nv];
	if (vertdata)
	{
		memcpy(tmp2,vertdata,sizeof(vertex)*nvert);
		delete vertdata;
	}
	vertdata=tmp2;

	memset(&vertdata[nvert],0,sizeof(vertex)*nv);

	nvert+=nv;
	return &vertdata[nvert-nv];
}
