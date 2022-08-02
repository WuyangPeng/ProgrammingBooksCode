enum 
{
	TYPE_VIEWPORT=0x160,
};

class viewport : public bsp_object
{
public:
	bsp_object *target;
	float xf,yf,sxf,syf;
	int dirflag,on,key;

	int get_custom_param_desc(int i,param_desc *pd);

	viewport() 
	{ 
	type=TYPE_VIEWPORT; 
	on=0;
	};
};

class viewport_desc : public class_desc
{
public:
	void *create() { return new viewport; };
	char *get_name() { return "viewport"; };
	int get_type() { return TYPE_VIEWPORT; };
};

