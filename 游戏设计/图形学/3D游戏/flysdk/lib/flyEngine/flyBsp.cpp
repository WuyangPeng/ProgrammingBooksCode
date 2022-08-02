#include "../Fly3D.h"

bsp_node::~bsp_node()
{
	if (elem) delete elem;
	if (child[0]) delete child[0];
	if (child[1]) delete child[1];
}

mesh *bsp_object::ray_intersect(vector& ro,vector& rd,vector& ip,float& dist,int &facenum,float rad)
{ 
	mesh *objmesh=get_mesh();

	if (objmesh) 
	{
		static float d1,d2;
		vector ro_local=(ro-pos)*mat_t,
			rd_local=rd*mat_t;
		if (objmesh->bbox.ray_intersect(ro_local,rd_local,d1,d2))
		{
		facenum=objmesh->ray_intersect(ro_local,rd_local,ip,dist,rad);
		if (facenum>-1)
			{
			ip=ip*mat+pos;
			return objmesh;
			}
		}
	}
	return 0;
}

int bsp_object::ray_intersect_test(vector& ro,vector& rd,float rad)
{ 
	mesh *objmesh=get_mesh();

	if (objmesh) 
	{
		static float d1,d2;
		vector ro_local=(ro-pos)*mat_t,
			rd_local=rd*mat_t;
		if (objmesh->bbox.ray_intersect(ro_local,rd_local,d1,d2))
		if (objmesh->ray_intersect_test(ro_local,rd_local,rad))
			return 1;
	}
	return 0;
}

void bsp_object::remove_from_bsp()
{
	if (node==0) return;
	bsp_object *e=node->elem,*ep=0;
	while(e)
	{
		if (e==this)
			{
			if (next_elem==0)
				if (ep)
					node->last_elem=&ep->next_elem;
				else node->last_elem=&node->elem;
			if (ep)
				ep->next_elem=next_elem;
			else
				node->elem=next_elem;
			next_elem=0;
			node=0;
			return;
			}
		ep=e;
		e=e->next_elem;
	}
	node=0;
}

void bsp_object::add_to_bsp()
{
	float d;
	if (node) remove_from_bsp();
	node=flyengine->bsp;
	while( node && node->leaf==-1)
	{
		d=node->distance(pos);
		if (d>-SMALL)
			node=node->child[0];
		else node=node->child[1];
	}

	if (node)
	{
		next_elem=0;
		*node->last_elem=this;
		node->last_elem=&next_elem;
	}
}

void bsp_object::load_params(fly_pak *file,char *sec)
{
	int i,n=get_param_desc(0,0);
	param_desc pd;
	char ret[256];

	for( i=0;i<n;i++ )
	{
		get_param_desc(i,&pd);
		ret[0]=0;
		file->get_profile_string(sec,pd.name,ret);
		pd.set_string(ret);
	}
}

void bsp_object::load_default_params(fly_pak *file,char *sec)
{
	int i,n=NUM_DEFAULT_PARAM;
	param_desc pd;
	char ret[256];

	for( i=0;i<n;i++ )
	{
		get_param_desc(i,&pd);
		ret[0]=0;
		file->get_profile_string(sec,pd.name,ret);
		pd.set_string(ret);
	}
}

int bsp_object::get_param_desc(int i,param_desc *pd)
{
	if (pd==0)
		return NUM_DEFAULT_PARAM+get_custom_param_desc(0,0);
	else
	if (i>=NUM_DEFAULT_PARAM)
		get_custom_param_desc(i-NUM_DEFAULT_PARAM,pd);
	else
	switch(i)
	{
		case 0:
			pd->type='v';
			pd->data=&pos;
			strcpy(pd->name,"pos");
			break;
		case 1:
			pd->type='v';
			pd->data=&rot;
			strcpy(pd->name,"rot");
			break;
		case 2:
			pd->type='v';
			pd->data=&vel;
			strcpy(pd->name,"vel");
			break;
		case 3:
			pd->type='v';
			pd->data=&force;
			strcpy(pd->name,"force");
			break;
		case 4:
			pd->type='i';
			pd->data=&life;
			strcpy(pd->name,"life");
			break;
		case 5:
			pd->type='i';
			pd->data=&col_flag;
			strcpy(pd->name,"colflag");
			break;
		case 6:
			pd->type='f';
			pd->data=&mass;
			strcpy(pd->name,"mass");
			break;
		case 7:
			pd->type='f';
			pd->data=&radius;
			strcpy(pd->name,"radius");
			break;
		case 8:
			pd->type='f';
			pd->data=&bump;
			strcpy(pd->name,"bump");
			break;
		case 9:
			pd->type='f';
			pd->data=&friction;
			strcpy(pd->name,"friction");
			break;
		case 10:
			pd->type='i';
			pd->data=&active;
			strcpy(pd->name,"active");
			break;
		case 11:
			pd->type='i';
			pd->data=&latedraw;
			strcpy(pd->name,"latedraw");
			break;
	}
	return 0;
}

char *param_desc::get_string()
{
	static char str[256];
	str[0]=0;
	if (type>255 || type<-255)
		{
		if (*((bsp_object **)data)!=0)
				strcpy(str,(*((bsp_object **)data))->name);
		}
	else
	switch(type)
		{
		case 'b':
			strcpy(str,flyengine->bspfile);
			break;
		case 'i':
			sprintf(str,"%i",*((int *)data));
			break;
		case 'f':
			sprintf(str,"%f",*((float *)data));
			break;
		case 'a':
			sprintf(str,"%f",acos(*((float *)data))*PiUnder180);
			break;
		case 'c':
		case 'v':
			sprintf(str,"%f %f %f",
				((float *)data)[0],
				((float *)data)[1],
				((float *)data)[2]);
			break;
		case 'p':
			if (*((int *)data)!=-1)
				strcpy(str,flyengine->piclib[*((int *)data)]->name);
			break;
		case 'o':
			if (*((bsp_object **)data)!=0)
				strcpy(str,(*((bsp_object **)data))->name);
			break;
		case 'd':
			if (*((bsp_object **)data)!=0)
				strcpy(str,(*((bsp_object **)data))->name);
			break;
		case '3':
			if (*((mesh **)data)!=0)
				strcpy(str,(*((mesh **)data))->name);
			break;
		case 'm':
			if (*((mesh **)data)!=0)
				strcpy(str,(*((mesh **)data))->name);
			break;
		case 'z':
			if (*((bezier_curve **)data)!=0)
				strcpy(str,(*((bezier_curve **)data))->name);
			break;
		case 'h':
			if (*((bezier_patch **)data)!=0)
				strcpy(str,(*((bezier_patch **)data))->name);
			break;
		case 'w':
			if (*((sound **)data)!=0)
				strcpy(str,(*((sound **)data))->name);
			break;
		case 's':
			strcpy(str,(char *)data);
			break;
		}
	return str;
}

void param_desc::set_string(char *str)
{
	if (type>255)
		(*((bsp_object **)data))=flyengine->get_stock_object(str);
	else
	if (type<-255)
		(*((bsp_object **)data))=flyengine->get_active_object(str);
	else
	switch(type)
	{
		case 'i':
			*((int *)data)=0;
			sscanf(str,"%i",(int *)data);
			break;
		case 'f':
			*((float *)data)=0;
			sscanf(str,"%f",(float *)data);
			break;
		case 'a':
			*((float *)data)=0;
			sscanf(str,"%f",(float *)data);
			*((float *)data)=(float)cos(*((float *)data)*PiOver180);
			break;
		case 'c':
		case 'v':
			((float *)data)[0]=
			((float *)data)[1]=
			((float *)data)[2]=0;
			sscanf(str,"%f %f %f",
				&((float *)data)[0],
				&((float *)data)[1],
				&((float *)data)[2]);
			break;
		case 'p':
			*((int *)data)=flyengine->get_picture(str);
			break;
		case 'o':
			*((bsp_object **)data)=flyengine->get_stock_object(str);
			break;
		case 'd':
			*((bsp_object **)data)=flyengine->get_active_object(str);
			break;
		case '3':
			*((mesh **)data)=flyengine->get_model_object(str);
			break;
		case 'm':
			*((mesh **)data)=flyengine->get_model_object(str);
			break;
		case 'z':
			*((bezier_curve **)data)=flyengine->get_bezier_curve(str);
			break;
		case 'h':
			*((bezier_patch **)data)=flyengine->get_bezier_patch(str);
			break;
		case 'w':
			*((sound **)data)=flyengine->get_sound_object(str);
			break;
		case 'b':
		case 's':
			strcpy((char *)data,str);
			break;
	}
}
