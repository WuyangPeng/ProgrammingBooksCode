// the explode class implements a explosion definition
class explode : public bsp_object
{
	public:

		exp_sphere *e;	// the explode sphere
		sprite_light *s;		// the sprite
		light *l;		// the light
		dyn_sound *snd;		// the sound
		particle_system *ps;	// the particle system
		float damage,damageradius;	// the damage value and radius

	int get_custom_param_desc(int i,param_desc *pd);
	virtual void do_explode(vector& pos,vector& z,int fromplayer);

	explode() 
	{ type=TYPE_EXPLODE; };
};

class explode_desc : public class_desc
{
public:
	void *create() { return new explode; };
	char *get_name() { return "explode"; };
	int get_type() { return TYPE_EXPLODE; };
};

