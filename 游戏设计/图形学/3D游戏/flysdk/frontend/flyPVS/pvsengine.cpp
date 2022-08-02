#include "../../lib/Fly3D.h"
#include "pvsengine.h"
#include "opengl.h"

extern int cur_side,savelog;
extern HDC hdc;
extern short **face_nodes;
extern char file[256];
extern float VOLUME_FACTOR;
char flypathname[256];

void pvsEngine::set_pvs_bit(int node1,int node2)
{
	*(pvs + node1*pvsrowsize + (node2>>3)) |= (1<<(node2&7));
}

int pvsEngine::get_pvs_bit(int node1,int node2)
{
	return PVS_TEST(node1,node2);
}

static_mesh *pvsEngine::get_object(bsp_node *n)
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

void pvsEngine::draw_bsp(bsp_node *n,vector& p,vector& z)
{
	if (n->leaf!=-1)
		{
		static_mesh *o=get_object(n);
		if (o==0)
			return;
		int i,j;
		for( i=0;i<o->objmesh->nf;i++)
			{
			if (o->objmesh->faces[i]->color.w<1.0f)
				{
				glEnd();
				glEnable(GL_POLYGON_STIPPLE);
				glBegin(GL_TRIANGLES);
				}

			j=o->objmesh->faces[i]->indx;
	
			//glColor3ub(j&255,(j>>8)&255,(j>>16)&255);
			glColor3ub( ((j&31)<<3)+7, (((j>>5)&31)<<3)+7, (((j>>10)&31)<<3)+7);

			glVertex3fv((float *)o->objmesh->faces[i]->vert[0]);
			glVertex3fv((float *)o->objmesh->faces[i]->vert[1]);
			glVertex3fv((float *)o->objmesh->faces[i]->vert[2]);

			if (o->objmesh->faces[i]->color.w<1.0f)
				{
				glEnd();
				glDisable(GL_POLYGON_STIPPLE);
				glBegin(GL_TRIANGLES);
				}
			}
		return;
		}

	float x,y;
	x=vec_dot(n->normal,z);
	y=(vec_dot(n->normal,p)+n->d0)/x;

	if (y>0)
		if(fabs(x)>0.7071)
		{
		if (x>0)
			if (n->child[0]) draw_bsp(n->child[0],p,z); else ;
		else 
			if (n->child[1]) draw_bsp(n->child[1],p,z); else ;
		return;
		}

	if (n->child[0]) draw_bsp(n->child[0],p,z);
	if (n->child[1]) draw_bsp(n->child[1],p,z);
}

void pvsEngine::render_hc_face(vector& p,vector& z,vector& u,char *buf)
{
    glLoadIdentity();
	gluLookAt( 
			p.x,p.y,p.z, 
			p.x+z.x, p.y+z.y, p.z+z.z, 
			u.x,u.y,u.z);

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glPolygonMode(GL_FRONT,GL_FILL);
	glBegin(GL_TRIANGLES);
	draw_bsp(bsp,p,z);
	glEnd();

	glReadPixels(0,0,screen_sx,screen_sy,GL_RGB,GL_UNSIGNED_BYTE,buf);
}

void pvsEngine::update_pvs(int node,char *buf)
{
	int i,j,indx1,indx2,indx3,t=screen_sx*(screen_sy-1)-1;
	unsigned char *b=(unsigned char *)buf;

	for( i=0;i<t;i++,b+=3 )
	{
//	indx=((unsigned)*b)+((unsigned)*(b+1)<<8)+((unsigned)*(b+2)<<16);

	indx1=((unsigned)*b>>3)+((unsigned)*(b+1)>>3<<5)+((unsigned)*(b+2)>>3<<10);
	indx2=((unsigned)*(b+3)>>3)+((unsigned)*(b+4)>>3<<5)+((unsigned)*(b+5)>>3<<10);
	indx3=((unsigned)*(b+screen_sx*3)>>3)+((unsigned)*(b+screen_sx*3+1)>>3<<5)+((unsigned)*(b+screen_sx*3+2)>>3<<10);

	if (indx1>=nfaces || indx1!=indx2 || indx1!=indx3)
		continue;

	for(j=0;j<face_nodes[indx1][0];j++)
		set_pvs_bit(node, face_nodes[indx1][j+1]);
	}
}

void pvsEngine::sample_node(bsp_node *n,vector& v)
{
	vector z,u;
	
	char *buf=new char[3*screen_sx*screen_sy];

	z.vec(0,0,1);
	u.vec(1,0,0);
	render_hc_face(v,z,u,buf);
	if (cur_side==0)	SwapBuffers(hdc);
	update_pvs(n->leaf,buf);

	z.vec(0,0,-1);
	u.vec(1,0,0);
	render_hc_face(v,z,u,buf);
	if (cur_side==1)	SwapBuffers(hdc);
	update_pvs(n->leaf,buf);

	z.vec(0,1,0);
	u.vec(1,0,0);
	render_hc_face(v,z,u,buf);
	if (cur_side==2)	SwapBuffers(hdc);
	update_pvs(n->leaf,buf);

	z.vec(0,-1,0);
	u.vec(1,0,0);
	render_hc_face(v,z,u,buf);
	if (cur_side==3)	SwapBuffers(hdc);
	update_pvs(n->leaf,buf);

	z.vec(1,0,0);
	u.vec(0,0,1);
	render_hc_face(v,z,u,buf);
	if (cur_side==4)	SwapBuffers(hdc);
	update_pvs(n->leaf,buf);

	z.vec(-1,0,0);
	u.vec(0,0,1);
	render_hc_face(v,z,u,buf);
	if (cur_side==5)	SwapBuffers(hdc);
	update_pvs(n->leaf,buf);
	
	delete buf;
}

int pvsEngine::get_node_random_point(int leafnum,vector& point)
{
	static_mesh *so=(static_mesh *)leaf[leafnum]->elem;
	boundbox bb=so->objmesh->bbox;
	int i,j=10000;
	for( i=0;i<j;i++ )
	{
		point.x =
			bb.min.x+
			FABSRAND*(bb.max.x-bb.min.x);
		point.y =
			bb.min.y+
			FABSRAND*(bb.max.y-bb.min.y);
		point.z =
			bb.min.z+
			FABSRAND*(bb.max.z-bb.min.z);
		bsp_node *n=find_node(bsp,point,NEAR_PLANE_THRESHOLD);
		if (n==leaf[leafnum])
			break;
	}
	if (i==j)
		return 0;
	return 1;
}

void pvsEngine::save_pvslog(char *f)
{
	FILE *fp=fopen(f,"wt");
	if (fp)
	{
		int i,j,k,t=0;

		fprintf(fp,"nodenum\tnfaces\tnsamp\tnvis\tbboxx\tbboxy\tbboxz\n");

		for( i=0;i<nleaf;i++ )
		{
			k=0;
			for( j=0;j<nleaf;j++ )
				if (PVS_TEST(i,j))
					k++;
			t+=k;

			static_mesh *so=(static_mesh *)leaf[i]->elem;
			if(so==0)
				fprintf(fp,"%i\n",i);
			else 
			{
				vector v=so->objmesh->bbox.max-so->objmesh->bbox.min;
				float vol=v.x*v.y*v.z;
				j=(int)(vol/VOLUME_FACTOR)+1;
				fprintf(fp,"%i\t%i\t%i\t%i\t%.1f\t%.1f\t%.1f\n",
					i,so->objmesh->nf,j,k,
				so->objmesh->bbox.max.x-so->objmesh->bbox.min.x,
				so->objmesh->bbox.max.y-so->objmesh->bbox.min.y,
				so->objmesh->bbox.max.z-so->objmesh->bbox.min.z);
			}
		}

		fprintf(fp,"\nTotal: %i nodes (%i%%)\n",nleaf,t*100/(nleaf*nleaf));

		fclose(fp);
	}
}

int pvsEngine::opendata(char *f) 
{
	char str[256];
	strcpy(flypathname,f);
	*(strrchr(flypathname,'\\')+1)=0;
	strcpy(file,strrchr(f,'\\')+1);
	*strchr(file,'.')=0;

	strcpy(str,flypathname);
	strcat(str,file);
	strcat(str,".bsp");
	if (load_bsp(str)==0)
		return 0;

	alloc_pvs(0);

	face_nodes=new short *[nfaces];

	int i, j, k;
	for( i=0;i<nfaces;i++ )
	{
		face_nodes[i]=new short;
		face_nodes[i][0]=0;
	}

	for( i=0;i<nleaf;i++ )
	{
		static_mesh *o=get_object(flyengine->leaf[i]);
		if(o)
			for(j=0;j<o->objmesh->nf;j++)
			{
				k=o->objmesh->faces[j]->indx;
				short *temp=new short[face_nodes[k][0]+2];
				memcpy(temp, face_nodes[k], sizeof(short)*(face_nodes[k][0]+1));
				delete face_nodes[k];
				face_nodes[k]=temp;
				face_nodes[k][face_nodes[k][0]+1]=i;
				face_nodes[k][0]++;
			}
	}

	return 1;
}

void pvsEngine::save()
{
	char str[256];

	strcpy(str,flypathname);
	strcat(str,file);
	strcat(str,".pvs");
	save_pvs(str);

	if (savelog)
	{
	strcpy(str,flypathname);
	strcat(str,file);
	strcat(str,".pvslog.txt");
	save_pvslog(str);
	}
}
