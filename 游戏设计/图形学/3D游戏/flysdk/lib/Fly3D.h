#ifndef STRICT
#define STRICT
#endif

#ifdef FLY_EXPORTS
#define FLY_API __declspec(dllexport)
#else
#define FLY_API __declspec(dllimport)
#endif

class FLY_API boundbox;
class FLY_API plane;
class FLY_API face;
class FLY_API local_system;
class FLY_API base_object;
class FLY_API sound;
class FLY_API mesh;
class FLY_API anim_mesh;
class FLY_API stripfan_mesh;
class FLY_API bezier_curve;
class FLY_API bezier_patch;
class FLY_API particle;
class FLY_API bsp_node;
class FLY_API bsp_object;
class FLY_API static_mesh;
class FLY_API light_map;
class FLY_API light_map_pic;
class FLY_API light_vertex;
class FLY_API class_desc;
class FLY_API console;
class FLY_API flydll;
class FLY_API flydllgroup;
class FLY_API flyEngine;

#define MAX_ELEMDRAW 16384
#define MAX_LIGHTMAP 8192
#define MAX_PICTURES 1024
#define MAX_VERT 4096
#define MAX_HWLIGHTS 8
#define MAX_TEXTURE_UNITS 4
#define MAX_LATEDRAW_LAYERS 8
#define MAX_SOUND_CHANNELS	4

#define NUM_DEFAULT_PARAM 12

#define FLYM_INITSCENE			1000
#define FLYM_UPDATESCENE		1001
#define FLYM_DRAWSCENE			1002
#define FLYM_DRAWTEXT			1003
#define FLYM_CLOSESCENE			1004
#define FLYM_MPMESSAGE			1005
#define FLYM_MPUPDATE			1006

#define FLYOBJM_CHANGEPARAM		2000
#define FLYOBJM_ILLUM			2001
#define FLYOBJM_STATICILLUM		2002
#define FLYOBJM_DYNILLUM		2003
#define FLYOBJM_DAMAGE			2004

#define FLYAPPID_NONE			0
#define FLYAPPID_FLY			1
#define FLYAPPID_FLYEDITOR		2
#define FLYAPPID_LIGHTBSP		3
#define FLYAPPID_FLYSERV		4
#define FLYAPPID_FLYOCX			5
#define FLYAPPID_VIEWBSPGL		6

#define TYPE_STATIC_MESH -1

#define MAPPING_NUM			4
#define MAPPING_OPTIONS		16
#define MAPPING_TEXTURE		1
#define MAPPING_DETAIL		2
#define MAPPING_LIGHTMAP	4
#define MAPPING_FOGMAP		8

#define MESH_IMPLODE 1
#define MESH_FACENORM 2
#define MESH_VERTNORM 4
#define MESH_BBOX 8
#define MESH_EDGES 16

#define PATCH_EVAL_POINT		1
#define PATCH_EVAL_TEXTCOORD	2
#define PATCH_EVAL_NORMAL		4

#define CONSOLE_MAX_LINES 128
#define CONSOLE_COL 40
#define CONSOLE_LIN 30
#define FONTS_IMG_SIZE 128
#define FONTS_SIZE 16
#define FONTS_NUM 8

#define PVS_TEST(from,to) \
        (*(pvs + (from)*pvsrowsize + ((to)>>3)) & (1 << ((to) & 7)))

#include <windows.h>
#include <stdio.h>
#include <math.h>
#include <mmsystem.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include "glext.h"
#include "dx.h"
#include "vecmat.h"
#include "render.h"
#include "picture.h"
#include "flypak.h"
#include "3dsimpexp.h"

struct vertex
{
	vector pos,normal,color;
	float u,v,ul,vl;
};

class FLY_API boundbox
{
	public:
		vector min,max;

	void reset() { min.vec(BIG,BIG,BIG); max.vec(-BIG,-BIG,-BIG); };
	int ray_intersect(vector& ro,vector& rd,float& tnear,float& tfar);
	void add_point(vector &p);
	void add_point(float x,float y,float z);
};

class FLY_API local_system
{
	public:
		vector X,Y,Z;	// base axis vector4s
		mat4x4 mat,mat_t; // rotation matrix and transpose

	void update_mat();
	void rotate(vector& rot);
	void rotate(float ang,vector& v);
	void rotate(vector &v, vector &u, float maxang=360);
	void align_z(vector& z);
};

class FLY_API plane
{
	public:
		vector normal;		// plane normal
		float d0;			// the perpendicular distance from the 
							// plane to the origin

	// computes the perpendicular distance from 
	// a point to the plane
	inline float distance(vector &v)
		{ return vec_dot(normal,v)+d0; }
};

class FLY_API face : public plane
{
	public:
		vector *vert[3];		// the 3 vertices
		vector edgenormal[3];	// the 3 edge normals
		vector vertnormal[3];	// the 3 vertices normals
		vector color;			// the face color
		int texpic;				// the texture applyed to the face
		int lm;					// the lightmap applyed to the face
		float uv[3][2];			// the 3 vertices (u,v) texture coord.
		float lmuv[3][2];		// lightmap 3 vertices (u,v) texture coord.
		float emmradius;		// illum radius
		int lastdraw;			// last time draw
		int indx;				// face index into face array

	face() { texpic=-1; lm=-1; };

	// computes ray intersection with the face
	int ray_intersect(vector& ro,vector& rd,vector& ip,float& dist,float rad=0.0f);

	// convert point p in face u,v coordinates
	void inverse_map(vector& p,float& u,float& v);
	// convert face u,v coordinates to point p
	void forward_map(float& u,float& v,vector& p);
};

class FLY_API base_object
{
	public: 
		char name[32];			// the object name
		char long_name[32];		// the object long name
		base_object *next_obj;	// the next object in the linked list

	base_object()
	{ next_obj=0; name[0]=long_name[0]=0; };
	virtual ~base_object()
	{ ; };
};

class FLY_API sound : public base_object
{
	public:
		int total_time;
		
		int bufuse[MAX_SOUND_CHANNELS];
		LPDIRECTSOUNDBUFFER buf[MAX_SOUND_CHANNELS];
		LPDIRECTSOUND3DBUFFER buf3d[MAX_SOUND_CHANNELS];

	void reset();
	int load_wav(char *filename);
	int get_sound_instace();
	void free_sound_instance(int i);
	
	sound();
	~sound();
};

// the object class implements a 3d object
// its faces may reference the local faces or
// the global engine bsp faces
class FLY_API mesh : public base_object
{
	public:
		int nv,		// number of vertices
			nf;		// number of faces
		vector *vert;	// the vertices
		vector *vertnorm; // the vertices normals
		face **faces;	// the faces
		boundbox bbox;	// the object bound box
		vector pivotpos;	// object pivot position
		face *localfaces;	// the local faces
		int *edges,nedges;	// the edges info
		vector color;		// the color multiplier
		float scrollu,scrollv;	// texture scroll values
		int lastdraw;		// last time this mesh was drawn

	// frees the object
	void reset();
	// draws all object faces
	virtual void draw();
	virtual void draw_cartoon(vector& campos,vector& light,light_vertex& lights,float edgewidth);
	virtual void draw_shadow_volume(vector& lightpos);
	// loads a 3dsfile into this object
	int load_3ds(char *name);
	// compute face normals for all object faces and its boundbox
	void compute_normals(int flag);
	// computes ray intersection with all object faces
	int ray_intersect(vector& ro,vector& rd,vector& ip,float& dist,float rad=0.0f);
	// returns on first ray intersection
	int ray_intersect_test(vector& ro,vector& rd,float rad=0.0f);
	// dynamicaly illuminate object faces
	void illum_faces(vector& ip,float d_max,vector& c,int shadows);
	// weld all vertices closer then mindist
	void implode(float mindist=0.1f);
	// find a vertex edge for two mesh vertices
	int get_edge(int v1,int v2);
	// returns a new mesh identical to the original
	mesh *clone();
	void set_numverts(int nverts,int keep=0);
	void set_numfaces(int nfaces,int local=0,int keep=0);

	mesh() 
	{ 
		nv=0; nf=0;
		vert=0; vertnorm=0; 
		faces=0; localfaces=0; 
		edges=0; nedges=0;
		color.vec(1.0f,1.0f,1.0f,1.0f); 
		scrollu=scrollv=0.0f;
		lastdraw=0; 
	};
	virtual ~mesh()
	{ reset(); };
};

class FLY_API anim_mesh : public mesh
{
	public:
		int nframes,texpic;
		vector *ao_vert;
		vector *ao_bbox;
		
		int nstripfan,nstripfanvert,*stripfancount,*stripfanvert;
		vertex *vertdata;

	void reset();
	void compute_bbox();
	int load_fao(char *name);
	void set_key(float key);
	void set_key(int key);
	void draw();

	virtual ~anim_mesh() 
	{ reset(); };
	anim_mesh()
	{
		ao_vert=0;
		ao_bbox=0;
		nframes=0;
		nstripfan=0;
		nstripfanvert=0;
		stripfancount=0;
		stripfanvert=0;
		vertdata=0;
		texpic=-1;
	}
};

class FLY_API stripfan_mesh
{
	public:
		int nstripfan;
		int *stripfandata;

		int nvert;
		vertex *vertdata;

		void reset();
		void draw(int mode);
		mesh *build_mesh();
		vertex *add_stripfan(int nvert,int texpic,int lmpic);
	
	stripfan_mesh()
	{
	nstripfan=0; stripfandata=0;
	nvert=0; vertdata=0;
	}
	virtual ~stripfan_mesh()
	{
		reset();
	}
};

class FLY_API bezier_curve : public base_object
{
	protected:
		float distance(float *p,float *p1,float *p2);
		void subdiv(float u1,float u2,float *p1,float *p2,float *points,int& npoints,float maxerror,int maxpoints);

	public:
		float *p;	// curve control points
		int np,		// number of control points
			ns,		// number of bezier segments ((np-1)/3)
			nd;		// curve dimensions (2->2D, 3->3D, etc...)
		vector pivot;	// curve pivot position

	void reset();
	void set_dim(int ndim);
	void add_point(float *f);
	void evaluate(float u,float *f);
	void evaluate_tangent(float u,float *f);
	
	int load_bez(char *file);
	int adaptative_subdiv(float maxerror,float *points,int maxpoints);
	float length();

	bezier_curve() { p=0; reset(); };
	virtual ~bezier_curve() { reset(); };
};

class FLY_API bezier_patch : public base_object
{
	public:
		int mode;		// 2 for quadratic and 3 for cubic
		vector *p;		// the surface control points
		vector *t;		// the surface texture control points
		int np,	 // num points
			npu, // num points in u dir
			npv, // num points in v dir
			nsu, // num segments in u dir
			nsv; // num segments in u dir

		int levelu,levelv; // subdivision level in u and v
		int nvertu,nvertv; // surface num vertices in u and v
		int texpic,lm;	// texture and lightmap
		vector *surf;	// discretized surface
		vector pivot;	// the pivot position

	void reset();
	int load_pch(char *file);
	void build_loft(bezier_curve *shape,bezier_curve *path,int texture,int lightmap,float tileu,float tilev);
	void evaluate(int evaltype,float u,float v,vector *dest);
	void build_surface();
	void illuminate(vector& p,float rad,vector& color,int shadows);
	void draw(int nleveldrop=0);
	mesh *build_mesh();

	bezier_patch()	{ p=0; t=0; surf=0; reset(); };
	~bezier_patch()	{ reset(); };
};

// particle class implements a single, invisible, particle 
class FLY_API particle
{
	public:
		vector pos,		// particle position
			vel,		// partuicle velocity
			force;		// particle force
		float mass,		// particle mass
			bump,		// particle bump factor [0-1]
			friction,	// particle friction factor [0-1]
			radius;		// particle radius in mm
		int life;		// particle life in ms
		int col_flag;	// collision flag (0-no collision, 
						// 1-do collision, 3-collide and die)

	// computes particle collision
	int compute_collision(vector& p,vector& v);

	// moves the particle dt ms
	int step(int dt);
};

class FLY_API param_desc
{
	public:
		char name[64];
		int type;
		void *data;
	
	char *get_string();
	void set_string(char *str);
};

// the bsp_node class implements a node from the bsp tree
// if it has no childs (child[0]==child[1]==0), elements
// may be present in the elem linked list member
class FLY_API bsp_node : public plane
{
	public:
		bsp_node *child[2];		// the node childs
		bsp_object 
			*elem,			// the elements in this node
			**last_elem;

		int leaf;		// leaf index (-1 not a leaf)
		vector color;	// ambient light

	bsp_node()
	{ child[0]=child[1]=0; elem=0; leaf=-1; last_elem=&elem; };
	virtual ~bsp_node();
};

// bsp_object implements any object that is moving in space and
// is considered a particle to bsp
class FLY_API bsp_object :	public base_object,
							public particle, 
							public local_system
{
	public:
		int type;			// object type
		int active;			// actite at startup?
		int latedraw;		// draw after standard objects
		vector rot;			// rotation at startup
		bsp_object *next_elem;	// next element in the bsp node
		bsp_object *source;		// original object after cloning
		bsp_node *node;			// the bsptree node the object is in

	// adds object to the bsp
	void add_to_bsp();	

	// removes the object from the bsp
	void remove_from_bsp();

	// moves the object dt ms
	virtual int step(int dt)			
	{ return particle::step(dt); };

	virtual bsp_object *clone() 
	{ return 0; };

	virtual mesh *get_mesh()
	{ return 0; };

	virtual void init()
	{ ; };

	int get_param_desc(int i,param_desc *pd);

	virtual int get_custom_param_desc(int i,param_desc *pd)
	{ return 0; };

	virtual mesh *ray_intersect(vector& ro,vector& rd,vector& ip,float& dist,int &facenum,float rad=0.0f);
	virtual int ray_intersect_test(vector& ro,vector& rd,float rad=0.0f);

	virtual int message(vector& p,float rad,int msg,int param,void *data)
	{ return 0; };

	virtual void draw();

	void load_default_params(fly_pak *file,char *sec);
	void load_params(fly_pak *file,char *sec);

	bsp_object() 
	{ node=0; col_flag=0; source=0; next_elem=0; type=0; };
	virtual ~bsp_object() 
	{ if (node) remove_from_bsp(); };
};

// the static_object class implements the group of faces 
// that are presentg at a bsp leaf node
class FLY_API static_mesh : public bsp_object
{
	public:
		mesh *objmesh;

	// computes ray intersection with the static object
	mesh *ray_intersect(vector& ro,vector& rd,vector& ip,float& dist,int &facenum,float rad=0.0f);
	int ray_intersect_test(vector& ro,vector& rd,float rad);
	int message(vector& p,float rad,int msg,int param,void *data);

	static_mesh() 
	{ type=TYPE_STATIC_MESH; objmesh=new mesh; };
	virtual ~static_mesh()
	{ if (objmesh) delete objmesh; };
};

class FLY_API light_map_pic
{
	public:
		unsigned char *bmp;
		int sizex,sizey;
		int bytesx,bytesxy;
		int bytespixel;

	light_map_pic(int sx,int sy,int bp=3)
	{
		bytespixel=bp;
		sizex=sx; 
		sizey=sy; 
		bytesx=sx*bytespixel;
		bytesxy=bytesx*sizey;
		bmp=new unsigned char [bytesxy];
	};
	virtual ~light_map_pic() 
	{ 
		if(bmp) delete bmp; 
	};
};

class FLY_API light_map
{
	protected:
		vector v0, v1, v2, normal;
		float det;
		float uv[3][2];
	public:
		int lastupdate;
		int pic;
		int offsetx,offsety;
		int sizex,sizey;
		int facenum;
		unsigned char *bmp;
		int bytespixel,bytesx,bytesxy;
		vector d0, d1, d2;

	void map_point(float u, float v, vector &point);
	void set_base(face *f,light_map_pic *lmp,vector& pos=vector(0,0,0));
	void illum(vector& pos,vector& color,float rad,int shadows);
	void load(light_map_pic *lmp);
	void save(light_map_pic *lmp);

	light_map(int f,int p,int x,int y,int sx,int sy,int bp=3)
	{
		facenum=f;
		pic=p;
		offsetx=x;
		offsety=y;
		sizex=sx;
		sizey=sy;
		bytespixel=bp;
		lastupdate=0;
		bytesx=sx*bp;
		if (bytesx&3) bytesx+=4-(bytesx&3);
		bytesxy=bytesx*sy;
		bmp=new unsigned char[bytesxy];
	};
	virtual ~light_map() 
	{ 
		if (bmp) 
			delete bmp; 
	};
};

class FLY_API light_vertex
{
	public:
		int nlights;
		vector pos[MAX_HWLIGHTS];
		vector color[MAX_HWLIGHTS];
		float radius[MAX_HWLIGHTS];

	light_vertex() { nlights=0; };
	void add_light(vector& p,vector& c,float r);
	void init_draw(bsp_object *obj);
	void end_draw();
};

// the class_desc, flydll and flydllgroup
// classes are used to manage the plugins
class FLY_API class_desc
{
	public:
		virtual void *create()=0;
		virtual char *get_name()=0;
		virtual int get_type()=0;
};

class FLY_API console
{
	public:
		int mode,time,nlines,linecount,winlines;
		char *buf[CONSOLE_MAX_LINES];

		char cmd_line[256];
		int cmd_pos;

		float dx,dy;

	console();
	~console();

	void show();
	void hide();
	void draw();
	void step(int dt);
	float draw_text(float x,float y,char *text);

	void key_press(int key);
	void add_string(char *fmt, ...);
	int command_tokens(char *str,char **token);
	void command_exec(char *str);
};

class FLY_API flydll
{
	public:
		HINSTANCE hdll;
		char dll_filename[256];
		int nclasses;

	int (* num_classes)();
	class_desc *(* get_class_desc)(int i);
	int (* fly_message)(int msg,int param,void *data);
};

class FLY_API flydllgroup
{
	public:
		int ndll;
		flydll **dll;

		int ncd;
		class_desc **cd;
		
	flydllgroup();
	virtual ~flydllgroup();
	
	void reset();
	
	int add_dll(char *filename);
	int delete_dll(char *filename);
	void move_dll(char *filename,int newrelpos);

	int send_message(int msg,int param,void *data);
	
	void load_all_classes(fly_pak *file);
	void load_classes(int d,fly_pak *file);
	void load_default_param(bsp_object *o,char *sec,fly_pak *file);
	void delete_class(bsp_object *o);
	void delete_references(bsp_object *o);
	bsp_object *add_class(char *name);
};

class FLY_API flyEngine
{
	private:
		int load_data();
		void save_bsp(bsp_node *n,FILE *fp);
		void load_bsp(bsp_node **n,fly_pak *fp);
		
		void find_leaf(bsp_node *n);
		void draw_static_faces(int *fd,int nfd);
		void draw_static_faces_cartoon(int *fd,int nfd);
		void draw_bsp(bsp_node *n);

	protected:
		void reset();
		int load_pictures(char *name);
		void load_level();
		void compute_normals();
		void compute_node_light();
		void compute_edges();

		int load_bsp(char *file);
		int save_bsp(char *file);

		int save_lightmaps(char *file);

		void alloc_pvs(char value);
		int load_pvs(char *file);
		int save_pvs(char *file);

	public:
		int load_lightmaps(char *file);
		int	cur_step,cur_step_base;
		int cur_frame,cur_frame_base;
		int start_time,cur_time,cur_dt;
		int intropic,introtime;

		flydllgroup dll;
		console con;

		bsp_object *player;
		bsp_object *cam;
		vector frustrum[5];

		bsp_object *excludecollision,*stepobj;

		int nelemdraw;
		bsp_object *elemdraw[MAX_ELEMDRAW];
		int nelemlatedraw[MAX_LATEDRAW_LAYERS];
		bsp_object *elemlatedraw[MAX_LATEDRAW_LAYERS][MAX_ELEMDRAW];
		int *facedraw;
		int nfacedraw;
		int *facedrawtransp;
		int nfacedrawtransp;

		char flysdkpath[256];   // the sdk path (c:\flysdk\)
		char flyfile[256];		// the .fly file (ship\ship.fly)
		char flydatapath[256];	// the .fly path (c:\flysdk\data\ship\)
		char flyfilename[256];	// the .fly full file (c:\flysdk\data\ship\ship.fly)
		char bspfile[256];		// the bsp file (ship)
		char status_msg[256];
		char console_command[256];
		unsigned status_msg_time;
		
		float bboxdiag,viewmaxdist,viewmindist,camangle,aspect,geomdetail,
			curveerr,lmpxsize,detailtile,cartoonwidth,shadowdepth;
		vector bbox1,bbox2,bboxC,filter,background,cartooncolor,shadowcolor;
		int nodedrawcount,nodeonly,pvsoff,fog,mpdelay,antialias,
			amblight,mapmode,shadows,noinput,wireframe,mute,mouse,
			clearbk,moving,crosshairpic,crosshairsize,appid,multitexture,
			detailpic,hwlights,stencil,cartoonpic,cartoonpicbsp;

		// linked list of active objects
		bsp_object *active_obj0,*last_active_obj;
		
		// linked list of stock script objects
		bsp_object *stock_obj0;

		// linked list of model objects
		mesh *model_obj0;

		// linked list of sound objects
		sound *sound_obj0;

		// linked list of bezier curves
		bezier_curve *bezier_curve0;

		// linked list of bezier patches
		bezier_patch *bezier_patch0;

		// dynamic shadows
		bsp_object *shadow_obj;

		// ray intersection data
		bsp_object *hitobj;
		mesh *hitmesh;
		int hitface;
		vector hitip;

		// fonts
		int fonts_width[64];
		int status,fontspic,consolepic;

		// vertex array for static bsp faces
		vector *vert,*vertcolor,*vertnormal;
		int nvert;

		// faces array for static bsp
		face *faces;
		int nfaces;

		// edges array for static bsp faces
		int *edges,nedges,*faceedges;

		// the bsp tree
		bsp_node *bsp;

		// array of pictures used as texture maps
		picture *piclib[MAX_PICTURES];
		int npiclib;

		// lightmaps
		light_map *lm[MAX_LIGHTMAP];
		light_map_pic *lmpic[MAX_LIGHTMAP];
		int nlm,lmbase,nlmpic;

		// fogmaps
		light_map *fm[MAX_LIGHTMAP];
		light_map_pic *fmpic[MAX_LIGHTMAP];
		int fmbase;

		// the pvs
		char *pvs;
		bsp_node **leaf;
		int nleaf,pvssize,pvsrowsize;

		// draws the scene recusively
		void draw_bsp(int mode=0);

		// draws edges of the selected bsp faces from the draw_bsp function
		void draw_bsp_edges();

		// compute collision
		int collision_bsp(bsp_node *n,vector& p1,vector& p2,int elemtype=0,float rad=0.0f);
		int collision_test(bsp_node *n,vector& p1,vector& p2,int elemtype=0,float rad=0.0f);

		// update scene for elapsed time dt in ms
		void step(int dt);
		int step();

		// recurse bsp calling a custom function
		void apply_bsp(bsp_node *n,vector& p,float rad,void *data,void (*func)(void *data,bsp_object *e));
		void apply_bsp(bsp_node *n,vector *p,int np,void *data,void (*func)(void *data,bsp_object *e));

		// recurse bsp sending messages
		void send_bsp_message(bsp_node *n,vector& p,float rad,int msg,int param,void *data);

		// opens/closes a .fly file
		int open_fly_file(char *file);
		void close_fly_file();
		int save_fly_file(char *file);

		// init/close the texture cache
		int add_lightmap(int sx,int sy);
		void init_texture_cache();
		void close_texture_cache();
	
		// text output functions
		void start_text_mode();
		void end_text_mode();
		int draw_text(int x,int y,char *text);
		int draw_text_center(int x,int y,char *text);
		void set_status_msg(char *fmt, ...);

		// load a picture to the texture cache or
		// return its index if already loaded
		int get_picture(char *file);

		// get objects from the scene
		bsp_object *get_stock_object(char *name);
		bsp_object *get_active_object(char *name);
		mesh *get_model_object(char *name);
		sound *get_sound_object(char *name);
		bezier_curve *get_bezier_curve(char *name);
		bezier_patch *get_bezier_patch(char *name);
		bsp_object *get_next_stock_object(bsp_object *o,int type=0);
		bsp_object *get_next_active_object(bsp_object *o,int type=0);
		
		int set_obj_param(char *objname,char *param,char *value);
		int get_obj_param(char *objname,char *param,char *value);
		int set_global_param(char *name,char *value);
		int get_global_param_desc(int i,param_desc *pd);

		void activate(bsp_object *d,int flag=1);
		void set_camera(bsp_object *d);

		// get a random point iside the level
		bsp_node *get_random_point(vector& v,float mindist);
		bsp_node *find_node(bsp_node *n,vector& v,float mindist);

		int join_multiplayer();
		void close_multiplayer();
		void check_multiplayer();

		flyEngine();
		virtual ~flyEngine()
		{ close_fly_file(); };
};

extern FLY_API flyEngine *flyengine;
extern FLY_API GUID FLYGUID;
extern FLY_API HWND hFlyWnd;
extern FLY_API HINSTANCE hFlyInst;

FLY_API void init_engine(HWND hWnd,HINSTANCE hInst,int appid=FLYAPPID_NONE);
FLY_API void set_engine(flyEngine *eng,HWND hWnd,HINSTANCE hInst,int appid=FLYAPPID_NONE);
FLY_API void free_engine();

FLY_API BOOL FAR PASCAL MultiplayerProc(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam);
