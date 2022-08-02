class cartoon_mesh : public bsp_object
{
public:
	cartoon_mesh() 
	{ type=TYPE_CARTOON_MESH; };

	mesh* objmesh;		// 3d mesh
	light_vertex lights;	// lights illuminating the object

	void init();
	void draw();
	int step(int dt) { return 0; };
	int get_custom_param_desc(int i,param_desc *pd);
	bsp_object *clone();
	int message(vector& p,float rad,int msg,int param,void *data);
	mesh *get_mesh() { return objmesh; };
};

class cartoon_mesh_desc : public class_desc
{
public:
	void *create() { return new cartoon_mesh; };
	char *get_name() { return "cartoon_mesh"; };
	int get_type() { return TYPE_CARTOON_MESH; };
};

