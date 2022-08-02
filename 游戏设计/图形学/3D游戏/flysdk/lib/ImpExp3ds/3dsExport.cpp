#include "../Fly3D.h"

export3ds::export3ds(char *filename, float scale, material *matlib, int nmatlib)
{
	m_fp=fopen(filename,"wb");
	if(m_fp==NULL)
		return;

	M3DMAGIC_bpatch=WriteChunk(M3DMAGIC, 0);
	M3DMAGIC_size=SizeofChunk;

	WriteChunk(M3D_VERSION, SizeofChunk+sizeof(long));
	WriteLong(4);
	M3DMAGIC_size+=SizeofChunk+sizeof(long);

	WriteChunk(MASTER_SCALE, SizeofChunk+sizeof(float));
	WriteFloat(scale);
	M3DMAGIC_size+=SizeofChunk+sizeof(float);

	WriteMData_Ini(matlib, nmatlib);
}

export3ds::~export3ds()
{
	if(m_fp!=NULL)
		close();
}

void export3ds::close()
{
	if(m_fp==NULL)
		return;
	M3DMAGIC_size+=WriteMData_Fim();
	WritePatch(M3DMAGIC_bpatch, M3DMAGIC_size);
	fclose(m_fp);
	m_fp=NULL;
}

long export3ds::WriteChunk(unsigned short id, long size)
{
	long retval;

	WriteUShort(id);
	retval=ftell(m_fp);
	WriteULong((unsigned long) size);

	return retval;
}

long export3ds::WritePatch(long location, long data)
{
	long current=ftell(m_fp);
	fseek(m_fp, location, SEEK_SET);
	WriteLong(data);
	fseek(m_fp, current, SEEK_SET);

	return current;
}

void export3ds::WriteMData_Ini(material *matlib, int nmatlib)
{
	MDATA_bpatch=WriteChunk(MDATA, 0);
	MDATA_size=SizeofChunk;
	MDATA_size+=WriteMeshVersion(2L);
	MDATA_size+=WriteMatEntries(matlib, nmatlib);
}

long export3ds::WriteMData_Fim()
{
	WritePatch(MDATA_bpatch, MDATA_size);

	return MDATA_size;
}

long export3ds::WriteMeshVersion(long version)
{
	WriteChunk(MESH_VERSION, SizeofChunk+sizeof(long));
	WriteLong(version);
	
	return SizeofChunk+sizeof(long);
}

long export3ds::WriteChunkString(unsigned short id, char *buffer)
{
	long size;

	size=SizeofChunk+strlen(buffer)+1;
	WriteChunk(id, size);
	WriteString(buffer);

	return size;
}

void export3ds::WriteString(char *buffer)
{
	unsigned int j;

	for(j=0;j<strlen(buffer);j++)
		WriteByte(buffer[j]);

	WriteByte('\0');
}

long export3ds::WriteChunkMapping(unsigned short id, struct mapping *m)
{
	if(m->filename[0]==0)
		return 0;

	long size=0, bpatch;

	bpatch=WriteChunk(id , 0);
	size=SizeofChunk;

	WriteChunk(INT_PERCENTAGE, SizeofChunk+sizeof(short));
	WriteShort(m->amount);
	size+=SizeofChunk+sizeof(short);

	size+=WriteChunkString(MAPP_FILENAME, m->filename);

	WriteChunk(MAPP_OPTIONS, SizeofChunk+sizeof(short));
	WriteShort(m->options);
	size+=SizeofChunk+sizeof(short);

	WriteChunk(MAPP_FILTERING, SizeofChunk+sizeof(float));
	WriteFloat(m->filtering);
	size+=SizeofChunk+sizeof(float);

	WriteChunk(MAPP_U_SCALE, SizeofChunk+sizeof(float));
	WriteFloat(m->u_scale);
	size+=SizeofChunk+sizeof(float);

	WriteChunk(MAPP_V_SCALE, SizeofChunk+sizeof(float));
	WriteFloat(m->v_scale);
	size+=SizeofChunk+sizeof(float);

	WriteChunk(MAPP_U_OFFSET, SizeofChunk+sizeof(float));
	WriteFloat(m->u_offset);
	size+=SizeofChunk+sizeof(float);

	WriteChunk(MAPP_V_OFFSET, SizeofChunk+sizeof(float));
	WriteFloat(-m->v_offset);
	size+=SizeofChunk+sizeof(float);

	WriteChunk(MAPP_ROTATION, SizeofChunk+sizeof(float));
	WriteFloat(-m->rotation);
	size+=SizeofChunk+sizeof(float);

	WritePatch(bpatch, size);

	return size;
}

long export3ds::WriteMatEntries(material *matlib, int nmatlib)
{
	const long SizeofColor=SizeofChunk+3;

	long size=0, itemSize, bpatch;

	for(int i=0;i<nmatlib;i++)
	{
		itemSize=0;
		
		bpatch=WriteChunk(MAT_ENTRY, 0);
		itemSize+=SizeofChunk;

		itemSize+=WriteChunkString(MAT_NAME, matlib[i].name);

		WriteChunk(MAT_AMBIENT, SizeofChunk+SizeofColor);
		WriteColor(matlib[i].ambient);
		itemSize+=SizeofChunk+SizeofColor;

		WriteChunk(MAT_DIFFUSE, SizeofChunk+SizeofColor);
		WriteColor(matlib[i].diffuse);
		itemSize+=SizeofChunk+SizeofColor;

		WriteChunk(MAT_SPECULAR, SizeofChunk+SizeofColor);
		WriteColor(matlib[i].specular);
		itemSize+=SizeofChunk+SizeofColor;

		WriteChunk(MAT_SHININESS, SizeofChunk*2+sizeof(short));
		WriteChunk(INT_PERCENTAGE, SizeofChunk+sizeof(short));
		WriteShort((short)(matlib[i].shininess*100.0));
		itemSize+=SizeofChunk*2+sizeof(short);

		WriteChunk(MAT_SHININESS_STRENGTH, SizeofChunk*2+sizeof(short));
		WriteChunk(INT_PERCENTAGE, SizeofChunk+sizeof(short));
		WriteShort((short)(matlib[i].shininess_strength*100.0));
		itemSize+=SizeofChunk*2+sizeof(short);

		WriteChunk(MAT_TRANSPARENCY, SizeofChunk*2+sizeof(short));
		WriteChunk(INT_PERCENTAGE, SizeofChunk+sizeof(short));
		WriteShort((short)(matlib[i].transparency*100.0));
		itemSize+=SizeofChunk*2+sizeof(short);

		WriteChunk(MAT_TRANSPARENCY_FALLOFF, SizeofChunk*2+sizeof(short));
		WriteChunk(INT_PERCENTAGE, SizeofChunk+sizeof(short));
		WriteShort((short)(matlib[i].transparency_falloff*100.0));
		itemSize+=SizeofChunk*2+sizeof(short);

		WriteChunk(MAT_REFLECT_BLUR, SizeofChunk*2+sizeof(short));
		WriteChunk(INT_PERCENTAGE, SizeofChunk+sizeof(short));
		WriteShort((short)(matlib[i].reflect_blur*100.0));
		itemSize+=SizeofChunk*2+sizeof(short);

		WriteChunk(MAT_SELF_ILLUM, SizeofChunk*2+sizeof(short));
		WriteChunk(INT_PERCENTAGE, SizeofChunk+sizeof(short));
		WriteShort((short)(matlib[i].self_illum*100.0));
		itemSize+=SizeofChunk*2+sizeof(short);

		WriteChunk(MAT_SHADING, SizeofChunk+sizeof(short));
		WriteShort(matlib[i].material_type);
		itemSize+=SizeofChunk+sizeof(short);

		itemSize+=WriteChunkMapping(MAT_MAP_TEXTURE1, &matlib[i].map_texture1);
		itemSize+=WriteChunkMapping(MAT_MAP_SPECULAR, &matlib[i].map_specular);
		itemSize+=WriteChunkMapping(MAT_MAP_OPACITY, &matlib[i].map_opacity);
		itemSize+=WriteChunkMapping(MAT_MAP_REFLECTION, &matlib[i].map_reflection);
		itemSize+=WriteChunkMapping(MAT_MAP_BUMP, &matlib[i].map_bump);
		itemSize+=WriteChunkMapping(MAT_MAP_TEXTURE2, &matlib[i].map_texture2);
		itemSize+=WriteChunkMapping(MAT_MAP_SHININESS, &matlib[i].map_shininess);
		itemSize+=WriteChunkMapping(MAT_MAP_SELFILLUM, &matlib[i].map_selfillum);

		WritePatch(bpatch, itemSize);

		size+=itemSize;
	}

	return size;
}

long export3ds::WriteColor(float c[3])
{
	WriteChunk(COLOR_24, SizeofChunk+sizeof(unsigned char)*3);
	WriteUByte((unsigned char) (c[0]*255.0+0.5));
	WriteUByte((unsigned char) (c[1]*255.0+0.5));
	WriteUByte((unsigned char) (c[2]*255.0+0.5));
	
	return SizeofChunk+sizeof(unsigned char)*3;
}

void export3ds::WriteNamedObject(
	char *name, float *vert, float *textcoord,
	unsigned short nv, unsigned short *faces, 
	unsigned short nf, unsigned short *mat, 
	int lmat, material *matlib,float *local_axis)
{
	long bpatch, itemSize;
	char nameI[64];

	if(m_fp==NULL)
		return;

	strcpy(nameI, name);

	bpatch=WriteChunk(NAMED_OBJECT, 0);
	WriteString(nameI);
	itemSize=SizeofChunk+strlen(nameI)+1;

	itemSize+=WriteTriObject(vert, textcoord, nv, faces, nf, mat, lmat, matlib, local_axis);

	WritePatch(bpatch, itemSize);

	MDATA_size+=itemSize;
}

long export3ds::WriteTextCoord(float *textcoord, unsigned short nv)
{
	long size=0;

	if(textcoord)
	{
		size=SizeofChunk+sizeof(unsigned short)+
			(nv*sizeof(float)*2);

		WriteChunk(TEXT_COORD, size);
		WriteUShort(nv);
		for(unsigned short i=0;i<nv;i++)
		{
			WriteFloat(textcoord[2*i]);
			WriteFloat(-textcoord[2*i+1]);
		}
	}

	return size;
}

long export3ds::WriteTriObject(float *vert, float *textcoord, unsigned short nv, unsigned short *faces, unsigned short nf, unsigned short *mat, int lmat, material *matlib,float *local_axis)
{
	long size=0;
	long tripatch;

	tripatch=WriteChunk(N_TRI_OBJECT, 0);
	size+=SizeofChunk;

	size+=WritePointArray(vert, nv);
	size+=WriteTextCoord(textcoord, nv);
	size+=WriteFaceArray(faces, nf, mat, lmat, matlib);

	long itemSize=SizeofChunk+sizeof(float)*12;
	WriteChunk(LOCAL_AXIS, itemSize);
	for(int i=0;i<12;i++)
		if (local_axis)
			WriteFloat(local_axis[i]);
		else if (i==0 || i==4 || i==8)
				WriteFloat(1.0f);
			else WriteFloat(0.0f);
	size+=itemSize;
	
	WritePatch(tripatch, size);

	return size;
}

long export3ds::WritePointArray(float *vert, unsigned short nv)
{
	long size=SizeofChunk+sizeof(unsigned short)+
		sizeof(float)*3*nv;

	WriteChunk(POINT_ARRAY, size);
	WriteUShort(nv);
	for(unsigned short i=0; i<nv;i++)
	{
		WriteFloat(vert[3*i]);
		WriteFloat(vert[3*i+1]);
		WriteFloat(vert[3*i+2]);
	}
	
	return size;
}

long export3ds::WriteMaterial(unsigned short *mat, int lmat, material *matlib)
{
	long size=0, itemSize;
	int i=0, j;

	while(i<lmat)
	{
		itemSize=SizeofChunk+
			strlen(matlib[mat[i]].name)+1+
			sizeof(unsigned short)+
			(sizeof(short)*mat[i+1]);

		size+=itemSize;

		WriteChunk(MSH_MAT_GROUP, itemSize);
		WriteString(matlib[mat[i]].name);

		WriteUShort((unsigned short)mat[i+1]);

		for(j=0;j<mat[i+1];j++)
			WriteUShort(mat[i+1+j+1]);

		i+=2+mat[i+1];
	}

	return size;
}

long export3ds::WriteFaceArray(unsigned short *faces, unsigned short nf, unsigned short *mat, int lmat, material *matlib)
{
	long size=0, bpatch;
	unsigned short i;

	bpatch=WriteChunk(FACE_ARRAY, 0);
	WriteUShort((unsigned short)nf);
	
	size=SizeofChunk+sizeof(unsigned short)+
		(4*sizeof(unsigned short)*nf);

	for(i=0;i<nf;i++)
		{
		WriteUShort(faces[i*3]);
		WriteUShort(faces[i*3+1]);
		WriteUShort(faces[i*3+2]);
		WriteUShort((unsigned short)7);
		}

	long itemSize=SizeofChunk+sizeof(unsigned long)*nf;
	WriteChunk(SMOOTH_GROUP, itemSize);
	for(i=0;i<nf;i++)
		WriteULong(1);
	size+=itemSize;

	size+=WriteMaterial(mat, lmat, matlib);

	WritePatch(bpatch, size);
	
	return size;
}

void export3ds::WriteUShort(unsigned short d)
{
	fwrite(&d, sizeof(unsigned short), 1, m_fp);
}

void export3ds::WriteULong(unsigned long d)
{
	fwrite(&d, sizeof(unsigned long), 1, m_fp);
}

void export3ds::WriteLong(long d)
{
	fwrite(&d, sizeof(long), 1, m_fp);
}

void export3ds::WriteByte(char d)
{
	fwrite(&d, sizeof(char), 1, m_fp);
}
void export3ds::WriteFloat(float d)
{
	fwrite(&d, sizeof(float), 1, m_fp);
}
void export3ds::WriteShort(short d)
{
	fwrite(&d, sizeof(short), 1, m_fp);
}
void export3ds::WriteUByte(unsigned char d)
{
	fwrite(&d, sizeof(unsigned char), 1, m_fp);
}
