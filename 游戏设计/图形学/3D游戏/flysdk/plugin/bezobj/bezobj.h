enum classes_types
{
	TYPE_BEZIER_EXTRUDE=0x130,
	TYPE_BEZIER_LOFT,
	TYPE_BEZIER_SURFACE,
};

#define MAX_CURVE_VERTS 64
#define MAX_CURVE_LMPIXELS 32

class bezier_extrude : public bsp_object
{
public:

	bezier_curve *curve;
	mesh *objmesh;
	stripfan_mesh *sfmesh;

	float width;
	int strippic,fanpic;
	float tileu,tilev,tilew;
	int lm[3];

	void build_stripfan();
	int step(int dt) { return 0; };
	void draw();
	int get_custom_param_desc(int i,param_desc *pd);
	int message(vector& p,float rad,int msg,int param,void *data);
	void illuminate_edge(vector& p,float rad,vector& color,int shadows);
	void init();
	bsp_object *clone();
	mesh *get_mesh() { return objmesh; };

	bezier_extrude() 
	{ 
		type=TYPE_BEZIER_EXTRUDE; 
		objmesh=0;
		sfmesh=0;
	};
	~bezier_extrude() 
	{ 
		if (objmesh) delete objmesh;
		if (sfmesh) delete sfmesh;
	};
};

class bezier_loft : public bsp_object
{
public:

	bezier_curve *shape,*path;
	bezier_patch patch;
	mesh *objmesh;
	stripfan_mesh *sfmesh;

	int texpic,lm;
	float tileu,tilev;

	int create_normal_map(float scale);
	void build_stripfan();
	int step(int dt) { return 0; };
	void draw();
	int get_custom_param_desc(int i,param_desc *pd);
	int message(vector& p,float rad,int msg,int param,void *data);
	void init();
	bsp_object *clone();
	mesh *get_mesh() { return objmesh; };
	void illuminate_patch(vector& p,float rad,vector& color,int shadows);

	bezier_loft() 
	{ 
		type=TYPE_BEZIER_LOFT; 
		objmesh=0;
		sfmesh=0;
	};
	~bezier_loft() 
	{ 
		if (objmesh) 
			delete objmesh;
	};
};

class bezier_surface : public bsp_object
{
public:
	bezier_patch *patch;
	mesh *objmesh;
	
	int step(int dt) { return 0; };
	mesh *get_mesh() { return objmesh; };
	void draw();
	void init();
	void build_stripfan();
	int get_custom_param_desc(int i,param_desc *pd);
	int message(vector& p,float rad,int msg,int param,void *data);
	void illuminate_patch(vector& p,float rad,vector& color,int shadows);
	bsp_object *clone();

	bezier_surface() 
	{ 
		type=TYPE_BEZIER_SURFACE;
		objmesh=0;
	};
	~bezier_surface() 
	{ 
		if (objmesh)
			delete objmesh;
	}
};

class bezier_extrude_desc : public class_desc
{
public:
	void *create() { return new bezier_extrude; };
	char *get_name() { return "bezextrude"; };
	int get_type() { return TYPE_BEZIER_EXTRUDE; };
};

class bezier_loft_desc : public class_desc
{
public:
	void *create() { return new bezier_loft; };
	char *get_name() { return "bezloft"; };
	int get_type() { return TYPE_BEZIER_LOFT; };
};

class bezier_surface_desc : public class_desc
{
public:
	void *create() { return new bezier_surface; };
	char *get_name() { return "bezsurface"; };
	int get_type() { return TYPE_BEZIER_SURFACE; };
};

