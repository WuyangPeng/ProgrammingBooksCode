class dpblend_sphere : public bsp_object
{
public:
	dpblend_sphere() { type=TYPE_DPBLEND_SPHERE; lightdist=1e10; };

	vector ambient,diffuse;
	int pxlsize;
	int normalmap;
	int mode;

	vector lightpos;
	vector lightcolor;
	float lightradius;
	float lightdist;

	void build_normalmap(char *file);
	void init_combiners();

	void init();
	int step(int dt);
	void draw();
	int message(vector& p,float rad,int msg,int param,void *data);
	int get_custom_param_desc(int i,param_desc *pd);
	bsp_object *clone();
};

class dpblend_sphere_desc : public class_desc
{
public:
	void *create() { return new dpblend_sphere; };
	char *get_name() { return "dpblend_sphere"; };
	int get_type() { return TYPE_DPBLEND_SPHERE; };
};

