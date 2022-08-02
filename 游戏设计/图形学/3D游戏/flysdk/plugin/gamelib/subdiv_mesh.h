class subdiv_mesh : public bsp_object
{
public:
	subdiv_mesh() 
	{
		type=TYPE_SUBDIV_MESH; 
		divmesh=0; nedges=0; edges=0; edgefaces=0;
		dynlight.null();
	};
	~subdiv_mesh() { reset(); };

	// dynamic vertex light info
	light_vertex dynlights;	
	// dynamic constant light info
	vector dynlight;

	int nsubdiv;	// num subdivisions
	int mode;		// mode: 0-standard 1-modified
	mesh* basemesh;	// base mesh
	mesh* divmesh;	// basemesh subdivided nsubdiv times

	int nedges;		// number of edges
	int *edges;		// edges array (2*nedges)
	int *edgefaces;	// faces array (2*nedges)
	
	void reset();	// reset allocated data
	void subdiv();	// subdiv mesh nsubdiv times

	// finds edge with vertices v1,v2
	int get_edge(int v1,int v2);
	// get valence for vertex v1
	int get_valence(int v1);

	// add all mesh edges to the edges array
	void build_edge_list(mesh *m1);
	// add a single edge to the edges array
	void add_edge(int v1,int v2,int f);	
	// add one vertex at m2 for each edge in m1
	void add_vertices(mesh *m1,mesh *m2);
	// add 4 faces in m2 for each face from m1
	void add_faces(mesh *m1,mesh *m2);

	void init();
	void draw();
	int step(int dt) { return 0; };
	mesh *get_mesh() { return divmesh; };
	int get_custom_param_desc(int i,param_desc *pd);
	bsp_object *clone();
	int message(vector& p,float rad,int msg,int param,void *data);
};

class subdiv_mesh_desc : public class_desc
{
public:
	void *create() { return new subdiv_mesh; };
	char *get_name() { return "subdiv_mesh"; };
	int get_type() { return TYPE_SUBDIV_MESH; };
};

