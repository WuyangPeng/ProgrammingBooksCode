#include "../Fly3D.h"

textcacheGL::textcacheGL()
{
	tex=0;
}

textcacheGL::~textcacheGL()
{
	reset();
}

void textcacheGL::reset()
{
	int i;
	for( i=0;i<npic;i++ )
		free_tex(i);
	if (tex)
		{
		glDeleteTextures(npic,tex);
		delete tex;
		}
	tex=0;
	npic=0;
}

void textcacheGL::init(int np,picture **pic)
{
	reset();
	
	if (np)
		{
		npic=np;
		tex=new unsigned[npic];
		glGenTextures(npic,tex);
		for( int i=0;i<npic;i++)
			if (pic[i]->buf)
				load_tex(i,pic[i]->sx,pic[i]->sy,pic[i]->bytespixel,pic[i]->buf[0]);
		memset(curpic,-1,sizeof(int)*MAX_TEXTURE_UNITS);
		}
}

void textcacheGL::load_tex(int pic,int sx,int sy,int bytespixel,unsigned char *buf)
{
	glBindTexture(GL_TEXTURE_2D,tex[pic]);
	if (bytespixel==4)
		glTexImage2D(GL_TEXTURE_2D,0,4,sx,sy,0,GL_RGBA,GL_UNSIGNED_BYTE,buf);
	else 
		glTexImage2D(GL_TEXTURE_2D,0,3,sx,sy,0,GL_RGB,GL_UNSIGNED_BYTE,buf);

	if (mipmap)
	{
		if (bytespixel==4)
			gluBuild2DMipmaps(GL_TEXTURE_2D,4,sx,sy,GL_RGBA,GL_UNSIGNED_BYTE,buf);
		else
			gluBuild2DMipmaps(GL_TEXTURE_2D,3,sx,sy,GL_RGB,GL_UNSIGNED_BYTE,buf);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,textfilter?GL_LINEAR_MIPMAP_LINEAR:GL_NEAREST);
	}
	else
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,textfilter?GL_LINEAR:GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,textfilter?GL_LINEAR:GL_NEAREST);
}

void textcacheGL::free_tex(int pic)
{
	glBindTexture(GL_TEXTURE_2D,tex[pic]);
	glTexImage2D(GL_TEXTURE_2D,0,3,0,0,0,GL_RGB,GL_UNSIGNED_BYTE,0);
}

int textcacheGL::add_picture(int sx,int sy,int bytespixel,unsigned char *buf)
{
	unsigned *tmp=new unsigned[npic+1];
	if (tex)
		{
		memcpy(tmp,tex,sizeof(unsigned)*npic);
		delete tex;
		}
	tex=tmp;
	
	glGenTextures(1,&tex[npic]);

	glBindTexture(GL_TEXTURE_2D,tex[npic]);
	if (bytespixel==4)
		glTexImage2D(GL_TEXTURE_2D,0,4,sx,sy,0,GL_RGBA,GL_UNSIGNED_BYTE,buf);
	else 
		glTexImage2D(GL_TEXTURE_2D,0,3,sx,sy,0,GL_RGB,GL_UNSIGNED_BYTE,buf);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,textfilter?GL_LINEAR:GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,textfilter?GL_LINEAR:GL_NEAREST);

	return npic++;
}

void textcacheGL::update_picture(int picnum,int sx,int sy,int bytespixel,unsigned char *buf)
{
	glBindTexture(GL_TEXTURE_2D,tex[picnum]);
	if (bytespixel==4)
		glTexImage2D(GL_TEXTURE_2D,0,4,sx,sy,0,GL_RGBA,GL_UNSIGNED_BYTE,buf);
	else 
		glTexImage2D(GL_TEXTURE_2D,0,3,sx,sy,0,GL_RGB,GL_UNSIGNED_BYTE,buf);
}

void textcacheGL::update_sub_picture(int picnum,int x,int y,int sx,int sy,int bytespixel,unsigned char *buf)
{
	glBindTexture(GL_TEXTURE_2D,tex[picnum]);
	if (bytespixel==4)
		glTexSubImage2D(GL_TEXTURE_2D,0,x,y,sx,sy,GL_RGBA,GL_UNSIGNED_BYTE,buf);
	else 
		glTexSubImage2D(GL_TEXTURE_2D,0,x,y,sx,sy,GL_RGB,GL_UNSIGNED_BYTE,buf);
}
