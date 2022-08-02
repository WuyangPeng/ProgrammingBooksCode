#include "..\gamelib\gamelib.h"

enum classes_types
{
	TYPE_GUN=0x170,
	TYPE_HITMARK,
	TYPE_LASER,
	TYPE_MISSILE,
	TYPE_MINE,
};

#define TYPE_GUN_PROJECTILE (TYPE_LASER|(TYPE_MINE<<16))

class hitmark : public bsp_object
{
public:
	hitmark() { type=TYPE_HITMARK; dynlight.null(); };

	int texture;
	float size;
	int fadetime;
	int mode;

	vector dynlight;

	int step(int dt);
	void draw();
	int get_custom_param_desc(int i,param_desc *pd);
	bsp_object *clone();
	int message(vector& p,float rad,int msg,int param,void *data);
};

class gun_projectile : public bsp_object
{
public:
	int player;
	float damage;

	virtual void fire(vector& p,vector& dir,float v,int playerid)=0;
};

class gun : public bsp_object
{
public:
	gun() { type=TYPE_GUN; firetime=0; curfire=0; };

	dyn_sound *sndfire;
	gun_projectile *p;
	int firecount,nfirepos,firetime,
		delay,nfire,curfire,firedelay;
	float firevel,randomangle;
	vector firepos[4];

	virtual void fire(bsp_object *obj,int player);
	virtual int fire_status();
	int get_custom_param_desc(int i,param_desc *pd);
	bsp_object *clone();
};

class mine : public gun_projectile
{
public:
	mine() { type=TYPE_MINE; mine_find=0; dynlight.null(); };

	mesh *objmesh;
	explode *exp; 
	light *l;
	dyn_sound *snd;
	exp_sphere *s;
	int delay;
	float shield;
	float factor;
	vector dynlight;

	bsp_object *enemy;
	float enemydist,lookrange;
	void (* mine_find)(void *data, bsp_object *e);

	virtual void fire(vector& p,vector& dir,float v,int playerid);
	mesh *ray_intersect(vector& ro,vector& rd,vector& ip,float& dist,int &facenum,float rad=0.0f);
	int message(vector& p,float rad,int msg,int param,void *data);

	int step(int dt);
	void draw();
	int get_custom_param_desc(int i,param_desc *pd);
	bsp_object *clone();
};

class laser : public gun_projectile
{
public:
	laser() { type=TYPE_LASER; slast=0; };

	float sizetexture;
	int sidetexture,fronttexture;
	vector startpos;
	hitmark *hm;

	light *l;
	explode *exp; 
	sprite_light *s;
	float sfact,slast;

	virtual void fire(vector& p,vector& dir,float v,int playerid);

	int step(int dt);
	void draw();
	int get_custom_param_desc(int i,param_desc *pd);
	bsp_object *clone();
};

class missile : public gun_projectile
{
public:
	missile() { type=TYPE_MISSILE; missile_find=0; dynlight.null(); };

	mesh *objmesh;
	explode *exp; 
	dyn_sound *snd;
	viewport *viewport;
	float lightzpos;
	light *l;
	hitmark *hm;
	vector dynlight;
	bsp_object *enemy;
	float enemydist,rotvel,lookrange,lookangle;

	virtual void fire(vector& p,vector& dir,float v,int playerid);
	void (* missile_find)(void *data, bsp_object *e);

	int step(int dt);
	void draw();
	int get_custom_param_desc(int i,param_desc *pd);
	int message(vector& p,float rad,int msg,int param,void *data);
	bsp_object *clone();
};

class gun_desc : public class_desc
{
public:
	void *create() { return new gun; };
	char *get_name() { return "gun"; };
	int get_type() { return TYPE_GUN; };
};
class hitmark_desc : public class_desc
{
public:
	void *create() { return new hitmark; };
	char *get_name() { return "hitmark"; };
	int get_type() { return TYPE_HITMARK; };
};
class mine_desc : public class_desc
{
public:
	void *create() { return new mine; };
	char *get_name() { return "mine"; };
	int get_type() { return TYPE_MINE; };
};
class laser_desc : public class_desc
{
public:
	void *create() { return new laser; };
	char *get_name() { return "laser"; };
	int get_type() { return TYPE_LASER; };
};
class missile_desc : public class_desc
{
public:
	void *create() { return new missile; };
	char *get_name() { return "missile"; };
	int get_type() { return TYPE_MISSILE; };
};

