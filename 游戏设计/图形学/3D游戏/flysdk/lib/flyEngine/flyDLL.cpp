#include "../Fly3D.h"

flydllgroup::flydllgroup()
{ 
	dll=0; 
	ndll=0;
	cd=0;
	ncd=0;
};

flydllgroup::~flydllgroup() 
{
	reset();
}

void flydllgroup::reset()
{
	if (cd)
		delete cd;
	cd=0; ncd=0;

	if (dll) 
	{
		int i;
		for( i=0;i<ndll;i++ ) 
		{
			FreeLibrary(dll[i]->hdll);
			delete dll[i];
		}
		delete dll;
		dll=0;
		ndll=0;
	}
}

void flydllgroup::load_default_param(bsp_object *o,char *sec,fly_pak *file)
{
	o->pos.null();
	o->rot.null();
	o->vel.null();
	o->force.null();
	o->bump=0.0f;
	o->friction=0.0f;
	o->mass=1.0f;
	o->radius=1.0f;
	o->life=1;
	o->col_flag=0;
	o->active=0;
	o->align_z(vector(0,0,1));

	o->load_default_params(file,sec);

	o->rotate(o->rot);

	o->next_obj=flyengine->stock_obj0;
	flyengine->stock_obj0=o;

	int i;
	for( i=0;i<o->active;i++ )
		flyengine->activate(o->clone());
}

void flydllgroup::load_all_classes(fly_pak *file)
{
	for( int d=0;d<ndll;d++ )
		load_classes(d,file);
}

void flydllgroup::load_classes(int d,fly_pak *file)
{
	if (d>=0 && d<ndll)
	if (dll[d]->num_classes!=0 && dll[d]->get_class_desc!=0) 
	{
	int i,j;
	dll[d]->nclasses=dll[d]->num_classes();
	class_desc **tmp=new class_desc *[ncd+dll[d]->nclasses];
	if (cd) 
		{
		memcpy(tmp,cd,sizeof(class_desc *)*ncd);
		delete cd;
		}
	cd=tmp;
	for( i=0;i<dll[d]->nclasses;i++ )
		cd[i+ncd]=dll[d]->get_class_desc(i);

	if (file)
	{
	bsp_object *o;
	char str[256],ret[256];
	for( i=0;i<dll[d]->nclasses;i++ )
		{
		j=0;
		while(1)
			{
			sprintf(str,"%s%i",cd[i+ncd]->get_name(),j++);
//			GetPrivateProfileString(str,"longname","",ret,255,file);
			file->get_profile_string(str,"longname",ret);
			if (ret[0]==0) break;
			o=(bsp_object *)cd[i+ncd]->create();
			strcpy(o->name,str);
			strcpy(o->long_name,ret);
			load_default_param(o,str,file);
			}
		}
	}
	
	ncd+=dll[d]->nclasses;
	}	
}

int flydllgroup::send_message(int msg,int param,void *data)
{
	int i;
	for( i=0;i<ndll;i++ )
		if (dll[i]->fly_message(msg,param,data)==0)
			return 0;
	return 1;
}

int flydllgroup::add_dll(char *filename)
{
	char file[256];
	sprintf(file,"%splugin\\%s",flyengine->flysdkpath,filename);
	HINSTANCE d=LoadLibrary(file);
	if (d)
	{
		if (GetProcAddress(d,"num_classes")==0 ||
			GetProcAddress(d,"get_class_desc")==0 ||
			GetProcAddress(d,"fly_message")==0)
			return -1;

		flydll **tmp=new flydll *[ndll+1];
		memcpy(tmp,dll,sizeof(flydll *)*ndll);
		if (dll) delete dll;
		dll=tmp;
		
		dll[ndll]=new flydll;
		dll[ndll]->hdll=d;
		strcpy(dll[ndll]->dll_filename,filename);
		dll[ndll]->num_classes=(int (*)())GetProcAddress(d,"num_classes");
		dll[ndll]->get_class_desc=(class_desc *(*)(int i))GetProcAddress(d,"get_class_desc");
		dll[ndll]->fly_message=(int (*)(int msg,int param,void *data))GetProcAddress(d,"fly_message");
		dll[ndll]->nclasses=0;

		return ndll++;
	}
	return -1;
}

int flydllgroup::delete_dll(char *filename)
{
	int i,j=0,k;
	
	for( i=0;i<ndll;i++ )
		if (!strcmp(filename,dll[i]->dll_filename))
			break;
		else j+=dll[i]->nclasses;
	if (i==ndll)
		return 0;
	
	for( k=j;k<j+dll[i]->nclasses;k++ )
	{
		char *name=cd[k]->get_name();
		int len=strlen(name);

		bsp_object *o=flyengine->stock_obj0;
		while(o)
		{
			if (!strncmp(o->name,name,len))
			{
				bsp_object *tmp=o;
				o=(bsp_object *)o->next_obj;
				delete_class(tmp);
			}
			else o=(bsp_object *)o->next_obj;
		}
	}

	memcpy(&cd[j],&cd[j+dll[i]->nclasses],(ncd-(j+dll[i]->nclasses))*sizeof(class_desc *));
	ncd-=dll[i]->nclasses;
	delete dll[i];
	memcpy(&dll[i],&dll[i+1],(ndll-(i+1))*sizeof(flydll *));
	ndll--;
	return 1;
}

void flydllgroup::delete_references(bsp_object *o)
{
	param_desc pd;
	int n,k;
	bsp_object *obj;
	
	obj=flyengine->active_obj0;
	while(obj)
	{
		n=obj->get_param_desc(0,0);
		for( k=0;k<n;k++ )
			{
			obj->get_param_desc(k,&pd);
			if (pd.type>255 || pd.type<-255 || pd.type=='d' || pd.type=='o')
				if ((*((bsp_object **)pd.data))==o)
					*((bsp_object **)pd.data)=0;
			}
		
		obj=(bsp_object *)obj->next_obj;
	}

	obj=flyengine->stock_obj0;
	while(obj)
	{
		n=obj->get_param_desc(0,0);
		for( k=0;k<n;k++ )
			{
			obj->get_param_desc(k,&pd);
			if (pd.type>255 || pd.type<-255 || pd.type=='d' || pd.type=='o')
				if ((*((bsp_object **)pd.data))==o)
					*((bsp_object **)pd.data)=0;
			}
		
		obj=(bsp_object *)obj->next_obj;
	}
}

void flydllgroup::delete_class(bsp_object *o)
{
	bsp_object **op=0;

	op=&flyengine->active_obj0;
	while( *op )
	{
		bsp_object *tmp=*op;
		if (tmp->source==o)
		{
			if (flyengine->cam==tmp)
				flyengine->cam=0;
			if (flyengine->player==tmp)
				flyengine->player=0;
			*op=(bsp_object *)tmp->next_obj;
			tmp->next_obj=0;
			delete_references(tmp);
			tmp->remove_from_bsp();
			delete tmp;
		}
		else 
			op=(bsp_object **)&tmp->next_obj;
	}

	op=&flyengine->stock_obj0;
	while( *op )
	{
		bsp_object *tmp=*op;
		if (tmp==o)
		{
			if (flyengine->cam==tmp)
				flyengine->cam=0;
			if (flyengine->player==tmp)
				flyengine->player=0;
			*op=(bsp_object *)tmp->next_obj;
			delete_references(tmp);
			tmp->next_obj=0;
			delete tmp;
		}
		else 
			op=(bsp_object **)&tmp->next_obj;
	}
}

bsp_object *flydllgroup::add_class(char *name)
{
	int i;
	bsp_object *o=0;
	for( i=0;i<ncd;i++ )
		if (!stricmp(name,cd[i]->get_name()))
			break;
	if (i<ncd)
	{
		o=(bsp_object *)cd[i]->create();
		o->next_obj=flyengine->stock_obj0;
		flyengine->stock_obj0=o;
		o->pos.null();
		o->rot.null();
		o->vel.null();
		o->force.null();
		o->align_z(vector(0,0,1));
		o->force.null();
		o->col_flag=0;
		o->bump=0;
		o->friction=0;
		o->life=0;
		o->mass=0.0f;
		o->radius=0.0;
		o->active=0;
		int i,j,len;
		param_desc pd;
		i=o->get_param_desc(0,0);
		for( j=0;j<i;j++ )
		{
			o->get_param_desc(j,&pd);
			len=4;
			if (pd.type=='v' || pd.type=='c')
				len=12;
			else if (pd.type=='s')
				len=1;
			if (pd.type=='p')
				*((int *)pd.data)=-1;
			else memset(pd.data,0,len);
		}
	}
	return o;
}

void flydllgroup::move_dll(char *filename,int newrelpos)
{
	int i,j,k;
	for( i=0;i<ndll;i++ )
		if (!strcmp(filename,dll[i]->dll_filename))
			break;
	if (i<ndll)
	{
		flydll *d=dll[i];
		dll[i]=dll[i+newrelpos];
		dll[i+newrelpos]=d;

		k=0;
		for( i=0;i<ndll;i++ )
			for( j=0;j<dll[i]->nclasses;j++ )
				cd[k++]=dll[i]->get_class_desc(j);
	}
}
