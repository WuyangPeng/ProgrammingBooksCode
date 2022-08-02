#include "..\..\lib\Fly3D.h"
#include "gamelib.h"

void subdiv_mesh::init()
{
	subdiv();
}

void subdiv_mesh::draw()
{
	if (divmesh)
	{
		if (flyengine->hwlights)
			{
			divmesh->color.vec(1,1,1,1);
			dynlights.init_draw(this);
			}
		else if (node)
			{
			divmesh->color=node->color+dynlight;
			dynlight.null();
			}
		glPushMatrix();
		glTranslatef(pos.x,pos.y,pos.z);
		glMultMatrixf((float *)&mat);
		divmesh->draw();
		glPopMatrix();
		if (flyengine->hwlights)
			dynlights.end_draw();
	}
}

bsp_object *subdiv_mesh::clone()
{
	subdiv_mesh *tmp=new subdiv_mesh;
	*tmp=*this;
	tmp->source=this;
	return tmp;
}

int subdiv_mesh::get_custom_param_desc(int i,param_desc *pd)
{
	if (pd!=0)
	switch(i)
	{
	case 0:
		pd->type='3';
		pd->data=&basemesh;
		strcpy(pd->name,"basemesh");
		break;
	case 1:
		pd->type='i';
		pd->data=&nsubdiv;
		strcpy(pd->name,"nsubdiv");
		break;
	case 2:
		pd->type='i';
		pd->data=&mode;
		strcpy(pd->name,"mode");
		break;
	}
	return 3;
}

int subdiv_mesh::message(vector& p,float rad,int msg,int param,void *data)
{
	if (msg==FLYOBJM_CHANGEPARAM && param>=0)
		init();
	else
	if (flyengine->hwlights)
		if (msg==FLYOBJM_ILLUM || msg==FLYOBJM_DYNILLUM)
			dynlights.add_light(p,*((vector *)data),rad);
		else ;
	else if (msg==FLYOBJM_ILLUM)
	{
		float fac=(p-pos).length()/rad;
		if (fac<1.0f)
			dynlight+=*((vector *)data)*(1.0f-fac);
	}

	return 0;
}

void subdiv_mesh::reset()
{
	if (divmesh) delete divmesh; 
	if (edges) delete edges;
	if (edgefaces) delete edgefaces;
	divmesh=0;
	edges=0;
	edgefaces=0;
	nedges=0;
}

void subdiv_mesh::subdiv()
{
	reset();
	if (source==0 || basemesh==0)
		return;

	int i; 
	mesh *m1,*m2;
	m1=basemesh->clone();
	pos=basemesh->pivotpos;

	// for each subdiv step, subdivide mesh m1 into mesh m2
	for( i=0;i<nsubdiv;i++ )
	{
	reset();
	// create mesh
	m2=new mesh;
	// lists all edges for mesh m1
	build_edge_list(m1); 
	// add one vertex at each edge in mesh m2
	add_vertices(m1,m2);
	// add 3 faces at each original face
	add_faces(m1,m2);	 

	// delete mesh m1 and replace it with mesh m2
	delete m1;
	m1=m2;
	}

	// store last subdivided mesh
	divmesh=m1;
	// compute mesh normals
	divmesh->compute_normals(MESH_FACENORM|MESH_VERTNORM|MESH_BBOX);
}

int subdiv_mesh::get_edge(int v1,int v2)
{
	// returns index into edges list for edge (v1,v2)
	int i;
	for( i=0;i<nedges;i++ )
		if ((edges[i*2]==v1 && edges[i*2+1]==v2) ||
			(edges[i*2+1]==v1 && edges[i*2]==v2))
			break;
	if (i==nedges)
		return -1;
	return i;
}

int subdiv_mesh::get_valence(int v1)
{
	// returns the number of edges using vertex v1
	int i,count=0;
	for( i=0;i<nedges;i++ )
		if (edges[i*2]==v1 || edges[i*2+1]==v1)
			count++;
	return count;
}

void subdiv_mesh::build_edge_list(mesh *m1)
{
	// build the edges list adding all edges from 
	// all faces (faces can share edges)
	int i,j;
	for( i=0;i<m1->nf;i++ )
		for( j=0;j<3;j++ )
			add_edge(
				m1->localfaces[i].vert[j]-m1->vert,
				m1->localfaces[i].vert[(j+1)%3]-m1->vert,
				i);
}

void subdiv_mesh::add_edge(int v1,int v2,int f)
{
	// adds a new edge to the edges list

	int i=get_edge(v1,v2);
	if (i>=0)
		// edge already exists, just store face index
		edgefaces[i*2+1]=f;
	else
	{
	// add two new entries to the lists
	int *tmp;
	tmp=new int [nedges*2+2];
	memcpy(tmp,edges,sizeof(int)*2*nedges);
	if (edges) delete edges;
	edges=tmp;
	tmp=new int [nedges*2+2];
	memcpy(tmp,edgefaces,sizeof(int)*2*nedges);
	if (edgefaces) delete edgefaces;
	edgefaces=tmp;

	// store edge and face
	edges[nedges*2]=v1;
	edges[nedges*2+1]=v2;
	edgefaces[nedges*2]=f;
	edgefaces[nedges*2+1]=-1;
	nedges++;
	}
}

void subdiv_mesh::add_vertices(mesh *m1,mesh *m2)
{
	int a,i,j,k,n,v0[2],v1[2],v2[4],e[4],f0[2],f1[4],valence[2];

	// alloc vertices for destination mesh m2
	m2->nv=nedges + m1->nv;
	m2->set_numverts(m2->nv);
	// copy mesh m1 vertices into mesh m2
	memcpy(m2->vert,m1->vert,sizeof(vector)*m1->nv);

	// for all edges from mesh m1
	for( i=0;i<nedges;i++ )
	{
		// find the edge vertices
		v0[0]=edges[i*2];
		v0[1]=edges[i*2+1];
		// find the faces sharing this edge
		f0[0]=edgefaces[i*2];
		f0[1]=edgefaces[i*2+1];

		// place vertex in the center of the edge
		m2->vert[m1->nv+i]=(m1->vert[v0[0]]+m1->vert[v0[1]])*0.5f;

		if (mode)
		{
		valence[0]=get_valence(v0[0]);
		valence[1]=get_valence(v0[1]);
		if (valence[0]<5 || valence[1]<5)
			{
			vector disp[2];
			for( j=0;j<2;j++ )
				if (valence[j]==3 || valence[j]==4)
				{
					disp[j]=m1->vert[v0[j]]*(3.0f/4.0f);
					n=0;
					if (valence[j]==3)
					{
						 for( k=0;k<nedges;k++ )
							 if (edges[k*2]==v0[j] || edges[k*2+1]==v0[j])
							 {
								 if (edges[k*2]==v0[j])
									 a=edges[k*2+1];
								 else a=edges[k*2];
								 if (a==v0[!j])
									 disp[j]+=m1->vert[a]*(5.0f/12.0f);
								 else 
									 disp[j]-=m1->vert[a]*(1.0f/12.0f);
								 n++;
								 if (n==3)
									 break;
							 }
					 }
					 else
					 {
						int vv[4];
						for( k=0;k<nedges;k++ )
						if (edges[k*2]==v0[j] || edges[k*2+1]==v0[j])
						{
							if (edges[k*2]==v0[j])
								vv[n++]=edges[k*2+1];
							else vv[n++]=edges[k*2];
							if (n==4)
								break;
						}

						if (f0[1]==-1)
						{
							continue;
							// -1/16 9/16 9/16 -1/16
						}
						else
						{
							for( k=0;k<4;k++ )
								if (vv[k]==v0[!j])
									disp[j]+=m1->vert[vv[k]]*(3.0f/8.0f);
								else
								{
									for( a=0;a<3;a++ )
										if (vv[k]==m1->localfaces[f0[0]].vert[a]-m1->vert ||
											vv[k]==m1->localfaces[f0[1]].vert[a]-m1->vert)
											break;
									if (a==3)
										disp[j]-=m1->vert[vv[k]]*(1.0f/8.0f);
								}
						}
					 }
				}

			if ((valence[0]==3 || valence[0]==4)&&
				(valence[1]==3 || valence[1]==4))
				m2->vert[m1->nv+i]=(disp[0]+disp[1])*0.5;
			else if (valence[0]==3 || valence[0]==4)
					m2->vert[m1->nv+i]=disp[0];
			else if (valence[1]==3 || valence[1]==4)
					m2->vert[m1->nv+i]=disp[1];

			continue;
			}
		}

		if (f0[1]==-1)
			continue;

		// compute the two v1 vertices
		v1[0]=v1[1]=-1;
		for( j=0;j<2;j++ )
			for( k=0;k<3;k++ )
			{
			a=m1->localfaces[f0[j]].vert[k]-m1->vert;
			if (a!=v0[0] && a!=v0[1])
				{
				v1[j]=a;
				break;
				}
			}

		// compute the four e edges
		e[0]=get_edge(v0[0],v1[0]);
		e[1]=get_edge(v0[0],v1[1]);
		e[2]=get_edge(v0[1],v1[0]);
		e[3]=get_edge(v0[1],v1[1]);
		if (e[0]==-1 || e[1]==-1 || e[2]==-1 || e[3]==-1)
			continue;
 
		// compute the four f faces
		for( j=0;j<4;j++ )
			if (edgefaces[e[j]*2]!=edgefaces[i*2] && 
				edgefaces[e[j]*2]!=edgefaces[i*2+1])
				f1[j]=edgefaces[e[j]*2];
			else f1[j]=edgefaces[e[j]*2+1];
		if (f1[0]==-1 || f1[1]==-1 || f1[2]==-1 || f1[3]==-1)
			continue;

		// compute the four v2 vertices
		v2[0]=v2[1]=v2[2]=v2[3]=-1;
		for( j=0;j<4;j++ )
		for( k=0;k<3;k++ )
			{
			a=m1->localfaces[f1[j]].vert[k]-m1->vert;
			if (a!=edges[e[j]*2] && a!=edges[e[j]*2+1])
				{
				v2[j]=a;
				break;
				}
			}
		if (v2[0]==-1 || v2[1]==-1 || v2[2]==-1 || v2[3]==-1)
			continue;
		
		// move vertex based on v1 and v2 and subdivfactor
		m2->vert[m1->nv+i]+=
			(m1->vert[v1[0]]+m1->vert[v1[1]])*(1.0f/8.0f)+
			(m1->vert[v2[0]]+m1->vert[v2[1]]+m1->vert[v2[2]]+m1->vert[v2[3]])*(-1.0f/16.0f);
	}
}

void subdiv_mesh::add_faces(mesh *m1,mesh *m2)
{
	int i,j,k,e[3];
	float euv[3][2];

	// alloc faces for destination mesh m2
	m2->nf=m1->nf*4;
	m2->set_numfaces(m2->nf,1);
	for( i=0;i<m2->nf;i++ )
		m2->faces[i]=&m2->localfaces[i];

	// for all faces in m1
	for( i=j=0;i<m1->nf;i++ )
	{
	// find edges for mesh m1 face i and 
	// compute the face edges center texture coordinates
	for( k=0;k<3;k++ )
		{
		e[k]=get_edge(
			m1->localfaces[i].vert[k]-m1->vert,
			m1->localfaces[i].vert[(k+1)%3]-m1->vert);
		euv[k][0]=0.5f*(m1->localfaces[i].uv[k][0]+m1->localfaces[i].uv[(k+1)%3][0]);
		euv[k][1]=0.5f*(m1->localfaces[i].uv[k][1]+m1->localfaces[i].uv[(k+1)%3][1]);
		}

	// create face f1
	m2->localfaces[j]=m1->localfaces[i];
	m2->localfaces[j].vert[0]=&m2->vert[m1->localfaces[i].vert[0]-m1->vert];
	m2->localfaces[j].vert[1]=&m2->vert[e[0]+m1->nv];
	m2->localfaces[j].vert[2]=&m2->vert[e[2]+m1->nv];
	m2->localfaces[j].uv[1][0]=euv[0][0];
	m2->localfaces[j].uv[1][1]=euv[0][1];
	m2->localfaces[j].uv[2][0]=euv[2][0];
	m2->localfaces[j].uv[2][1]=euv[2][1];
	j++;

	// create face f2
	m2->localfaces[j]=m1->localfaces[i];
	m2->localfaces[j].vert[0]=&m2->vert[e[0]+m1->nv];
	m2->localfaces[j].vert[1]=&m2->vert[m1->localfaces[i].vert[1]-m1->vert];
	m2->localfaces[j].vert[2]=&m2->vert[e[1]+m1->nv];
	m2->localfaces[j].uv[0][0]=euv[0][0];
	m2->localfaces[j].uv[0][1]=euv[0][1];
	m2->localfaces[j].uv[2][0]=euv[1][0];
	m2->localfaces[j].uv[2][1]=euv[1][1];
	j++;

	// create face f3
	m2->localfaces[j]=m1->localfaces[i];
	m2->localfaces[j].vert[0]=&m2->vert[e[2]+m1->nv];
	m2->localfaces[j].vert[1]=&m2->vert[e[1]+m1->nv];
	m2->localfaces[j].vert[2]=&m2->vert[m1->localfaces[i].vert[2]-m1->vert];
	m2->localfaces[j].uv[0][0]=euv[2][0];
	m2->localfaces[j].uv[0][1]=euv[2][1];
	m2->localfaces[j].uv[1][0]=euv[1][0];
	m2->localfaces[j].uv[1][1]=euv[1][1];
	j++;

	// create face f4
	m2->localfaces[j]=m1->localfaces[i];
	m2->localfaces[j].vert[0]=&m2->vert[e[0]+m1->nv];
	m2->localfaces[j].vert[1]=&m2->vert[e[1]+m1->nv];
	m2->localfaces[j].vert[2]=&m2->vert[e[2]+m1->nv];
	m2->localfaces[j].uv[0][0]=euv[0][0];
	m2->localfaces[j].uv[0][1]=euv[0][1];
	m2->localfaces[j].uv[1][0]=euv[1][0];
	m2->localfaces[j].uv[1][1]=euv[1][1];
	m2->localfaces[j].uv[2][0]=euv[2][0];
	m2->localfaces[j].uv[2][1]=euv[2][1];
	j++;
	}
}

