#include "..\..\lib\Fly3D.h"
#include "..\weapon\weapon.h"

#define FLYMP_MSG_POS 9180
#define FLYMP_MSG_KILL 9181
#define FLYMP_MSG_DAMAGE 9182

class person;
class jump_pad;
class birth_pad;
class gib;

struct mp_data
{
	DWORD type,dpid,flag;
	vector pos,vel,walkvel,X,Y,Z;
	float rot;
};

struct mp_data_damage
{
	DWORD type,dpid,from;
	vector pushvec;
	float value;
};

struct mp_data_kill
{
	DWORD type,dpid,dpidpoints;
	vector pos,hitpos;
	int birthpad;
};

enum 
{
	TYPE_PERSON=0x300,
	TYPE_JUMP_PAD,
	TYPE_BIRTH_PAD,
	TYPE_GIB,
};

class person : public bsp_object
{
public:
	float height,gravity,rotvel,updownrot,mousespeed;
	spot_light *spot;
	int flag,points,player;
	int jumpflag,jumpforcetime;
	float jumpforce,walkvel;
	vector jumpvec,walkvec;
	local_system ls;
	mesh *contactobj;
	int contactfacenum;
	shadow *personshadow;
	int zoomtime;
	float zoomangle1,zoomangle2;
	float shield,curshield;
	light_vertex dynlights;
	vector dynlight;
	
	anim_mesh *p_anim[3];
	anim_mesh *w_anim[3];
	int skin,cur_anim,cur_anim_time,loop_anim;
	gun *g;
	gib *gb;
	int ngib;
	float gibforce;
	birth_pad *bp;
	int zoompos;

	person()
	{
		type=TYPE_PERSON;
		contactobj=0;
		flag=0;
		player=0;
		points=0;
		cur_anim=0;
		cur_anim_time=0;
		loop_anim=1;
		bp=0;
		updownrot=0; 
		jumpflag=0;
		jumpvec.null();
		walkvec.null();
		zoompos=0;
		dynlight.null();
	}

	// virtual from bsp_object
	void init();
	int step(int dt);
	void draw();
	mesh *get_mesh() { return p_anim[cur_anim]; };
	mesh *ray_intersect(vector& ro,vector& rd,vector& ip,float& dist,int &facenum,float rad);
	int get_custom_param_desc(int i,param_desc *pd);
	int message(vector& p,float rad,int msg,int param,void *data);

	// check keys and mouse
	void do_input(int dt);
	// send mp message pos
	void mp_send_pos(int msgtype,int msgflag);
	// send mp message kill
	void mp_send_kill(int killer,int pad,vector& hitpoint);
	// send mp message damage
	void mp_send_damage(int from,vector& pushvec,float value);
	// show gibs, give points and select birth pad
	void die(int killer,vector& hitpos,int padindx);

	inline bsp_object *clone()
	{ 
		person *p=new person;
		*p=*this;
		p->source=this;
		return p;
	}
};

class jump_pad : public bsp_object
{
public:
	mesh *objmesh;
	float jumpforce;
	int forcetime,invert;

	jump_pad()
	{ type=TYPE_JUMP_PAD; };

	int get_custom_param_desc(int i,param_desc *pd);
	mesh *get_mesh() { return objmesh; };
	void init();
	int step(int dt) { return 0; };
	inline bsp_object *clone()
	{ 
		jump_pad *j=new jump_pad;
		*j=*this;
		j->source=this;
		return j;
	}
};

class birth_pad : public bsp_object
{
public:
	mesh *objmesh;
	mesh *animobj;
	int animtime;
	
	int animtime0;
	vector dynlight;

	birth_pad()
	{ type=TYPE_BIRTH_PAD; dynlight.null(); };

	void init();
	void draw();
	int message(vector& p,float rad,int msg,int param,void *data);
	int get_custom_param_desc(int i,param_desc *pd);
	int step(int dt) { return 0; };
	mesh *get_mesh() { return objmesh; };
	inline bsp_object *clone()
	{ 
		birth_pad *x=new birth_pad;
		*x=*this;
		x->source=this;
		return x;
	}
};

class gib : public bsp_object
{
public:
	mesh *objmesh;
	hitmark *hm;
	float gravity;
	int fadetime;
	int numbounces;
	int traildelay;

	vector dynlight;
	int lasttrail;


	gib()
	{ type=TYPE_GIB; dynlight.null(); lasttrail=0; };

	void draw();
	int step(int dt);
	int message(vector& p,float rad,int msg,int param,void *data);
	int get_custom_param_desc(int i,param_desc *pd);
	
	inline bsp_object *clone()
	{ 
		gib *x=new gib;
		*x=*this;
		x->source=this;
		return x;
	}
};

class person_desc : public class_desc
{
public:
	void *create() { return new person; };
	char *get_name() { return "person"; };
	int get_type() { return TYPE_PERSON; };
};

class jump_pad_desc : public class_desc
{
public:
	void *create() { return new jump_pad; };
	char *get_name() { return "jumppad"; };
	int get_type() { return TYPE_JUMP_PAD; };
};

class birth_pad_desc : public class_desc
{
public:
	void *create() { return new birth_pad; };
	char *get_name() { return "birthpad"; };
	int get_type() { return TYPE_BIRTH_PAD; };
};

class gib_desc : public class_desc
{
public:
	void *create() { return new gib; };
	char *get_name() { return "gib"; };
	int get_type() { return TYPE_GIB; };
};

