#include "walk.h"

void jump_pad::init()
{
	if (objmesh)
		pos=objmesh->pivotpos;
}

int jump_pad::get_custom_param_desc(int i,param_desc *pd)
{
	if (pd==0)
		return 4;
	else 
	switch(i)
	{
		case 0:
			pd->type='f';
			pd->data=&jumpforce;
			strcpy(pd->name,"jumpforce");
			break;
		case 1:
			pd->type='i';
			pd->data=&forcetime;
			strcpy(pd->name,"forcetime");
			break;
		case 2:
			pd->type='i';
			pd->data=&invert;
			strcpy(pd->name,"invert");
			break;
		case 3:
			pd->type='3';
			pd->data=&objmesh;
			strcpy(pd->name,"mesh");
			break;
	}
	return 0;
}

