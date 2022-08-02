#include "../Fly3D.h"

int import3ds::read_chunk()
{
	int i=0;

	i+=fp.read(&chunkid, 2);//fread(&chunkid,1,2,fp);
	i+=fp.read(&chunklen, 4);//fread(&chunklen,1,4,fp);
	if (i!=6)
		return 0;
	if (chunklen>6)
		chunklen-=6;
	filepos+=6;
	
	return 1;
}

void import3ds::jump_chunk()
{
	fp.seek(chunklen);//fseek(fp,chunklen,SEEK_CUR);
	filepos+=chunklen;
}

void import3ds::load_chunk()
{
	if (chunk)
		delete chunk;
	chunk=new char[chunklen];
	filepos+=chunklen;
	fp.read(chunk, chunklen);//fread(chunk,chunklen,1,fp);
}

void import3ds::load_string(char *str)
{
	int a=0;

	while( (fp.read(&str[a],1)==1) && str[a++] );

	chunklen-=a;
	filepos+=a;
}

void import3ds::load_object()
{
	char objname[256];

	load_string(objname);
	read_chunk();
	switch(chunkid)
	{
		case 0x4600:
		{
			load_light(objname);
			break;
		}
		case 0x4700:
		{
			load_chunk();
			camera(objname, (float *)chunk,(float *)&chunk[12], *((float *)&chunk[24]), *((float *)&chunk[28]));
			break;
		}
		case 0x4100:
		{
			if (object_name(objname))
				load_mesh(objname);
			else jump_chunk();
			break;
		}
		default:
			jump_chunk();
	}
}

void import3ds::load_mesh(char *objname)
{
	int nvert=0,nfaces=0,ntextcoord=0,nfacematerial=0;
	char *vert=0,*faces=0,*textcoord=0,*facematerial=0;
	float local_axis[12]={ 1,0,0, 0,1,0, 0,0,1, 0,0,0 };
	int a,fpos=filepos+chunklen;
	while( filepos<fpos)
	{
		read_chunk();
		switch(chunkid)
		{
		case 0x4110:
			{
			load_chunk();
			nvert=*((unsigned short *)chunk);
			vert=chunk;
			chunk=0;
			break;
			}
		case 0x4120:
			{
			int fpos2=filepos+chunklen;
			fp.read(&nfaces, 2);//fread(&nfaces,2,1,fp);
			faces=new char[nfaces*2*4+2];
			fp.read(&faces[2], nfaces*2*4);//fread(&faces[2],nfaces*2,4,fp);
			filepos+=nfaces*2*4+2;
			*((unsigned short *)faces)=nfaces;
			while( filepos<fpos2)
				{
				read_chunk();
				switch(chunkid)
					{
					case 0x4130:
						{
						load_chunk();
						if (nfacematerial==0)
							{
							facematerial=chunk;
							chunk=0;
							nfacematerial=chunklen;
							}
						else 
							{
							char *temp=new char[nfacematerial+chunklen];
							memcpy(temp,facematerial,nfacematerial);
							memcpy(&temp[nfacematerial],chunk,chunklen);
							delete facematerial;
							facematerial=temp;
							nfacematerial+=chunklen;
							}
						break;
						}
					default: jump_chunk();
					}
				}
			break;
			}
		case 0x4140:
			{
			load_chunk();
			ntextcoord=*((unsigned short *)chunk);
			textcoord=chunk;
			chunk=0;
			}
			break;
		case 0x4160:
			{
			load_chunk();
			memcpy(local_axis,chunk,sizeof(float)*12);
			}
			break;
		default:
			jump_chunk();
		}
	}
	if (nvert!=0 && nfaces!=0)
	{
	local_axis[9]*=masterscale*scale;
	local_axis[10]*=masterscale*scale;
	local_axis[11]*=masterscale*scale;

	object3d(objname,nvert,nfaces,ntextcoord,local_axis);
	
	for( a=0;a<nvert;a++ )
	{
		float *f=(float *)(2+vert+a*12);
		f[0]*=masterscale*scale;
		f[1]*=masterscale*scale;
		f[2]*=masterscale*scale;
		vertex3(f);
	}
	
	for( a=0;a<ntextcoord;a++ )
	{
		*((float *)(6+textcoord+a*8))*=-1;
		text_coord((float *)(2+textcoord+a*8));
	}

	for( a=0;a<nfaces;a++ )
		face3((unsigned short *)(2+faces+a*8));

	a=0;
	int b,c,len;
	while( a<nfacematerial )
		{
		for( b=0;b<nmat;b++ )
			if (!stricmp(matlib[b].name,&facematerial[a]))
				break;
		c=strlen(&facematerial[a]);
		len=*((unsigned short *)&facematerial[a+c+1]);
		if (b<nmat)
			face_material(&matlib[b],len,(unsigned short *)&facematerial[a+c+3]);
		a+=len*2+c+3;
		}
	}
	if (vert)
		delete vert;
	if (faces)
		delete faces;
	if (facematerial)
		delete facematerial;
	if (textcoord)
		delete textcoord;
}

void import3ds::load_light(char *objname)
{
	float pos[3],target[3],color[3],hotspot,falloff;
	int type=0;
	int fpos=filepos+chunklen;
	fp.read(pos,12);//fread(pos,12,1,fp);
	filepos+=12;
	while( filepos<fpos )
	{
		read_chunk();
		switch(chunkid)
		{
			case 0x0010:
				load_chunk();
				color[0]=*((float *)&chunk[0]);
				color[1]=*((float *)&chunk[4]);
				color[2]=*((float *)&chunk[8]);
				break;
			case 0x0011:
				load_chunk();
				color[0]=(float)(((unsigned char)chunk[0])/255.0);
				color[1]=(float)(((unsigned char)chunk[1])/255.0);
				color[2]=(float)(((unsigned char)chunk[2])/255.0);
				break;
			case 0x4610:
				load_chunk();
				target[0]=*((float *)&chunk[0]);
				target[1]=*((float *)&chunk[4]);
				target[2]=*((float *)&chunk[8]);
				hotspot=*((float *)&chunk[12]);
				falloff=*((float *)&chunk[16]);
				type=1;
				break;

			default:
				jump_chunk();
		}
	}
	if (type)
		spotlight(objname, pos, target, color, hotspot, falloff);
	else pointlight(objname, pos, color);
}

int import3ds::import(char *name,float scalefactor)
{
	scale=scalefactor;
	//fp=fopen(name,"rb");
	if (!fp.open(name))
		return 0;

	while(read_chunk())
		switch(chunkid)
		{
		case M3DMAGIC:
		case MDATA:
			break;
		case MASTER_SCALE:
			{
			load_chunk();
			masterscale=*((float *)chunk);
			}
			break;
		case NAMED_OBJECT:
			load_object();
			break;
		case MAT_ENTRY:
			load_material();
			matlib[nmat-1].ambient[3]=matlib[nmat-1].transparency;
			matlib[nmat-1].diffuse[3]=matlib[nmat-1].transparency;
			matlib[nmat-1].specular[3]=matlib[nmat-1].transparency;
			break;
		default:
			jump_chunk();
		}

	fp.close();//fclose(fp);
	return 1;
}

void import3ds::load_mapping(struct mapping *m)
{
	int fpos=filepos+chunklen;

	m->u_scale=1.0;
	m->v_scale=1.0;
	m->u_offset=0.0;
	m->v_offset=0.0;
	m->rotation=0.0;

	while( filepos<fpos )
	{
		read_chunk();
		switch(chunkid)
		{
		case 0x0030:
			load_chunk();
			m->amount=*((short int *)chunk);
			break;
		case 0xA300:
			load_string(m->filename);
			break;
		case 0xA351:
			load_chunk();
			m->options=*((short int *)chunk);
			break;
		case 0xA353:
			load_chunk();
			m->filtering=*((float *)chunk);
			break;
		case 0xA354:
			load_chunk();
			m->u_scale=*((float *)chunk);
			break;
		case 0xA356:
			load_chunk();
			m->v_scale=*((float *)chunk);
			break;
		case 0xA358:
			load_chunk();
			m->u_offset=*((float *)chunk);
			break;
		case 0xA35A:
			load_chunk();
			m->v_offset=*((float *)chunk);
			break;
		case 0xA35C:
			load_chunk();
			m->rotation=*((float *)chunk);
			break;
		default:
			jump_chunk();
		}
	}
}

void import3ds::load_material()
{
	int fpos=filepos+chunklen;
	while( filepos<fpos )
	{
		read_chunk();
		switch(chunkid)
		{
			case 0xA000:
				if (matlib)
					{
					material *temp=new material[nmat+1];
					memcpy(temp,matlib,sizeof(material)*nmat);
					delete matlib;
					matlib=temp;
					} else matlib=new material;
				load_string(matlib[nmat].name);
				nmat++;
				break;
			case 0xA010:
				load_chunk();
				matlib[nmat-1].ambient[0]=(float)(((unsigned char)chunk[6])/255.0);
				matlib[nmat-1].ambient[1]=(float)(((unsigned char)chunk[7])/255.0);
				matlib[nmat-1].ambient[2]=(float)(((unsigned char)chunk[8])/255.0);
				break;
			case 0xA020:
				load_chunk();
				matlib[nmat-1].diffuse[0]=(float)(((unsigned char)chunk[6])/255.0);
				matlib[nmat-1].diffuse[1]=(float)(((unsigned char)chunk[7])/255.0);
				matlib[nmat-1].diffuse[2]=(float)(((unsigned char)chunk[8])/255.0);
				break;
			case 0xA030:
				load_chunk();
				matlib[nmat-1].specular[0]=(float)(((unsigned char)chunk[6])/255.0);
				matlib[nmat-1].specular[1]=(float)(((unsigned char)chunk[7])/255.0);
				matlib[nmat-1].specular[2]=(float)(((unsigned char)chunk[8])/255.0);
				break;
			case 0xA040:
				load_chunk();
				matlib[nmat-1].shininess=(float)(((unsigned char)chunk[6])/100.0);
				break;
			case 0xA041:
				load_chunk();
				matlib[nmat-1].shininess_strength=(float)(((unsigned char)chunk[6])/100.0);
				break;
			case 0xA050:
				load_chunk();
				matlib[nmat-1].transparency=(float)(((unsigned char)chunk[6])/100.0);
				break;
			case 0xA052:
				load_chunk();
				matlib[nmat-1].transparency_falloff=(float)(((unsigned char)chunk[6])/100.0);
				break;
			case 0xA053:
				load_chunk();
				matlib[nmat-1].reflect_blur=(float)(((unsigned char)chunk[6])/100.0);
				break;
			case 0xA100:
				load_chunk();
				matlib[nmat-1].material_type=*((short *)chunk);
				break;
			case 0xA084:
				load_chunk();
				matlib[nmat-1].self_illum=(float)(((unsigned char)chunk[6])/100.0);
				break;
			case 0xA200:
				load_mapping(&matlib[nmat-1].map_texture1);
				break;
			case 0xA33A:
				load_mapping(&matlib[nmat-1].map_texture2);
				break;
			case 0xA210:
				load_mapping(&matlib[nmat-1].map_opacity);
				break;
			case 0xA230:
				load_mapping(&matlib[nmat-1].map_bump);
				break;
			case 0xA204:
				load_mapping(&matlib[nmat-1].map_specular);
				break;
			case 0xA33C:
				load_mapping(&matlib[nmat-1].map_shininess);
				break;
			case 0xA33D:
				load_mapping(&matlib[nmat-1].map_selfillum);
				break;
			case 0xA220:
				load_mapping(&matlib[nmat-1].map_reflection);
				break;
			default:
				jump_chunk();
		}
	}
}
