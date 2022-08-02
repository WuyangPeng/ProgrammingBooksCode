enum 
{
	TYPE_BLINK_LIGHT=100000,
	TYPE_BOUNCE_MESH,
};

class blink_light : public bsp_object
{
public:
	blink_light() { type=TYPE_BLINK_LIGHT; };

	vector color;
	float illumradius;
	int blinktime;

	int step(int dt);
	void draw();
	int get_custom_param_desc(int i,param_desc *pd);
	bsp_object *clone();
};

class blink_light_desc : public class_desc
{
public:
	void *create() { return new blink_light; };
	char *get_name() { return "blink_light"; };
	int get_type() { return TYPE_BLINK_LIGHT; };
};

class bounce_mesh : public bsp_object
{
public:
	bounce_mesh() { type=TYPE_BOUNCE_MESH; };

	// the obejct's mesh
	mesh *objmesh;

	// no step() defined, so it uses the partcile base class step

	// this will handle drawing and collision with the object
	mesh *get_mesh() { return objmesh; };

	int get_custom_param_desc(int i,param_desc *pd);
	bsp_object *clone();
};

class bounce_mesh_desc : public class_desc
{
public:
	void *create() { return new bounce_mesh; };
	char *get_name() { return "bounce_mesh"; };
	int get_type() { return TYPE_BOUNCE_MESH; };
};

