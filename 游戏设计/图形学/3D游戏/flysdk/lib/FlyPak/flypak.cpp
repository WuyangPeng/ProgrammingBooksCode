#include "../Fly3D.h"
#include <direct.h>

fly_pak::fly_pak()
{
	pos=0;
	len=0;
	buf=0;
	pakfile=0;
}

fly_pak::~fly_pak()
{
	if(buf) delete buf;
	if(pakfile) fclose(pakfile);
}

bool fly_pak::open(char *filename)
{
	FILE *fp=fopen(filename, "rb");
	
	if(!fp)
	{
		char *p;
		while(p=strchr(filename, '/')) *p='\\';

		if(!pakfile || !same_pak(filename))
			if(!open_pak(filename))
				return false;

		if(!seek_file(filename))
			return false;

		buf=new char[len];
		fread(buf, 1, len, pakfile);
		pos=0;
	}
	else
	{
		fseek(fp, 0, SEEK_END);
		len=ftell(fp);
		buf=new char[len];
		fseek(fp, 0, SEEK_SET);
		fread(buf, 1, len, fp);
		pos=0;
		fclose(fp);
	}

	return true;
}

FILE *fly_pak::get_fp(char *filename)
{
	FILE *fp=fopen(filename, "rb");

	if (fp) 
		return fp;

	char *p;
	while(p=strchr(filename, '/')) *p='\\';

	if(!pakfile || !same_pak(filename))
		if(!open_pak(filename))
			return 0;

	if(!seek_file(filename))
		return 0;

	fp=pakfile;
	pakfile=0;

	return fp;
}

void fly_pak::close()
{
	if(buf)
	{
		delete buf;
		buf=0;
		pos=0;
		len=0;
	}
}

int fly_pak::read(void *dest, int size)
{
	if(pos+size>=len) size=len-pos;
	memcpy(dest, &buf[pos], size);
	pos+=size;
	return size;
}

void fly_pak::get_string(char *dest)
{
	int i=0;

	while(pos<len && buf[pos]!='\r' && buf[pos]!='\n') dest[i++]=buf[pos++];

	dest[i]='\0';
	if(pos<len && buf[pos]=='\r') pos++;
	if(pos<len && buf[pos]=='\n') pos++;
}

bool fly_pak::proc_section(char *section)
{
	char *s;
	int slen, spos, pant=pos;

	slen=strlen(section)+2;
	s=new char[slen+1];
	strcpy(s, "[");
	strcat(s, section);
	strcat(s, "]");

	pos=0;
	
	while(pos<len)
	{
		if(buf[pos]==s[0])
		{
			spos=0;
			while(pos<len && spos<slen && buf[pos]==s[spos])
			{
				pos++;
				spos++;
			}
			if(spos==slen) return true;
		}
		pos++;
	}

	pos=pant;

	return false;
}

bool fly_pak::proc_key(char *key)
{
	char *s;
	int slen, spos, pant=pos;

	slen=strlen(key)+1;
	s=new char[slen+1];
	strcpy(s, key);
	strcat(s, "=");
	
	while(pos<len && buf[pos]!='[')
	{
		if(buf[pos]==s[0])
		{
			spos=0;
			while(pos<len && spos<slen && buf[pos]==s[spos])
			{
				pos++;
				spos++;
			}
			if(spos==slen)	return true;
		}
		pos++;
	}
	
	pos=pant;

	return false;
}

void fly_pak::get_profile_string(char *section, char *key, char *dest)
{
	dest[0]='\0';
	if(!proc_section(section)) return;
	if(!proc_key(key)) return;
	get_string(dest);
}

float fly_pak::get_float()
{
	char s[64];
	int i=0;

	while(pos<len && !((buf[pos]>=48 && buf[pos]<=57) || buf[pos]=='.' || buf[pos]=='-'))
		pos++;

	if(pos==len) return 0;

	do s[i++]=buf[pos++];
	while(pos<len && ((buf[pos]>=48 && buf[pos]<=57) || buf[pos]=='.'));
		

	s[i]='\0';

	return (float)atof(s);
}

int fly_pak::get_int()
{
	char s[64];
	int i=0;

	while(pos<len && !((buf[pos]>=48 && buf[pos]<=57) || buf[pos]=='-'))
		pos++;

	if(pos==len) return 0;

	do s[i++]=buf[pos++];
	while(pos<len && buf[pos]>=48 && buf[pos]<=57);
		

	s[i]='\0';

	return atoi(s);
}

bool fly_pak::open_pak(char *filename)
{
	char *p;
	char str[MAXP];

	if(pakfile)
	{
		fclose(pakfile);
		pakfile=NULL;
	}

	strcpy(str, filename);

	while(!pakfile && (p=strrchr(str, '\\')))
	{
		*p=0;
		strcpy(fldrname, str);
		strcat(str,".fpk");
		pakfile=fopen(str,"rb");
	}

	return pakfile!=NULL;
}

bool fly_pak::seek_file(char *filename)
{
	char fp[MAXP];
	unsigned long t;
	unsigned int nfiles;
	struct fileinfo fl;

	strcpy(fp, &filename[strlen(fldrname)+1]);

	fseek(pakfile, 0, SEEK_SET);
	fread(&nfiles, sizeof(unsigned int), 1, pakfile);

	t=sizeof(unsigned int)+nfiles*sizeof(struct fileinfo);

	for(nfiles; nfiles>0; nfiles--)
	{
		fread(&fl, sizeof(struct fileinfo), 1, pakfile);
		if(_stricmp(fl.filename, fp)==0)
		{
			len=fl.size;
			break;
		}
		else
			t+=fl.size;
	}

	fseek(pakfile, t, SEEK_SET);

	return nfiles>0;
}

bool fly_pak::same_pak(char *filename)
{
	unsigned int t=strlen(fldrname);
	char str[MAXP];

	if(t>strlen(filename))
		return false;

	strncpy(str, filename, t);
	str[t]=0;

	return _stricmp(filename, str)==0;
}

void fly_pak::seek(long offset)
{
	long newpos=pos+offset;

	if(newpos>=0 && newpos<(signed)len) pos=newpos;
}

