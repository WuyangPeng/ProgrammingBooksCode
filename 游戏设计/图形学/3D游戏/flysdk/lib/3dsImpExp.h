#define MASTER_SCALE 0x100
#define M3DMAGIC 0x4d4d
#define M3D_VERSION 0x0002
#define COLOR_24 0x0011
#define INT_PERCENTAGE 0x0030
#define MDATA 0x3d3d
#define MAT_ENTRY 0xafff
#define MAT_NAME 0xa000
#define MAT_AMBIENT 0xa010
#define MAT_DIFFUSE 0xa020
#define MAT_SPECULAR 0xa030
#define MAT_SHININESS 0xa040
#define MAT_SHININESS_STRENGTH 0xa041
#define MAT_TRANSPARENCY 0xa050
#define MAT_TRANSPARENCY_FALLOFF 0xa052
#define MAT_REFLECT_BLUR 0xa053
#define MAT_SELF_ILLUM 0xa084
#define MAT_SHADING 0xa100
#define MAT_MAP_TEXTURE1 0xa200
#define MAT_MAP_SPECULAR 0xa204
#define MAT_MAP_OPACITY 0xa210
#define MAT_MAP_REFLECTION 0xa220
#define MAT_MAP_BUMP 0xa230
#define MAT_MAP_TEXTURE2 0xa33a
#define MAT_MAP_SHININESS 0xa33c
#define MAT_MAP_SELFILLUM 0xa33d
#define MESH_VERSION 0x3d3e
#define MAPP_FILENAME 0xa300
#define MAPP_OPTIONS 0xa351
#define MAPP_FILTERING 0xa353
#define MAPP_U_SCALE 0xa354
#define MAPP_V_SCALE 0xa356
#define MAPP_U_OFFSET 0xa358
#define MAPP_V_OFFSET 0xa35a
#define MAPP_ROTATION 0xa35C
#define NAMED_OBJECT 0x4000
#define N_TRI_OBJECT 0x4100
#define POINT_ARRAY 0x4110
#define FACE_ARRAY 0x4120
#define MSH_MAT_GROUP 0x4130
#define TEXT_COORD 0x4140
#define SMOOTH_GROUP 0x4150
#define LOCAL_AXIS 0x4160
#define N_CAM_OBJECT 0x4700
#define N_DIRECT_LIGHT 0x4600
#define DL_SPOTLIGHT 0x4610

#define SizeofChunk 6

struct mapping
{
	char filename[256];
	short int type,amount,options;
	float filtering;
	float u_scale,v_scale,u_offset,v_offset;
	float rotation;
	int piclibindx;
};

class material
{
public:
	float reflection;
	float ambient[4];
	float diffuse[4];
	float specular[4];
	float shininess;
	float shininess_strength;
	float transparency;
	float transparency_falloff;
	float reflect_blur;
	short int material_type;
	float self_illum;

	char name[256];

	struct mapping 
		map_texture1,map_texture2,
		map_opacity,map_bump,map_specular,
		map_shininess,map_selfillum,map_reflection;

	material()
	{
		memset(this,0,sizeof(material));
	}

	int l;
};

class FLY_API export3ds
{
public:
	FILE *m_fp;

	export3ds(char *, float, material *, int);
	~export3ds(void);
	void WriteNamedObject(
		char *, float *, float *,
		unsigned short, unsigned short *, 
		unsigned short, unsigned short *, 
		int, material *,float *);
	void close();

private:
	long MDATA_size, MDATA_bpatch;
	long M3DMAGIC_size, M3DMAGIC_bpatch;

	void WriteString(char *);
	void WriteUShort(unsigned short);
	void WriteULong(unsigned long);
	void WriteLong(long);
	void WriteByte(char);
	void WriteShort(short);
	void WriteFloat(float);
	void WriteUByte(unsigned char);
	long WriteChunk(unsigned short, long);
	long WritePatch(long, long);
	void WriteMData_Ini(material *, int);
	long WriteMData_Fim();
	long WriteMeshVersion(long);
	long WriteMatEntries(material *, int);
	long WriteChunkString(unsigned short, char *);
	long WriteChunkMapping(unsigned short, struct mapping *);
	long WriteColor(float [3]);
	long WriteTriObject(
		float *, float *, unsigned short,
		unsigned short *, unsigned short,
		unsigned short *, int, material *,float *);
	long WritePointArray(float *, unsigned short);
	long WriteFaceArray(
		unsigned short *, unsigned short, unsigned short *,
		int, material *);
	long WriteMaterial(unsigned short *, int, material *);
	long WriteTextCoord(float *, unsigned short);
	long WriteO();
	long WriteMasterScale();
};

class FLY_API import3ds
{
	fly_pak fp;
	char *chunk;
	int chunklen;
	unsigned short chunkid;
	int filepos,nmat;
	material *matlib;
	float masterscale,scale;
	
	virtual void object3d(char *name,int nv,int nf,int ntc,float *local_axis)
	{ ; };
	virtual void vertex3(float *vec)
	{ ; };
	virtual void text_coord(float *uv)
	{ ; };
	virtual void face3(unsigned short *fa)
	{ ; };
	virtual void camera(char *name, float *pos, float *target, float bank, float lens)
	{ ; };
	virtual void pointlight(char *name, float *pos,float *color)
	{ ; };
	virtual void spotlight(char *name, float *pos,float *target,float *color,float hotspot,float falloff)
	{ ; };
	virtual void face_material(material *mat,int nf,unsigned short *faces)
	{ ;	};
	virtual int object_name(char *name)
	{ return 1;	};

	int read_chunk();
	void jump_chunk();
	void load_chunk();
	void load_object();
	void load_string(char *str);
	void load_light(char *objname);
	void load_mesh(char *objname);
	void load_mapping(struct mapping *mat);
	void load_material();

public:
	import3ds() 
		{ 
		chunk=0; chunklen=0; nmat=0; matlib=0; masterscale=1.0f; scale=1.0; filepos=0;
		};
	~import3ds() 
		{ 
		if (chunk) delete chunk; 
		if (matlib) delete matlib; 
		};
	int import(char *name,float scalefactor);
};