class exp_sphere : public bsp_object
{
public:
		vector color;
		float curradius;
		stripfan_mesh *sfmesh;

		void init();
		int step(int dt);
		void draw();
		int get_custom_param_desc(int i,param_desc *pd);
		int message(vector& p,float rad,int msg,int param,void *data);
		bsp_object *clone()
		{
		exp_sphere *tmp=new exp_sphere;
		*tmp=*this;
		tmp->source=this;
		return tmp;
		}

		exp_sphere()
		{ type=TYPE_EXP_SPHERE; sfmesh=0; };
		~exp_sphere()
		{ 
			if (source==0 && sfmesh) delete sfmesh; 
		};
};

class exp_sphere_desc : public class_desc
{
public:
	void *create() { return new exp_sphere; };
	char *get_name() { return "expsphere"; };
	int get_type() { return TYPE_EXP_SPHERE; };
};
