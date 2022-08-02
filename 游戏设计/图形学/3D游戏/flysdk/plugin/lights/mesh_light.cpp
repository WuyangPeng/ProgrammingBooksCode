#include "../../lib/Fly3D.h"
#include "lights.h"

int mesh_light::get_custom_param_desc(int i,param_desc *pd)
{
	if (pd!=0)
	switch(i)
	{
		case 0:
			pd->type='f';
			pd->data=&illum_radius;
			strcpy(pd->name,"illumradius");
			break;
		case 1:
			pd->type='c';
			pd->data=&color;
			strcpy(pd->name,"color");
			break;
		case 2:
			pd->type='p';
			pd->data=&halopic;
			strcpy(pd->name,"halopic");
			break;
		case 3:
			pd->type='f';
			pd->data=&halosize;
			strcpy(pd->name,"halosize");
			break;
		case 4:
			pd->type='3';
			pd->data=&objmesh;
			strcpy(pd->name,"mesh");
			break;
	}
	return 5;
}

void mesh_light::init()
{
	if (objmesh)
		pos=objmesh->pivotpos;
}

int mesh_light::step(int dt)
{
	if (directx->mpmode!=FLYMP_SERVER)
	{
		if (halopic!=-1)
			{
			flyengine->excludecollision=flyengine->cam;
			if (flyengine->collision_test(flyengine->bsp,pos,flyengine->cam->pos))
				{
				color.w-=dt/200.0f;
				if (color.w<0.0f)
					color.w=0.0f;
				}
			else 
				{
				color.w+=dt/200.0f;
				if (color.w>1.0f)
					color.w=1.0f;
				}
			flyengine->excludecollision=0;
			}
		flyengine->send_bsp_message(flyengine->bsp,pos,illum_radius,FLYOBJM_DYNILLUM,0,&color);
	}
	return 0;
}

void mesh_light::draw()
{
	lastdraw=flyengine->cur_frame;
	if (objmesh)
	{
	glPushMatrix();
	glTranslatef(pos.x,pos.y,pos.z);
	objmesh->draw();
	glPopMatrix();
	}

	if (halopic==-1 || FP_BITS(color.w)==0) 
		return;

	static vector x,y;
	x=flyengine->cam->X*halosize;
	y=flyengine->cam->Y*halosize;

	glBlendFunc(GL_ONE,GL_ONE);
	glDepthMask(GL_FALSE);
	glDisable(GL_FOG);
	glDisable(GL_DEPTH_TEST);
	
	glColor3f(color.x*color.w,color.y*color.w,color.z*color.w);

	tc->use(halopic);

	glBegin(GL_QUADS);

	glTexCoord2f(1,0);
	glVertex3f(pos.x+x.x-y.x, pos.y+x.y-y.y, pos.z+x.z-y.z);

	glTexCoord2f(1,1);
	glVertex3f(pos.x+x.x+y.x, pos.y+x.y+y.y, pos.z+x.z+y.z);

	glTexCoord2f(0,1);
	glVertex3f(pos.x+y.x-x.x, pos.y+y.y-x.y, pos.z+y.z-x.z);

	glTexCoord2f(0,0);
	glVertex3f(pos.x-x.x-y.x, pos.y-x.y-y.y, pos.z-x.z-y.z);

	glEnd();

	glDepthMask(GL_TRUE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	if (flyengine->fog) glEnable(GL_FOG);
	glEnable(GL_DEPTH_TEST);
}

int mesh_light::message(vector& p,float rad,int msg,int param,void *data)
{
	if (msg==FLYOBJM_STATICILLUM)
		if (radius==0.0f || objmesh==0)
			flyengine->send_bsp_message(flyengine->bsp,pos,illum_radius,FLYOBJM_ILLUM,flyengine->shadows,&color);
		else
		{
		vector c=color*0.125f;
		vector m1(radius,radius,radius);
		vector m2(-radius,-radius,-radius);
		
		pos=objmesh->pivotpos+m1;
		flyengine->send_bsp_message(flyengine->bsp,pos,illum_radius,FLYOBJM_ILLUM,flyengine->shadows,&c);

		flyengine->cur_step++;
		pos=objmesh->pivotpos+m1;
		pos.x=objmesh->pivotpos.x+m2.x;
		flyengine->send_bsp_message(flyengine->bsp,pos,illum_radius,FLYOBJM_ILLUM,flyengine->shadows,&c);

		flyengine->cur_step++;
		pos=objmesh->pivotpos+m1;
		pos.y=objmesh->pivotpos.y+m2.y;
		flyengine->send_bsp_message(flyengine->bsp,pos,illum_radius,FLYOBJM_ILLUM,flyengine->shadows,&c);

		flyengine->cur_step++;
		pos=objmesh->pivotpos+m1;
		pos.z=objmesh->pivotpos.z+m2.z;
		flyengine->send_bsp_message(flyengine->bsp,pos,illum_radius,FLYOBJM_ILLUM,flyengine->shadows,&c);

		flyengine->cur_step++;
		pos=objmesh->pivotpos+m2;
		flyengine->send_bsp_message(flyengine->bsp,pos,illum_radius,FLYOBJM_ILLUM,flyengine->shadows,&c);
		
		flyengine->cur_step++;
		pos=objmesh->pivotpos+m2;
		pos.x=objmesh->pivotpos.x+m1.x;
		flyengine->send_bsp_message(flyengine->bsp,pos,illum_radius,FLYOBJM_ILLUM,flyengine->shadows,&c);

		flyengine->cur_step++;
		pos=objmesh->pivotpos+m2;
		pos.y=objmesh->pivotpos.y+m1.y;
		flyengine->send_bsp_message(flyengine->bsp,pos,illum_radius,FLYOBJM_ILLUM,flyengine->shadows,&c);

		flyengine->cur_step++;
		pos=objmesh->pivotpos+m2;
		pos.z=objmesh->pivotpos.z+m1.z;
		flyengine->send_bsp_message(flyengine->bsp,pos,illum_radius,FLYOBJM_ILLUM,flyengine->shadows,&c);

		pos=objmesh->pivotpos;
		}
	return 0;
}
