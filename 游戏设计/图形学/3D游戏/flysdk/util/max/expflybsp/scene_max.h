class light_max
{
public:
	char name[256];
	int type;
	vector color,pos,target,dir;
	float hotspot,falloff;
};

class bsp_node_max : public bsp_node
{	
public:
	int nplanes,side;
	plane *planes;
	char *planeflags;
	boundbox bbox;

	bsp_node_max() 
	{ planes=0; nplanes=0; planeflags=0; };
	~bsp_node_max() 
	{ if (planes) delete planes; };

	void split_faces_aligned();
	void split_axis_aligned(int depth);
	void add_face(face *f,int planeflag);
	void free_faces();
	void print(FILE *fp,int& tot,int depth);

	int find_split_plane();
	int find_plane(vector& normal,float d0);
	int add_plane(vector& normal,float d0);
	void calc_bbox();
};

class scene_max : public flyEngine
{
public:
	void compute_scene_normals();
	int nmatlib;
	material *matlib;

	int nlights;
	light_max *lightlib;

	int nleaf;

	void build_bsptree();
	void enum_leaf(bsp_node *n);
	void compute_light();
	void save_map(char *);
	void save(char *);

	scene_max() 
		{ 
		lightlib=0; 
		nlights=0;
		matlib=new material;
		strcpy(matlib[0].name, "");
		matlib[0].ambient[0]=0;
		matlib[0].ambient[1]=0;
		matlib[0].ambient[2]=0;
		matlib[0].diffuse[0]=.5f;
		matlib[0].diffuse[1]=.5f;
		matlib[0].diffuse[2]=.5f;
		matlib[0].transparency=0;
		matlib[0].self_illum=0;
		nmatlib=1;
		};
	~scene_max() 
		{
		if (matlib) delete matlib; 
		if (lightlib) delete lightlib; 
		};
};
