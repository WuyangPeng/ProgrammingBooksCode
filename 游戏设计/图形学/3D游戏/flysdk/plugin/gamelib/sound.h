class dyn_sound : public bsp_object
{	
public:
		sound *snd;
		int instance;
		vector *lockpos,*lockvel;
		int volume,loop;
		float mindist,maxdist;

	dyn_sound();
	virtual ~dyn_sound();
	int step(int dt);
	bsp_object *clone();
	int get_custom_param_desc(int i,param_desc *pd);
	virtual void play();
	virtual void add_sound_clone(vector *lock_pos,vector *lock_vel);
};

class dyn_sound_desc : public class_desc
{
public:
	void *create() { return new dyn_sound; };
	char *get_name() { return "sound"; };
	int get_type() { return TYPE_SOUND; };
};
