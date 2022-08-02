#include "..\..\lib\Fly3D.h"
#include "gamelib.h"

void cartoon_mesh::init()
{
	if (objmesh)
	{
		pos=objmesh->pivotpos;
		if (objmesh->edges==0)
			objmesh->compute_normals(MESH_EDGES);
	}
}

void cartoon_mesh::draw()
{
	if (objmesh)
	{
	// position the object
	glPushMatrix();
	glTranslatef(pos.x,pos.y,pos.z);
	glMultMatrixf((float *)&mat);

	// compute ambient light
	vector ambient;
	if (node)
		ambient=node->color;
	else ambient.null();

	vector v=flyengine->cam->pos-pos;
	float f=v.length()/flyengine->viewmaxdist;
	if (f<1.0f)
		f=(1.0f-f)*flyengine->cartoonwidth;
	else f=0.0f;
	
	// make light positions local to object
	for( int i=0;i<lights.nlights;i++ )
		lights.pos[i]-=pos;
	// draw object as cartoon
	objmesh->draw_cartoon(v,ambient,lights,f);
	//clear lights
	lights.nlights=0;

	glPopMatrix();
	}
}

bsp_object *cartoon_mesh::clone()
{
	cartoon_mesh *tmp=new cartoon_mesh;
	*tmp=*this;
	tmp->source=this;
	return tmp;
}

int cartoon_mesh::get_custom_param_desc(int i,param_desc *pd)
{
	if (pd!=0)
	switch(i)
	{
	case 0:
		pd->type='3';
		pd->data=&objmesh;
		strcpy(pd->name,"objmesh");
		break;
	}
	return 1;
}

int cartoon_mesh::message(vector& p,float rad,int msg,int param,void *data)
{
	if (msg==FLYOBJM_CHANGEPARAM && param>=0)
		init();
	else
	if (msg==FLYOBJM_ILLUM || msg==FLYOBJM_DYNILLUM)
		lights.add_light(p,*((vector *)data),rad);

	return 0;
}
