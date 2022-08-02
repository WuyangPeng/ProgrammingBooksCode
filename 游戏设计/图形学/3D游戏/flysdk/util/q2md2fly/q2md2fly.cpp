#include "windows.h"
#include "stdio.h"
#include "math.h"
#include "q2md2fly.h"

FILE *fm=0,*ff=0;
dmdl_t dmdl;

float vert[MAX_VERTS][3];
float uv[MAX_VERTS][2];
short face[MAX_TRIANGLES][3];
short faceuv[MAX_TRIANGLES][3];
char framename[64]="";
char skinname[64]="";
int nstripfan,stripfancount[MAX_TRIANGLES];
dcomandvertex_t stripfan[MAX_TRIANGLES*3];

void load_faces()
{
	dtriangle_t tri;
	int i;

	fseek(fm,dmdl.ofs_tris,SEEK_SET);
	for( i=0;i<dmdl.num_tris;i++ )
	{
		fread(&tri,1,sizeof(tri),fm);
		face[i][2]=tri.index_xyz[0];
		face[i][1]=tri.index_xyz[1];
		face[i][0]=tri.index_xyz[2];
		faceuv[i][2]=tri.index_st[0];
		faceuv[i][1]=tri.index_st[1];
		faceuv[i][0]=tri.index_st[2];
	}
}

void load_uv()
{
	dstvert_t st;
	int i;

	fseek(fm,dmdl.ofs_st,SEEK_SET);
	for( i=0;i<dmdl.num_st;i++ )
	{
		fread(&st,1,sizeof(st),fm);
		uv[i][0]=(float)st.s/dmdl.skinwidth;
		uv[i][1]=(float)st.t/dmdl.skinheight;
	}
}

void load_frame(int n)
{
	daliasframe_t frame;
	int i;
	mat4x4 mr;
	vector v1,v2;
	v1.vec(1,0,0);
	v2.vec(0,1,0);
	mr.load_identity();
	mr.set_rotation(v1,-90);
	mr.set_rotation(v2,90);

	fseek(fm,dmdl.ofs_frames+dmdl.framesize*n,SEEK_SET);
	fread(&frame,1,sizeof(frame),fm);
	strcpy(framename,frame.name);
	fseek(fm,-(int)sizeof(dtrivertx_t),SEEK_CUR);
	for( i=0;i<dmdl.num_xyz;i++ )
	{
		fread(frame.verts,1,sizeof(dtrivertx_t),fm);
		v1.x=frame.verts->v[0]*frame.scale[0]+frame.translate[0];
		v1.y=frame.verts->v[1]*frame.scale[1]+frame.translate[1];
		v1.z=frame.verts->v[2]*frame.scale[2]+frame.translate[2];
		v2=v1*mr;
		vert[i][0]=v2.x;
		vert[i][1]=v2.y;
		vert[i][2]=v2.z;
	}
}

void write_head()
{
	float f[3]={ 0,0,0 };
	int i;
	
	i=9171;
	fwrite(&i,1,sizeof(int),ff);

	i=dmdl.num_tris;
	fwrite(&i,1,sizeof(int),ff);

	i=dmdl.num_xyz;
	fwrite(&i,1,sizeof(int),ff);

	i=dmdl.num_frames;
	fwrite(&i,1,sizeof(int),ff);

	fwrite(f,3,sizeof(float),ff);

	fwrite(skinname,1,64,ff);

	fwrite(&face[0][0],dmdl.num_tris,sizeof(short)*3,ff);

	for( i=0;i<dmdl.num_tris;i++ )
	{
		fwrite(&uv[faceuv[i][0]],2,sizeof(float),ff);
		fwrite(&uv[faceuv[i][1]],2,sizeof(float),ff);
		fwrite(&uv[faceuv[i][2]],2,sizeof(float),ff);
	}
}

main(int an,char **av)
{
	if (an==2 || an==3)
	{
		fm=fopen(av[1],"rb");
		if (fm)
			{
			fread(&dmdl,1,sizeof(dmdl),fm);
			if (dmdl.ident==IDALIASHEADER && dmdl.version==8)
				{
				char str[256];
				int n=0;
				if (strrchr(av[1],'\\'))
					strcpy(str,strrchr(av[1],'\\')+1);
				else
				if (strrchr(av[1],'/'))
					strcpy(str,strrchr(av[1],'/')+1);
				else
					strcpy(str,av[1]);
				if (strrchr(str,'.'))
					*strrchr(str,'.')=0;
				strcpy(skinname,str);
				strcat(skinname,".tga");
				if (an==3)
				{
					strcat(str,"_");
					strcat(str,av[2]);
				}
				strcat(str,".fao");
				printf("filename  : %s\n",str);
				printf("skinname  : %s\n",skinname);
				ff=fopen(str,"wb");
				if (ff)
					{
					load_faces();
					load_uv();
					printf("num_faces : %i\nnum_verts : %i\nnum_uv    : %i\nnum_frames: %i\n",dmdl.num_tris,dmdl.num_xyz,dmdl.num_st,dmdl.num_frames);
					write_head();

					for( int i=0;i<dmdl.num_frames;i++ )
						{
						load_frame(i);
						if (an==3 && strncmp(framename,av[2],strlen(av[2])))
							continue;
						n++;
						printf("frame %02i  : %s\n",n,framename);
						fwrite(&vert[0][0],dmdl.num_xyz,sizeof(float)*3,ff);
						}

					fseek(fm,dmdl.ofs_glcmds,SEEK_SET);
					nstripfan=0;
					i=0;
					while(1)
					{	
						fread(&stripfancount[nstripfan],1,sizeof(int),fm);
						if (stripfancount[nstripfan]==0) 
							break;
						fread(&stripfan[i],abs(stripfancount[nstripfan]),sizeof(dcomandvertex_t),fm);
						i+=abs(stripfancount[nstripfan]);
						nstripfan++;
					} 
					fwrite(&nstripfan,1,sizeof(int),ff);
					fwrite(&stripfancount[0],nstripfan,sizeof(int),ff);
					fwrite(&i,1,sizeof(int),ff);
					fwrite(&stripfan[0],i,sizeof(dcomandvertex_t),ff);

					fseek(ff,12,SEEK_SET);
					fwrite(&n,1,sizeof(int),ff);
					fclose(ff);
					}
				}
			fclose(fm);
			return 1;
			}
	}
	printf("Fly3D quake2 md2 converter\n");
	printf("use: q2md2fly q2model.md2 [animname]\n");
	return 0;
}
