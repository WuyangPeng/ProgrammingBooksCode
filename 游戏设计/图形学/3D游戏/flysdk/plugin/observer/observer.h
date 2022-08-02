enum
{
	TYPE_OBSERVER=0x199,
};

class observer : public bsp_object
{
public:
	observer() { type=TYPE_OBSERVER; };

	float rotvel;
	float mousevel;
	float moveforce;
	float maxvel;
	float veldamp;

	void check_keys(int dt);
	void init();
	int step(int dt);
	void draw();
	int get_custom_param_desc(int i,param_desc *pd);
	bsp_object *clone();
};

class observer_desc : public class_desc
{
public:
	void *create() { return new observer; };
	char *get_name() { return "observer"; };
	int get_type() { return TYPE_OBSERVER; };
};

