#include "..\..\lib\Fly3D.h"
#include "..\weapon\weapon.h"

#define SHIP_FLAG3_INVISIBLE 0x10000
#define SHIP_FLAG3_INVENSIBLE 0x20000
#define SHIP_MAXAB_SPEEDBOOST 5000

#define FLYMP_MSG_POS 9180
#define FLYMP_MSG_KILL 9181
#define FLYMP_MSG_EXPLODE 9182
#define FLYMP_MSG_DAMAGE 9183
#define FLYMP_MSG_POWERUPMOVE 9184
#define FLYMP_MSG_POWERUPGET 9185

void init_multiplayer();
void mp_message(int from,mp_msg *msg);

enum 
{ 
	TYPE_SHIP=0x200,
	TYPE_TURRET,
	TYPE_ROBOT,
	TYPE_POWERUP,
	TYPE_CONTAINER,
};

struct mp_data
{
	DWORD type,dpid,flag;
	vector pos,vel,Y,Z;
};

struct mp_data2
{
	DWORD type,from;
	vector v;
	float f;
};

class ship : public bsp_object
{	
	public:

		float veldamp,maxvel;
		float speedboost,speedboost0;
		float shield,maxshield;
		int abtime,maxabtime;
		int display;
		int flag,flag2,flag3;
		spot_light *spot;
		mesh *objmesh,*shieldmesh;
		explode *exp;
		light *englight;
		sprite_light *enghalo;
		float engpos;
		vector rotvel;
		vector rotforce;
		float angularmaxvel,angulardamp,mousespeed,forcefactor;
		vector mouserot;
		int lasthitfrom,lasthittime,player,points,exptime;
		bsp_object expcam;
		vector hitcolor,invencolor,killcolor;
		float invistransp;
		int ng,firesel;
		gun *g[9];
		light_vertex dynlights;	
		vector dynlight;

	mesh *get_mesh() { return objmesh; };
	int step(int dt);
	void draw();
	int get_custom_param_desc(int i,param_desc *pd);
	int message(vector& p,float rad,int msg,int param,void *data);
	mesh *ray_intersect(vector& ro,vector& rd,vector& ip,float& dist,int &facenum,float rad);

	void draw_game_status();
	void check_keys(int time_step);
	void mp_send_pos(int msgtype,int msgflag);

	inline bsp_object *clone() 
	{
		ship *s=new ship;
		*s=*this;
		s->source=this;
		return s; 
	};
	ship();
};

class powerup : public bsp_object
{
public:

	mesh *objmesh;
	light *l;
	int value;
	int valuetype;
	int mode;
	dyn_sound *sndget;

	mesh *get_mesh() { return objmesh; };
	int step(int dt);
	void draw();
	int get_custom_param_desc(int i,param_desc *pd);

	void powerup_get(ship *s);

	inline bsp_object *clone() 
	{ 
		powerup *p=new powerup;
		*p=*this;
		p->source=this;
		return p;
	};

	powerup()
	{ type=TYPE_POWERUP; }
};

class turret : public bsp_object
{
public:
	mesh *base,*tube;
	gun *g;
	float fireang;
	int firedelay;
	float lookrange;
	explode *exp;
	float shield;
	vector dynlight;
	float enemydist;
	bsp_object *enemy;
	float rotvel;
	local_system tubels;

	mesh *get_mesh() { return base; };
	void init();
	int step(int dt);
	void draw();
	int get_custom_param_desc(int i,param_desc *pd);
	int message(vector& p,float rad,int msg,int param,void *data);
	mesh *ray_intersect(vector& ro,vector& rd,vector& ip,float& dist,int &facenum,float rad);

	inline bsp_object *clone() 
	{ 
		turret *t=new turret;
		*t=*this;
		t->source=this;
		return t;
	};

	turret()
	{ type=TYPE_TURRET; }
};

class robot : public bsp_object
{
public:
	mesh *objmesh;
	mesh *shieldmesh;
	gun *g;
	float lookrange;
	float lookangle;
	float maxvel;
	float rotvel;
	float fireang;
	float mindist;
	explode *exp;
	float shield;
	vector shieldcolor;

	vector dynlight;
	bsp_object *enemy;
	vector enemylastpos;
	float enemydist;
	int flag;
	int lasthittime;

	mesh *get_mesh() { return objmesh; };
	void init();
	int step(int dt);
	void draw();
	int get_custom_param_desc(int i,param_desc *pd);
	int message(vector& p,float rad,int msg,int param,void *data);
	mesh *ray_intersect(vector& ro,vector& rd,vector& ip,float& dist,int &facenum,float rad);

	inline bsp_object *clone() 
	{ 
		robot *tmp=new robot;
		*tmp=*this;
		tmp->source=this;
		return tmp;
	}

	robot()
	{ type=TYPE_ROBOT; dynlight.null(); enemy=0; flag=0; lasthittime=0; }
};

class container : public bsp_object
{
public:
	mesh *objmesh;
	explode *exp;
	powerup *p;
	float shield;
	vector dynlight;

	mesh *get_mesh() { return objmesh; };	
	void init();
	int step(int dt);
	void draw();
	int get_custom_param_desc(int i,param_desc *pd);
	int message(vector& p,float rad,int msg,int param,void *data);
	mesh *ray_intersect(vector& ro,vector& rd,vector& ip,float& dist,int &facenum,float rad);

	inline bsp_object *clone() 
	{ 
		container *tmp=new container;
		*tmp=*this;
		tmp->source=this;
		return tmp;
	}

	container()
	{ type=TYPE_CONTAINER; dynlight.null(); }
};

class ship_desc : public class_desc
{
public:
	void *create() { return new ship; };
	char *get_name() { return "ship"; };
	int get_type() { return TYPE_SHIP; };
};

class powerup_desc : public class_desc
{
public:
	void *create() { return new powerup; };
	char *get_name() { return "powerup"; };
	int get_type() { return TYPE_POWERUP; };
};

class turret_desc : public class_desc
{
public:
	void *create() { return new turret; };
	char *get_name() { return "turret"; };
	int get_type() { return TYPE_TURRET; };
};

class robot_desc : public class_desc
{
public:
	void *create() { return new robot; };
	char *get_name() { return "robot"; };
	int get_type() { return TYPE_ROBOT; };
};

class container_desc : public class_desc
{
public:
	void *create() { return new container; };
	char *get_name() { return "container"; };
	int get_type() { return TYPE_CONTAINER; };
};

