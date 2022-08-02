class shadow : public bsp_object
{
public:
	// external parameters
	int texture;
	float sizex, sizey;

	// internal parmeters
	int hit;
	bsp_object *curobj;

	// constructor resets all internal parameters
	shadow()
	{ type=TYPE_SHADOW; hit=0; curobj=0; };

	// virtual functions from bsp_object
	void draw();
	int get_custom_param_desc(int i,param_desc *pd);
	bsp_object *clone()
	{
	shadow *tmp=new shadow;
	*tmp=*this;
	tmp->source=this;
	return tmp;
	}
	
	// custom functions
	void draw_simple_shadow();
	virtual void reposition(bsp_object *obj);
};

class shadow_desc : public class_desc
{
public:
	void *create() { return new shadow; };
	char *get_name() { return "shadow"; };
	int get_type() { return TYPE_SHADOW; };
};
