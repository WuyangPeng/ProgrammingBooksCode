class fao_mesh : public bsp_object
{
public:
	anim_mesh *o;
	int mode;
	int time;
	int delay;
	int wait;
	int timeactivate;
	vector dynlight;

	fao_mesh()
	{ 
		type=TYPE_FAO_MESH; 
		timeactivate=0; 
		dynlight.null();
	};

	mesh *get_mesh() { return o; };
	mesh *ray_intersect(vector& ro,vector& rd,vector& ip,float& dist,int &facenum,float rad);
	int step(int dt);
	void draw();
	int get_custom_param_desc(int i,param_desc *pd);
	void init();
	int message(vector& p,float rad,int msg,int param,void *data);
	inline bsp_object *clone()
	{ 
		fao_mesh *f=new fao_mesh;
		*f=*this;
		f->source=this;
		return f;
	}
};

class fao_mesh_desc : public class_desc
{
public:
	void *create() { return new fao_mesh; };
	char *get_name() { return "fao_mesh"; };
	int get_type() { return TYPE_FAO_MESH; };
};
