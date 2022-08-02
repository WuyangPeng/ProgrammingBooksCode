/*
========================================================================

.MD2 triangle model file format

========================================================================
*/

#define IDALIASHEADER		(('2'<<24)+('P'<<16)+('D'<<8)+'I')
#define ALIAS_VERSION	8

#define	MAX_TRIANGLES	4096
#define MAX_VERTS		2048
#define MAX_FRAMES		512
#define MAX_MD2SKINS	32
#define	MAX_SKINNAME	64

typedef struct
{
	short	s;
	short	t;
} dstvert_t;

typedef struct 
{
	short	index_xyz[3];
	short	index_st[3];
} dtriangle_t;

typedef struct
{
	byte	v[3];			// scaled byte to fit in frame mins/maxs
	byte	lightnormalindex;
} dtrivertx_t;

typedef struct
{
	float u,v;
	int index_vert;
} dcomandvertex_t;

#define DTRIVERTX_V0   0
#define DTRIVERTX_V1   1
#define DTRIVERTX_V2   2
#define DTRIVERTX_LNI  3
#define DTRIVERTX_SIZE 4

typedef struct
{
	float		scale[3];	// multiply byte verts by this
	float		translate[3];	// then add this
	char		name[16];	// frame name from grabbing
	dtrivertx_t	verts[1];	// variable sized
} daliasframe_t;


// the glcmd format:
// a positive integer starts a tristrip command, followed by that many
// vertex structures.
// a negative integer starts a trifan command, followed by -x vertexes
// a zero indicates the end of the command list.
// a vertex consists of a floating point s, a floating point t,
// and an integer vertex index.


typedef struct
{
	int			ident;
	int			version;

	int			skinwidth;
	int			skinheight;
	int			framesize;		// byte size of each frame

	int			num_skins;
	int			num_xyz;
	int			num_st;			// greater than num_xyz for seams
	int			num_tris;
	int			num_glcmds;		// dwords in strip/fan command list
	int			num_frames;

	int			ofs_skins;		// each skin is a MAX_SKINNAME string
	int			ofs_st;			// byte offset from start for stverts
	int			ofs_tris;		// offset for dtriangles
	int			ofs_frames;		// offset for first frame
	int			ofs_glcmds;	
	int			ofs_end;		// end of file

} dmdl_t;



#define PiOver180		1.74532925199433E-002f

class vector
{
	public:
		float x,y,z;

	vector() 
	{ ; };
	inline vector(float x0,float y0,float z0)
	{ x=x0; y=y0; z=z0; };
	vector(vector &v) 
	{ *this=v; };
	inline void null(void)
	{ x=y=z=0; };
	inline float length(void)
	{ return (float)sqrt(x*x+y*y+z*z); };
	inline void  vec(float x0,float y0,float z0)
	{ x=x0; y=y0; z=z0; };
	inline void  negate(void)
	{ x=-x; y=-y; z=-z; };
	inline void cross(vector& v1,vector& v2)
	{
     x=v1.y*v2.z-v1.z*v2.y;
     y=v1.z*v2.x-v1.x*v2.z;
     z=v1.x*v2.y-v1.y*v2.x;
	}
	inline int normalize(void)
	{
     float len=(float)sqrt(x*x+y*y+z*z);
     if (len<0.0f)
        return 0;
     x/=len; y/=len; z/=len;
     return 1;
	}
	inline float operator[](int i) { return (&x)[i]; };
};

class mat4x4
{
public:
	float m[4][4];

	inline void null(void)
	{
		memset(&m,0,sizeof(m));
	}
	inline void load_identity(void)
	{
		 memset(m,0,sizeof(m));
		 m[0][0]=m[1][1]=m[2][2]=m[3][3]=1.0;
	}

	void set_rotation( vector& dir, float rad )
	{
		static mat4x4 m;

		rad*=-PiOver180;

		float fCos=(float)cos( rad );
		float fSin=(float)sin( rad );

		m.m[0][0] = ( dir.x * dir.x ) * ( 1 - fCos ) + fCos;
		m.m[0][1] = ( dir.x * dir.y ) * ( 1 - fCos ) - (dir.z * fSin);
		m.m[0][2] = ( dir.x * dir.z ) * ( 1 - fCos ) + (dir.y * fSin);

		m.m[1][0] = ( dir.y * dir.x ) * ( 1 - fCos ) + (dir.z * fSin);
		m.m[1][1] = ( dir.y * dir.y ) * ( 1 - fCos ) + fCos ;
		m.m[1][2] = ( dir.y * dir.z ) * ( 1 - fCos ) - (dir.x * fSin);

		m.m[2][0] = ( dir.z * dir.x ) * ( 1 - fCos ) - (dir.y * fSin);
		m.m[2][1] = ( dir.z * dir.y ) * ( 1 - fCos ) + (dir.x * fSin);
		m.m[2][2] = ( dir.z * dir.z ) * ( 1 - fCos ) + fCos;
    
		m.m[0][3] = m.m[1][3] = m.m[2][3] = 0;
		m.m[3][1] = m.m[3][2] = m.m[3][3] = 0;
		m.m[3][3] = 1;

		*this=*this*m;
	}

	inline mat4x4 operator*(mat4x4& m1)
	{
	  int i,j,k;
	  float ab;
	  mat4x4 m2;

	  for(i=0; i<4; i++)
		for(j=0; j<4; j++)
		{
		  ab=0;
		  for(k=0; k<4; k++)
			   ab+=m[i][k]*m1.m[k][j];
		  m2.m[i][j]=ab;
		}
	  return m2;
	};
};

inline vector operator*(vector& v,mat4x4& m)
{
  vector a;
  float *f=&a.x;
  for(int j=0; j<3; j++,f++ )
  {
    *f=0;
    for(int i=0; i<3; i++)
      *f+=*(&v.x+i)*m.m[i][j];
    *f+=m.m[i][j];
  }
  return a;
}
