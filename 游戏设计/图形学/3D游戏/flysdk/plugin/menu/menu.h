enum classes_types
{
	TYPE_MENUGROUP=0x180,
	TYPE_MENUITEM,
	TYPE_MENUCAMERA,
};

class menugroup;
class menuitem;
class menucamera;

class menugroup : public bsp_object
{
public:
	menugroup() { type=TYPE_MENUGROUP; selitem=0; };

	int nitem;
	menuitem *item[8];
	float height;
	int selitem;

	int step(int dt) { return 1; };
	void draw();
	int get_custom_param_desc(int i,param_desc *pd);
	bsp_object *clone();
};
class menuitem : public bsp_object
{
public:
	menuitem() { type=TYPE_MENUITEM; };

	float width;
	float height;
	int texture;
	vector color;
	char command[256];

	void draw();
	int get_custom_param_desc(int i,param_desc *pd);
	bsp_object *clone();
};
class menucamera : public bsp_object
{
public:
	menucamera() { type=TYPE_MENUCAMERA; keystatus=0; };

	bsp_object *target;
	float rotvel;
	int keystatus;
	light *l;
	dyn_sound *sndchangesel;
	dyn_sound *sndselect;

	int step(int dt);
	int get_custom_param_desc(int i,param_desc *pd);
	bsp_object *clone();
};

class menugroup_desc : public class_desc
{
public:
	void *create() { return new menugroup; };
	char *get_name() { return "menugroup"; };
	int get_type() { return TYPE_MENUGROUP; };
};
class menuitem_desc : public class_desc
{
public:
	void *create() { return new menuitem; };
	char *get_name() { return "menuitem"; };
	int get_type() { return TYPE_MENUITEM; };
};
class menucamera_desc : public class_desc
{
public:
	void *create() { return new menucamera; };
	char *get_name() { return "menucamera"; };
	int get_type() { return TYPE_MENUCAMERA; };
};


