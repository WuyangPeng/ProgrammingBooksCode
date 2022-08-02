#include "..\..\lib\Fly3D.h"
#include "gamelib.h"

void exp_sphere::init()
{
	// num segments
	int s=(int)(M_2Pi*radius/flyengine->geomdetail);
	if (s<2) s=2;
	if (s>32) s=32;

	int nu=2*s+1; //num vert in u dir
	int ns=s-2; // num strips 
	
	float du=M_2Pi/(nu-1); // step in u
	float dv=M_Pi/s;

	int i,j;
	float u,v;
	vertex *verts;

	if (sfmesh==0)
		sfmesh=new stripfan_mesh;
	sfmesh->reset();

	// create top fan
	verts=sfmesh->add_stripfan(-nu-1,-1,-1);

	// set fan center vertex
	verts->pos.vec(0,0,1);
	verts++;
	
	// set fan vertices
	v=M_Pi2-dv;
	u=0.0f;
	for( i=0;i<nu;i++ )
		{
		verts[i].pos.vec(
			(float)(cos(u)*cos(v)),
			(float)(sin(u)*cos(v)),
			(float)sin(v));
		u+=du;
		}

	// cerate bottom fan
	verts=sfmesh->add_stripfan(-nu-1,-1,-1);
	
	// set fan center vertex
	verts->pos.vec(0,0,-1);
	verts++;

	// set fan vertices
	u=0.0f;
	v=-M_Pi2+dv;
	for( i=0;i<nu;i++ )
		{
		verts[i].pos.vec(
			(float)(sin(u)*cos(v)),
			(float)(cos(u)*cos(v)),
			(float)sin(v));
		u+=du;
		}

	// cerate center strips
	v=M_Pi2-dv;
	for( i=0;i<ns;i++ )
		{
		verts=sfmesh->add_stripfan(nu*2,-1,-1);
		u=0.0f;
		for( j=0;j<nu;j++ )
			{
			verts[2*j].pos.vec(
				(float)(cos(u)*cos(v)),
				(float)(sin(u)*cos(v)),
				(float)sin(v));

			verts[2*j+1].pos.vec(
				(float)(cos(u)*cos(v-dv)),
				(float)(sin(u)*cos(v-dv)),
				(float)sin(v-dv));

			u+=du;
			}
		v-=dv;
		}
}

int exp_sphere::step(int dt)
{
	life-=dt;
	float x;
	if (life<0)
		x=0.0f;
	else x=(float)life/source->life;
	curradius=radius*(1.0f-x);
	return 0;
}

void exp_sphere::draw()
{
	glPushMatrix();
	glTranslatef(pos.x,pos.y,pos.z);
	glScalef(curradius,curradius,curradius);
	glColor3fv(&color.x);

	glDepthMask(GL_FALSE);
	glBlendFunc(GL_ONE, GL_ONE);
	glDisable(GL_FOG);

	sfmesh->draw(1);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	if (flyengine->fog) glEnable(GL_FOG);
	glDepthMask(GL_TRUE);

	glPopMatrix();
}

int exp_sphere::get_custom_param_desc(int i,param_desc *pd)
{
	if (pd!=0)
	switch(i)
	{
	case 0:
		pd->type='c';
		pd->data=&color;
		strcpy(pd->name,"color");
		break;
	}
	return 1;
}

int exp_sphere::message(vector& p,float rad,int msg,int param,void *data)
{
	if (msg==FLYOBJM_CHANGEPARAM)
		if (param>=0 || 
			((param_desc *)data)->data==&flyengine->geomdetail)
			init();
	return 0;
}
