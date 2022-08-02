#define FLYMP_MSG_POS 9180

class camera;
class car;
class sun;

struct mp_data
{
	DWORD type,dpid,flag;
	float wheelrot;
	vector pos,vel,Y,Z;
};

enum classes_types
{
	TYPE_CAR=0x400,
	TYPE_CAMERA,
	TYPE_SUN
};

class car : public bsp_object
{
public:
	car() 
	{ 
		type=TYPE_CAR; player=0;
		wheelrot=0; wheelroll=0; 
		contactobj=0; contactfacenum=0;
		totaltracktime=curtracktime=0;
	}

	float accel;
	float maxvel;
	vector veldamp;
	float carwheelrot;
	float carheight;
	float wheelrotvel;
	float wheelmaxrot;
	float wheelrotdamp;
	float wheelradius;
	float gravity;
	mesh *carmesh;
	mesh *wheelmesh;
	vector wheelposft;
	vector wheelposbk;
	bezier_curve *track;
	shadow *carshadow;

	int totaltracktime,curtracktime,player;
	float wheelrot,wheelroll;
	mesh *contactobj;
	int contactfacenum;

	void check_keys(int dt);
	void check_robot_keys(int dt);
	void mp_send_pos(int msgtype,int msgflag);
	void draw_stencil_shadow(vector& lightpos);

	void init();
	int step(int dt);
	void draw();
	int get_custom_param_desc(int i,param_desc *pd);
	bsp_object *clone();
	mesh *get_mesh() { return carmesh; };
};

class camera : public bsp_object
{
public:
	camera() { type=TYPE_CAMERA; };

	float height;
	float dist;
	float maxvel;
	vector lp;
	bsp_object *target;
	sun *s;

	void init();
	int step(int dt);
	int get_custom_param_desc(int i,param_desc *pd);
	bsp_object *clone();
};

class sun : public bsp_object
{
public:
	sun() { type=TYPE_SUN; };

	mesh *objmesh;
	vector color;
	int halopic;
	float halosize;

	void init();
	void draw();
	int get_custom_param_desc(int i,param_desc *pd);
	bsp_object *clone();
};

class car_desc : public class_desc
{
public:
	void *create() { return new car; };
	char *get_name() { return "car"; };
	int get_type() { return TYPE_CAR; };
};

class camera_desc : public class_desc
{
public:
	void *create() { return new camera; };
	char *get_name() { return "camera"; };
	int get_type() { return TYPE_CAMERA; };
};

class sun_desc : public class_desc
{
public:
	void *create() { return new sun; };
	char *get_name() { return "sun"; };
	int get_type() { return TYPE_SUN; };
};

