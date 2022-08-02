#include "../Fly3D.h"
#include <direct.h>

bool fly_pak_util::implode(char *foldername)
{
	char *str;
	bool rslt;

	strcpy(folder, foldername);

	str=new char[strlen(foldername)+5];

	strcpy(str, foldername);
	strcat(str,".fpk");
	
	fpk=fopen(str, "wb");

	delete str;
	
	if(!fpk)
		return false;

	filelist=(struct fileinfo *)malloc(0);
	lenfilelist=0;

	totalsize=0;
	currsize=0;

	rslt=browse(foldername);

	if(rslt) rslt=add_header();
	if(rslt) rslt=add_data();

	fclose(fpk);

	free(filelist);
	
	return rslt;
}

bool fly_pak_util::browse(char *foldername)
{
	HANDLE hFindFile;
	WIN32_FIND_DATA FindFileData;
	char *str;
	bool rslt;

	str=new char[strlen(foldername)+3];

	strcpy(str, foldername);
	strcat(str, "\\*");

	hFindFile=FindFirstFile(str, &FindFileData);

	delete str;

	if(hFindFile==INVALID_HANDLE_VALUE)
		return false;

	rslt=true;

	do
	{
		if(0==strcmp(FindFileData.cFileName, ".") ||
		   0==strcmp(FindFileData.cFileName, ".."))
			continue;

		str=new char[strlen(foldername)+strlen(FindFileData.cFileName)+2];

		strcpy(str, foldername);
		strcat(str, "\\");
		strcat(str, FindFileData.cFileName);

		if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			rslt=browse(str);
		else
			add_filelist(str, (FindFileData.nFileSizeHigh * MAXDWORD) + FindFileData.nFileSizeLow);

		delete str;
	}
	while(rslt && FindNextFile(hFindFile, &FindFileData));

	FindClose(hFindFile);

	return rslt;
}

bool fly_pak_util::add(int i)
{
	FILE *f;
	char fb[MAXP];
	bool rslt;
	char bl[10240];
	unsigned long curread;

	strcpy(fb, folder);
	strcat(fb, "\\");
	strcat(fb, filelist[i].filename);

	if(!(f=fopen(fb,"rb")))
		return false;

	rslt=true;

	while(rslt && (curread=fread(bl, 1, 10240, f)) )
		if((rslt=(fwrite(bl, 1, curread, fpk)==curread)))
			currsize+=curread;

	fclose(f);

	return rslt;
}

bool fly_pak_util::explode(char *filename)
{
	unsigned int i;
	char str[MAXP], *p;

	if(!(fpk=fopen(filename,"rb")))
		return false;

	while(p=strrchr(filename, '/')) *p='\\';

	if(p=strstr(filename, ".fpk"))
		*p=0;
	else
	{
		fclose(fpk);
		return false;
	}

	fread(&lenfilelist, sizeof(unsigned int), 1, fpk);

	if(lenfilelist==0)
	{
		fclose(fpk);
		return true;
	}

	filelist=new fileinfo[lenfilelist];

	fread(filelist, sizeof(struct fileinfo), lenfilelist, fpk);

	currsize=0;
	totalsize=0;

	for(i=0; i<lenfilelist; i++)
		totalsize+=filelist[i].size;

	fseek(fpk, sizeof(unsigned int)+lenfilelist*sizeof(struct fileinfo), SEEK_SET);

	for(i=0; i<lenfilelist; i++)
	{
		create_dir(filename, filelist[i].filename);
		strcpy(str, filename);
		strcat(str, "\\");
		strcat(str, filelist[i].filename);
		if(!extract(str, filelist[i].size))
			break;

		update_status(filelist[i].filename, filelist[i].size);
	}

	fclose(fpk);
	
	return i==lenfilelist;
}

bool fly_pak_util::extract(char *filename, unsigned long size)
{
	FILE *fp;
	char bl[10240];
	unsigned long curread, curfile=0;
	unsigned long curb;
	
	if(!(fp=fopen(filename, "wb")))
		return false;

	while(curfile<size)
	{
		if(10240+curfile>size)
			curb=size-curfile;
		else
			curb=10240;

		if((curread=fread(bl, 1, curb, fpk)) && (fwrite(bl, 1, curread, fp)==curread))
		{
			curfile+=curread;
			currsize+=curread;
//			if(totalsize==0)
//				update_status(100);
//			else
//				update_status((int)((100.0*currsize)/totalsize));
		}
		else
			break;
	}

	fclose(fp);

	return curfile==size;
}

void fly_pak_util::create_dir(char *basefolder, char *filename)
{
	char *p=filename;
	char str[MAXP];

	_mkdir(basefolder);
	while(p=strchr(p+1, '\\'))
	{
		*p='\0';
		strcpy(str, basefolder);
		strcat(str, "\\");
		strcat(str, filename);
		_mkdir(str);
		*p='\\';
	}
}

void fly_pak_util::add_filelist(char *filename, unsigned long size)
{
	filelist=(struct fileinfo *)realloc(filelist, (++lenfilelist)*sizeof(struct fileinfo));

	strcpy(filelist[lenfilelist-1].filename, &filename[strlen(folder)+1]);
	filelist[lenfilelist-1].size=size;

	totalsize+=size;
}

bool fly_pak_util::add_header()
{
	if(fwrite(&lenfilelist, sizeof(unsigned int), 1, fpk)!=1)
		return false;

	if(fwrite(filelist, sizeof(struct fileinfo), lenfilelist, fpk)!=lenfilelist)
		return false;

	return true;
}

bool fly_pak_util::add_data()
{
	unsigned int i;

	for(i=0; i<lenfilelist; i++)
	{
		if(!add(i))
			break;
		
		update_status(filelist[i].filename, filelist[i].size);
	}

	return i==lenfilelist;
}

void fly_pak_util::update_status(char *filename, unsigned long size)
{
}
