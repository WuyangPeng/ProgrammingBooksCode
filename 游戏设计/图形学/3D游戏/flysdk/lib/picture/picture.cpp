#include "../Fly3D.h"

FLY_API textcache *tc=0;
FLY_API int textfilter=1;
FLY_API int mipmap=1;

picture::picture() 
{ 
	buf=0; 
	name[0]=0; 
	sx=sy=bytespixel=size=0; 
}

picture::~picture() 
{ 
	FreePicture(); 
};

int picture::CreatePicture32(int xd,int yd)
{
    int a;
    sx=xd; sy=yd; bytespixel=4;

	size=sx*sy*bytespixel;

    if ((buf=new unsigned char *[sy])!=0)
       {
		buf[0]=new unsigned char[sx*sy*bytespixel];
		if (!buf[0])
			{
			delete buf;
			buf=0;
			return 0;
			}
        for( a=1;a<sy;a++ )
			buf[a]=&buf[0][a*sx*bytespixel];
		
        return 1;
       }
    return 0;
}

int picture::CreatePicture24(int xd,int yd)
{
    int a;
    sx=xd; sy=yd; bytespixel=3;

	size=sx*sy*bytespixel;

    if ((buf=new unsigned char *[sy])!=0)
       {
		buf[0]=new unsigned char[sx*sy*bytespixel];
		if (!buf[0])
			{
			delete buf;
			buf=0;
			return 0;
			}
        for( a=1;a<sy;a++ )
			buf[a]=&buf[0][a*sx*bytespixel];
		
        return 1;
       }
    return 0;
}

void picture::FreePicture(void)
{
	if (buf)
		{
		delete buf[0];
		delete buf;
		}
	buf=0;
}

int picture::LoadPIC(char *file)
{
	char *c=strrchr(file,'.');
	if (c==0)
		return 0;
	c++;
	
	if (!stricmp(c,"tga"))
		return LoadTGA(file);
	else
	if (!stricmp(c,"jpg"))
		return LoadJPG(file);
	
	return 0;
}

int picture::LoadJPG(char *file)
{
	FreePicture();
	JPEGDATA data;
	fly_pak fp;
	FILE *f;

	f=fp.get_fp(file);
	if (f==0) return 0;
	memset(&data,0,sizeof(JPEGDATA));
	data.input_file=f;
	JpegInfo(&data);
	fclose(f);
	if (data.components==3)
		{
		CreatePicture24(data.width,data.height);

		f=fp.get_fp(file);

		data.ptr             = buf[0];
		data.input_file      = f;
		data.hWnd            = 0;
		data.ProgressMsg     = 0;

		JpegRead(&data);
		fclose(f);

		if (data.status==0)
			return 1;
		}
	return 0;
}

int picture::LoadTGA(char *file)
{
	fly_pak fp;
	int x_pos1, x_pos2, y, i, p, cursize;
	unsigned char flag, TGA_INI[18], pixel_order;

	FreePicture();

	sx=sy=0;

	if(!fp.open(file))
		return 0;

	fp.read((char *)&TGA_INI[0], 18);
		
	if(!((TGA_INI[16]==24 || TGA_INI[16]==32) && (TGA_INI[2]==2 || TGA_INI[2]==10)))
		return 0;

	sx=*((unsigned short *)&TGA_INI[12]);
	sy=*((unsigned short *)&TGA_INI[14]);

	if(TGA_INI[16]==24)
		CreatePicture24(sx,sy);
	else
		CreatePicture32(sx,sy);

	pixel_order=TGA_INI[17]&0x30;

	if(TGA_INI[2]==2)
		fp.read(buf[0], size);
	else
	{
		unsigned char *p=buf[0], *q, c;

		cursize=0;
		while(cursize<sx*sy)
		{
			fp.read(&c, 1);
			if(!(c&0x80))
			{
				c++;
				fp.read(p, c*bytespixel);
				p+=c*bytespixel;
			}
			else
			{
				c=(c&0x7f)+1;
				fp.read(p, bytespixel);
				q=p;
				for(i=1; i<c; i++)
				{
					q+=bytespixel;
					q[0]=p[0];
					q[1]=p[1];
					q[2]=p[2];
				}
				p=q;
				p+=bytespixel;
			}
			cursize+=c;
		}
	}

	if (pixel_order==0x00 || pixel_order==0x10)
		{
		unsigned char *line=new unsigned char[bytespixel*sx];
		for( i=0;i<sy/2;i++ )
			{
			memcpy(line,buf[i],bytespixel*sx);
			memcpy(buf[i],buf[sy-i-1],bytespixel*sx);
			memcpy(buf[sy-i-1],line,bytespixel*sx);
			}
		delete line;
		}

	for( y=0;y<sy;y++ )
	{
		for(p=0; p<sx; p++)
		{
			x_pos1=p*bytespixel;
			flag=buf[y][x_pos1+2];
			buf[y][x_pos1+2]=buf[y][x_pos1];
			buf[y][x_pos1]=flag;
		}
		if(pixel_order==0x10 || pixel_order==0x30)
			for(p=0; p<sx/2; p++)
			{
				x_pos1=p*bytespixel;
				x_pos2=(sx-1-p)*bytespixel;
				for(i=0; i<bytespixel; i++)
				{
					flag=buf[y][x_pos2+i];
					buf[y][x_pos2+i]=buf[y][x_pos1+i];
					buf[y][x_pos1+i]=flag;
				}
			}
	}

	return 1;
}

int picture::SaveTGA(char *file)
{
    FILE *fp;
    int a,b;
    unsigned char TGA_INI[18];
    unsigned char *picline;

    picline=new unsigned char[sx*bytespixel];
    if (!picline)
       return 0;

    if ((fp=fopen(file,"wb"))!=0)
       {
        memset(&TGA_INI[0],0,18);
        TGA_INI[12]=(unsigned char)(sx%256);
        TGA_INI[13]=(unsigned char)(sx/256);
        TGA_INI[14]=(unsigned char)(sy%256);
        TGA_INI[15]=(unsigned char)(sy/256);
        TGA_INI[2]=2;
        TGA_INI[16]=8*bytespixel;
        fwrite((char *)&TGA_INI[0],18,1,fp);
        for( a=sy-1;a>=0;a-- )
             {
              for( b=0;b<sx;b++ )
                   {
                    picline[b*bytespixel]=buf[a][b*bytespixel+2];
                    picline[b*bytespixel+1]=buf[a][b*bytespixel+1];
                    picline[b*bytespixel+2]=buf[a][b*bytespixel];
					if (bytespixel==4)
						picline[b*bytespixel+3]=buf[a][b*bytespixel+3];
                   }
              if (fwrite((char *)picline,sx,bytespixel,fp)!=(unsigned)bytespixel)
                 {
                  fclose(fp);
                  delete picline;
                  return 0;
                 }
             }
        fclose(fp);
       }
    delete picline;
    return 1;
}

int picture::CreateNormalMap(float scale)
{
	if (bytespixel!=4)
		return 0;

	unsigned char *uc=buf[0];
	float c,cx,cy,dcx,dcy,nx,ny,nz;
	int wx=sx*bytespixel;
	int i,j;
	float one255=1.0f/255.0f,len;

	for( i=0;i<sx;i++ )
		for( j=0;j<sy;j++ )
		{
			c = uc[3] * one255;
			cx = buf[i][((j+1)%sx)*4+3] * one255;
			cy = buf[(i+1)%sy][j*4+3] * one255;
			dcx = scale * (c - cx);
			dcy = scale * (c - cy);		

			len = dcx*dcx + dcy*dcy + 1.0f;
			nz = (float)(1.0/sqrt(len));
			nx = dcy*nz;
			ny = -dcx*nz;

			uc[0] = (unsigned char)(128 + 127*nx);
			uc[1] = (unsigned char)(128 + 127*ny);
			uc[2] = (unsigned char)(128 + 127*nz);
			uc+=4;
		}

//	SaveTGA("teste.tga");

	return 1;
}