enum classes_types
{
	TYPE_FOGSPHERE=0x140,
	TYPE_FOGBOX,
};

class fogsphere : public bsp_object
{
public:
	fogsphere() { type=TYPE_FOGSPHERE; };
	float fogradius;
	float fogrange;
	float fogdepth;
	vector fogcolor;
	int fogmode;

	void fog_map(light_map *fm);
	int fog_intersect(vector& point,unsigned char& factor);
	int step(int dt);
	int get_custom_param_desc(int i,param_desc *pd);
	bsp_object *clone();
};

class fogbox : public bsp_object
{
public:
	fogbox() { type=TYPE_FOGBOX; };
	float fogsizex;
	float fogsizey;
	float fogsizez;
	float fogrange;
	float fogdepth;
	vector fogcolor;
	int fogmode;
	boundbox bb;
	float bbdiag;

	void fog_map(light_map *fm);
	int fog_intersect(vector& point,unsigned char& factor);
	int step(int dt);
	int get_custom_param_desc(int i,param_desc *pd);
	bsp_object *clone();
};

class fogsphere_desc : public class_desc
{
public:
	void *create() { return new fogsphere; };
	char *get_name() { return "fogsphere"; };
	int get_type() { return TYPE_FOGSPHERE; };
};

class fogbox_desc : public class_desc
{
public:
	void *create() { return new fogbox; };
	char *get_name() { return "fogbox"; };
	int get_type() { return TYPE_FOGBOX; };
};

