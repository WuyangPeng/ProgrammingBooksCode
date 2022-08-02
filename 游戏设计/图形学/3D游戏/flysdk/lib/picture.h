#include "jpg.h"

class FLY_API picture;
class FLY_API textcache;
class FLY_API textcacheGL;

extern FLY_API textcache *tc;
extern FLY_API int textfilter;
extern FLY_API int mipmap;

class FLY_API picture
{
	public:

		char name[256];

		int sx,sy,bytespixel,size;

		unsigned char **buf;

	picture();
	virtual ~picture();

	int  LoadTGA(char *file);
	int  SaveTGA(char *file);
	int  LoadPIC(char *file);
	int  LoadJPG(char *file);

	int  CreatePicture32(int xd,int yd);
	int  CreatePicture24(int xd,int yd);
	int  CreateNormalMap(float scale);
	void FreePicture(void);
};

class FLY_API textcache
{
public:
	int curpic[MAX_TEXTURE_UNITS];
	int npic,curtextunit;

	virtual void use(int pic=-1,int textunit=0)=0;
	virtual void use_triangles(int pic=-1,int textunit=0)=0;
	virtual void init(int np,picture **pic)=0;
	
	virtual int add_picture(int sx,int sy,int bytespixel,unsigned char *lm)=0;
	virtual void update_picture(int picnum,int sx,int sy,int bytespixel,unsigned char *buf)=0;
	virtual void update_sub_picture(int picnum,int x,int y,int sx,int sy,int bytespixel,unsigned char *buf)=0;

	textcache() 
	{ 
		memset(curpic,-1,sizeof(int)*MAX_TEXTURE_UNITS);
		npic=0; 
		curtextunit=0;
	};
		
	virtual ~textcache() { };
};

class FLY_API textcacheGL : public textcache
{
	void reset();
	void load_tex(int pic,int sx,int sy,int bytespixel,unsigned char *buf);
	void free_tex(int pic);

public:
	textcacheGL();
	~textcacheGL();

	unsigned *tex;
	
	int add_picture(int sx,int sy,int bytespixel,unsigned char *buf);
	void update_picture(int picnum,int sx,int sy,int bytespixel,unsigned char *buf);
	void update_sub_picture(int picnum,int x,int y,int sx,int sy,int bytespixel,unsigned char *buf);

	inline void use(int pic=-1,int textunit=0)
	{
	if (curpic[textunit]!=pic)
		{
		if (curtextunit!=textunit)
			{
			glActiveTextureARB(GL_TEXTURE0_ARB+textunit);
			curtextunit=textunit;
			}
		if (pic==-1)
			glDisable(GL_TEXTURE_2D);
		else 
			{
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D,tex[pic]);
			}
		curpic[curtextunit]=pic;
		}
	}
	inline void use_triangles(int pic=-1,int textunit=0)
	{
	if (curpic[textunit]!=pic)
		{
		glEnd();
		if (curtextunit!=textunit)
			{
			glActiveTextureARB(GL_TEXTURE0_ARB+textunit);
			curtextunit=textunit;
			}
		if (pic==-1)
			glDisable(GL_TEXTURE_2D);
		else 
			{
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D,tex[pic]);
			}
		curpic[curtextunit]=pic;
		glBegin(GL_TRIANGLES);
		}
	}

	void init(int np,picture **pic);
};

