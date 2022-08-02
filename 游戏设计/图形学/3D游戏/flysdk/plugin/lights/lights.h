enum 
{
	TYPE_LIGHT=0x120,
	TYPE_SPOT_LIGHT,
	TYPE_SPRITE_LIGHT,
	TYPE_MESH_LIGHT,
};

class light;
class spot_light;
class sprite_light;
class mesh_light;

class light : public bsp_object
{
	public:

		vector color;
		float illum_radius;
		bsp_object *shadow_obj;
		sprite_light *s;
		float grow;
		int shadowmode;

	int step(int dt);
	void draw();
	int get_custom_param_desc(int i,param_desc *pd);

	inline bsp_object *clone() 
	{ 
		light *l=new light;
		*l=*this;
		l->source=this;
		return l; 
	};

	light() { type=TYPE_LIGHT; };
};

class spot_light : public bsp_object
{
	public:

		float maxdist;
		vector color;
		light *l;

	spot_light() 
	{ type=TYPE_SPOT_LIGHT; };
	int get_custom_param_desc(int i,param_desc *pd);
	virtual void reposition(bsp_object *obj);

	inline bsp_object *clone() 
	{ 
		spot_light *l=new spot_light;
		*l=*this;
		l->source=this;
		return l; 
	};
};

class sprite_light : public bsp_object
{
	public:

		int texture;
		int mode;
		vector color;
		float size;
		float grow;

	int step(int dt);
	void draw();
	int get_custom_param_desc(int i,param_desc *pd);

	inline bsp_object *clone() 
	{ 
		sprite_light *l=new sprite_light;
		*l=*this;
		l->source=this;
		return l; 
	};
	sprite_light() { type=TYPE_SPRITE_LIGHT; }
};

class mesh_light : public bsp_object
{
	public:

		mesh *objmesh;
		float illum_radius;
		vector color;
		int halopic;
		float halosize;
		int lastdraw;

	int step(int dt);
	void draw();
	int get_custom_param_desc(int i,param_desc *pd);
	void init();
	mesh *get_mesh() { return objmesh; };
	int message(vector& p,float rad,int msg,int param,void *data);

	inline bsp_object *clone() 
	{ 
		mesh_light *l=new mesh_light;
		*l=*this;
		l->source=this;
		return l; 
	};
	mesh_light() { type=TYPE_MESH_LIGHT; color.vec(1,1,1,0); }
};

class light_desc : public class_desc
{
public:
	void *create() { return new light; };
	char *get_name() { return "light"; };
	int get_type() { return TYPE_LIGHT; };
};
class spot_light_desc : public class_desc
{
public:
	void *create() { return new spot_light; };
	char *get_name() { return "spotlight"; };
	int get_type() { return TYPE_SPOT_LIGHT; };
};
class sprite_light_desc : public class_desc
{
public:
	void *create() { return new sprite_light; };
	char *get_name() { return "spritelight"; };
	int get_type() { return TYPE_SPRITE_LIGHT; };
};
class mesh_light_desc : public class_desc
{
public:
	void *create() { return new mesh_light; };
	char *get_name() { return "meshlight"; };
	int get_type() { return TYPE_MESH_LIGHT; };
};
