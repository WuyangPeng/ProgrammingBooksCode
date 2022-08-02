#define FRAND (((rand()%10000)-5000)/5000.0f)
#define FABSRAND ((rand()%10000)/10000.0f)

#define vec_dot(v1,v2) ((v1).x*(v2).x+(v1).y*(v2).y+(v1).z*(v2).z)

#define SMALL 1.0e-4f
#define BIG   1.0e+10f
#define ISZERO(a) ((a)>-SMALL && (a)<SMALL)

#define M_Pi2			1.570796326795f
#define M_Pi			3.14159265359f
#define M_2Pi			6.28318530718f
#define PiOver180		1.74532925199433E-002f
#define PiUnder180		5.72957795130823E+001f
#define PiOver180		1.74532925199433E-002f

#define FP_BITS(fp) (*(DWORD *)&(fp))
#define FP_ABS_BITS(fp) (FP_BITS(fp)&0x7FFFFFFF)
#define FP_SIGN_BIT(fp) (FP_BITS(fp)&0x80000000)
#define FP_ONE_BITS 0x3F800000

//#define P3SIMD

class FLY_API vector;		// 4 floats
class FLY_API quaternion;	// 4 floats
class FLY_API mat4x4;		// 16 floats

class FLY_API vector
{
	public:
		float x,y,z,w;

	inline vector() 
	{ ; };
	inline vector(float x0,float y0,float z0)
	{ x=x0; y=y0; z=z0; };
	inline vector(float x0,float y0,float z0,float w0)
	{ x=x0; y=y0; z=z0; w=w0; };
	inline vector(vector &v) 
	{ *this=v; };
	inline void null(void)
	{ x=y=z=0; };
	inline float length(void)
	{ return (float)sqrt(x*x+y*y+z*z); };
	inline void  vec(float x0,float y0,float z0)
	{ x=x0; y=y0; z=z0; };
	inline void  vec(float x0,float y0,float z0,float w0)
	{ x=x0; y=y0; z=z0; w=w0; };
	inline void  negate(void)
	{ x=-x; y=-y; z=-z; };
	inline void cross(vector& v1,vector& v2)
	{
#ifdef P3SIMD
		__asm
		{
		mov esi, v1
		mov edi, v2

		movups xmm0, [esi]
		movups xmm1, [edi]
		movups xmm2, xmm0
		movups xmm3, xmm1

		shufps xmm0, xmm0, 0xc9
		shufps xmm1, xmm1, 0xd2
		mulps xmm0, xmm1

		shufps xmm2, xmm2, 0xd2
		shufps xmm3, xmm3, 0xc9
		mulps xmm2, xmm3

		subps xmm0, xmm2

		mov esi, this
		movups [esi],xmm0
		}
#else
		x=v1.y*v2.z-v1.z*v2.y;
		y=v1.z*v2.x-v1.x*v2.z;
		z=v1.x*v2.y-v1.y*v2.x;
#endif
	}
	inline void normalize(void)
	{
     float len=(float)sqrt(x*x+y*y+z*z);
     if (FP_BITS(len)==0) return;
	 len=1.0f/len;
     x*=len; y*=len; z*=len;
	}
	inline float& operator[](int i) { return (&x)[i]; };
};

class FLY_API mat4x4
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

	void set_rotation( float ang,vector& dir );
	void rotate( float ang,vector& dir );
	void lerp(mat4x4& m1,mat4x4& m2,float t);

	inline mat4x4 operator*(mat4x4& m1)
	{
	  mat4x4 m2;
#ifdef P3SIMD
	  __asm
	  {
		mov edi,m1
		movups xmm4,[edi]
		movups xmm5,[edi+16]
		movups xmm6,[edi+32]
		movups xmm7,[edi+48]

		mov esi,this
		mov	eax,0

		LOOP:
		movups xmm0,[esi+eax]
		movups xmm1,xmm0
		movups xmm2,xmm0
		movups xmm3,xmm0

		shufps xmm0,xmm2,0x00
		shufps xmm1,xmm2,0x55
		shufps xmm2,xmm2,0xAA
		shufps xmm3,xmm3,0xFF
		
		mulps xmm0,[edi]
		mulps xmm1,[edi+16]
		mulps xmm2,[edi+32]
		mulps xmm3,[edi+48]

		addps xmm0,xmm1
		addps xmm0,xmm2
		addps xmm0,xmm3

		movups m2+eax,xmm0

		add eax, 16
		cmp	eax, 48
		jle LOOP
	  }
#else
	  int i,j,k;
	  float ab;

	  for(i=0; i<4; i++)
		for(j=0; j<4; j++)
		{
		  ab=0;
		  for(k=0; k<4; k++)
			   ab+=m[i][k]*m1.m[k][j];
		  m2.m[i][j]=ab;
		}
#endif
	  return m2;
	};
};

class FLY_API quaternion : public vector
{
public:
	quaternion() {};
	quaternion(mat4x4 &mat);
	quaternion(float angle, vector &axis)
	{
		float f=(float)sin(angle*PiOver180*0.5f);
		x=axis.x*f;
		y=axis.y*f;
		z=axis.z*f;
		w=(float)cos(angle*PiOver180*0.5f);
	};

	void normalize();
	void get_mat(mat4x4 &mat);
	void get_rotate(float &angle, vector &axis);
	void lerp(quaternion& q1,quaternion& q2,float t);

	quaternion operator *(quaternion &q);
	quaternion operator +(quaternion &q)
	{
		quaternion res;
		res.x=x+q.x;
		res.y=y+q.y;
		res.z=z+q.z;
		res.w=w+q.w;
		return res;
	};
};

inline void operator*=(vector& v,float f)
{
  v.x*=f; v.y*=f; v.z*=f;
}
inline void operator/=(vector& v,float f)
{
  v.x/=f; v.y/=f; v.z/=f;
}
inline void operator-=(vector& v1,vector& v2)
{
  v1.x-=v2.x; v1.y-=v2.y; v1.z-=v2.z;
}
inline void operator+=(vector& v1,vector& v2)
{
  v1.x+=v2.x; v1.y+=v2.y; v1.z+=v2.z;
}
inline void operator*=(vector& v1,vector& v2)
{
  v1.x*=v2.x; v1.y*=v2.y; v1.z*=v2.z;
}
inline void operator/=(vector& v1,vector& v2)
{
  v1.x/=v2.x; v1.y/=v2.y; v1.z/=v2.z;
}
inline vector operator-(vector v1,vector& v2)
{
   v1.x-=v2.x; v1.y-=v2.y; v1.z-=v2.z;
   return v1;
}
inline vector operator+(vector v1,vector& v2)
{
   v1.x+=v2.x; v1.y+=v2.y; v1.z+=v2.z;
   return v1;
}
inline vector operator*(vector v1,vector& v2)
{
   v1.x*=v2.x; v1.y*=v2.y; v1.z*=v2.z;
   return v1;
}
inline vector operator/(vector v1,vector& v2)
{
   v1.x/=v2.x; v1.y/=v2.y; v1.z/=v2.z;
   return v1;
}
inline vector operator*(float f,vector v)
{
   v.x*=f; v.y*=f; v.z*=f;
   return v;
}
inline vector operator*(vector v,float f)
{
   v.x*=f; v.y*=f; v.z*=f;
   return v;
}
inline vector operator/(vector v,float f)
{
   v.x/=f; v.y/=f; v.z/=f;
   return v;
}

inline vector operator*(vector& v,mat4x4& m)
{
  vector a;
#ifdef P3SIMD
	v.w=1.0f;
	__asm
	{
		mov esi, v
		mov edi, m

		movups xmm0,[esi]
		movups xmm1,xmm0
		movups xmm2,xmm0
		movups xmm3,xmm0

		shufps xmm0,xmm2,0x00
		shufps xmm1,xmm2,0x55
		shufps xmm2,xmm2,0xAA
		shufps xmm3,xmm3,0xFF
		
		movups xmm4,[edi]
		movups xmm5,[edi+16]
		movups xmm6,[edi+32]
		movups xmm7,[edi+48]

		mulps xmm0,xmm4
		mulps xmm1,xmm5
		mulps xmm2,xmm6
		mulps xmm3,xmm7

		addps xmm0,xmm1
		addps xmm0,xmm2
		addps xmm0,xmm3

		movups a,xmm0
	}
#else
	float *f=&a.x;
	for(int j=0; j<3; j++,f++ )
	{
		*f=0;
		for(int i=0; i<3; i++)
			*f+=*(&v.x+i)*m.m[i][j];
		*f+=m.m[i][j];
	}
#endif
  return a;
}
inline vector operator*(mat4x4& m,vector& v)
{
  vector a;
#ifdef P3SIMD
	v.w=1.0f;
	__asm
	{
		mov esi, v
		mov edi, m

		movups xmm0,[esi]
		movups xmm1,xmm0
		movups xmm2,xmm0
		movups xmm3,xmm0

		shufps xmm0,xmm2,0x00
		shufps xmm1,xmm2,0x55
		shufps xmm2,xmm2,0xAA
		shufps xmm3,xmm3,0xFF
		
		movups xmm4,[edi]
		movups xmm5,[edi+16]
		movups xmm6,[edi+32]
		movups xmm7,[edi+48]

		mulps xmm0,xmm4
		mulps xmm1,xmm5
		mulps xmm2,xmm6
		mulps xmm3,xmm7

		addps xmm0,xmm1
		addps xmm0,xmm2
		addps xmm0,xmm3

		movups a,xmm0
	}
#else
	float *f=&a.x;
	for(int j=0; j<3; j++,f++ )
	{
		*f=0;
		for(int i=0; i<3; i++)
			*f+=*(&v.x+i)*m.m[i][j];
		*f+=m.m[i][j];
	}
#endif
  return a;
}

