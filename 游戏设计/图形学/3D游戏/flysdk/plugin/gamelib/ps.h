class particle_system : public bsp_object
{
	public:

		vector color_new,colorvar_new;
		float bump_new,friction_new,radius_new,
			mass_new,gravity_new,speed_new,
			speed_var,ax,ay;
		int col_flag_new,texture_new;
		int emmtime,totpart,fadetime;
		
		int part0,part1;
		color_particle *part;
		
	int step(int dt);

	void draw();

	int get_custom_param_desc(int i,param_desc *pd);

	inline bsp_object *clone() 
	{ 
		particle_system *p=new particle_system;
		*p=*this;
		p->source=this;
		return p; 
	};

	particle_system()
	{
		type=TYPE_PARTICLE_SYSTEM;
		part=0;
	}
	~particle_system()
	{
		if (part)
			delete part;
	}
};

class ps_desc : public class_desc
{
public:
	void *create() { return new particle_system; };
	char *get_name() { return "ps"; };
	int get_type() { return TYPE_PARTICLE_SYSTEM; };
};
