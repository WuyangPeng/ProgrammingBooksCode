enum
{
	TYPE_PANORAMA=0x150,
};

class panorama : public bsp_object
{
	public:

		int img[6];
		float size;
		vector color;

	void draw();
	int get_custom_param_desc(int i,param_desc *pd);

	 panorama() { type=TYPE_PANORAMA; rot.null(); };
};

class panorama_desc : public class_desc
{
public:
	void *create() { return new panorama; };
	char *get_name() { return "panorama"; };
	int get_type() { return TYPE_PANORAMA; };
};
