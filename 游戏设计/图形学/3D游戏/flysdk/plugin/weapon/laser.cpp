#include "..\..\lib\Fly3D.h"
#include "weapon.h"

int laser::step(int dt)
{
	if (node==0)
	{
		life=-1;
		return 0;
	}
		
	flyengine->hitobj=0;
	if (player>=0)
		flyengine->excludecollision=(bsp_object *)directx->players[player].data;
	particle::step(dt);
	flyengine->excludecollision=0;

	if (flyengine->hitobj || life<=0)
		{
		life=-1;
		if (flyengine->hitobj==0)
			if (exp)
				exp->do_explode(pos,Z,player);
			else ;
		else
			{
			pos=flyengine->hitip+flyengine->hitmesh->faces[flyengine->hitface]->normal;
			if (hm && flyengine->hitmesh->localfaces==0)
				{
				hitmark *tmp=(hitmark *)hm->clone();
				tmp->pos=pos;
				tmp->mode=0;
				tmp->align_z(flyengine->hitmesh->faces[flyengine->hitface]->normal);
				flyengine->activate(tmp);
				}
			if (exp)
				exp->do_explode(pos,flyengine->hitmesh->faces[flyengine->hitface]->normal,player);
			}
		}

	if (s)
	{
	vector v=pos-startpos;
	float t=v.length();
	if (t-slast>sfact)
		{	
		v/=t;
		int i=(int)(t/sfact);
		int j=(int)(slast/sfact);
		for( ;j<i;j++ )
			{
			sprite_light *tmp=(sprite_light *)s->clone();
			tmp->pos=startpos+v*(sfact*j);
			tmp->align_z(Z);
			flyengine->activate(tmp);
			}
		slast=t;
		}	
	}

	if (l)
		{
		l->pos=pos;
		l->step(dt);
		}

	force.x=force.y=force.z=0;

	return 1;
}

void laser::draw()
{
	if (node==0 || flyengine->cam==this) 
		return;
	static vector v;

	glDepthMask(GL_FALSE);
	glBlendFunc(GL_ONE,GL_ONE);
	glDisable(GL_CULL_FACE);
	glDisable(GL_FOG);
	glColor4f(1,1,1,1);

	if (fronttexture==-1)
		{
		if (sidetexture!=-1)
			{
			tc->use(sidetexture);
			v=pos-flyengine->cam->pos;
			X.cross(v,Z);
			X.normalize();
			glBegin(GL_QUADS);
			glTexCoord2f(1,1);
			glVertex3f(
				startpos.x-sizetexture*X.x,
				startpos.y-sizetexture*X.y,
				startpos.z-sizetexture*X.z);
			glTexCoord2f(0,1);
			glVertex3f(
				startpos.x+sizetexture*X.x,
				startpos.y+sizetexture*X.y,
				startpos.z+sizetexture*X.z);
			glTexCoord2f(0,0);
			glVertex3f(
				pos.x+sizetexture*X.x,
				pos.y+sizetexture*X.y,
				pos.z+sizetexture*X.z);
			glTexCoord2f(1,0);
			glVertex3f(
				pos.x-sizetexture*X.x,
				pos.y-sizetexture*X.y,
				pos.z-sizetexture*X.z);
			glEnd();
			}
		}
	else
		{
		tc->use(fronttexture);
		X=flyengine->cam->X*sizetexture;
		Y=flyengine->cam->Y*sizetexture;
		if (sidetexture!=-1)
			v=Z*sizetexture;
		else v.x=v.y=v.z=0.0f;
		glBegin(GL_QUADS);
		glTexCoord2f(0,0);
		glVertex3f(
			pos.x-Y.x-X.x+v.x,
			pos.y-Y.y-X.y+v.y,
			pos.z-Y.z-X.z+v.z);
		glTexCoord2f(0,1);
		glVertex3f(
			pos.x+Y.x-X.x+v.x,
			pos.y+Y.y-X.y+v.y,
			pos.z+Y.z-X.z+v.z);
		glTexCoord2f(1,1);
		glVertex3f(
			pos.x+Y.x+X.x+v.x,
			pos.y+Y.y+X.y+v.y,
			pos.z+Y.z+X.z+v.z);
		glTexCoord2f(1,0);
		glVertex3f(
			pos.x-Y.x+X.x+v.x,
			pos.y-Y.y+X.y+v.y,
			pos.z-Y.z+X.z+v.z);
		glEnd();

		sizetexture*=2.0f;
		if (sidetexture!=-1)
			{
			v=pos-flyengine->cam->pos;
			X.cross(v,Z);
			X.normalize();
			X.x*=0.5f; X.y*=0.5f; X.z*=0.5f;

			tc->use(sidetexture);

			glBegin(GL_QUADS);
			glTexCoord2f(1,1);
			glVertex3f(
				pos.x-sizetexture*(Z.x+X.x),
				pos.y-sizetexture*(Z.y+X.y),
				pos.z-sizetexture*(Z.z+X.z));
			glTexCoord2f(1,0);
			glVertex3f(
				pos.x+sizetexture*(Z.x-X.x),
				pos.y+sizetexture*(Z.y-X.y),
				pos.z+sizetexture*(Z.z-X.z));
			glTexCoord2f(0,0);
			glVertex3f(
				pos.x+sizetexture*(Z.x+X.x),
				pos.y+sizetexture*(Z.y+X.y),
				pos.z+sizetexture*(Z.z+X.z));
			glTexCoord2f(0,1);
			glVertex3f(
				pos.x-sizetexture*(Z.x-X.x),
				pos.y-sizetexture*(Z.y-X.y),
				pos.z-sizetexture*(Z.z-X.z));
			glEnd();
			}
		sizetexture*=0.5f;
		}

	glDepthMask(GL_TRUE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	if (flyengine->fog) glEnable(GL_FOG);
	glEnable(GL_CULL_FACE);
	if (l)
		{
		l->pos=pos;
		l->draw();
		}	
}

bsp_object *laser::clone()
{
	laser *tmp=new laser;
	*tmp=*this;
	tmp->source=this;
	return tmp;
}

int laser::get_custom_param_desc(int i,param_desc *pd)
{
	if (pd!=0)
	switch(i)
	{
		case 0:
			pd->type='f';
			pd->data=&sizetexture;
			strcpy(pd->name,"sizetexture");
			break;
		case 1:
			pd->type='p';
			pd->data=&fronttexture;
			strcpy(pd->name,"fronttexture");
			break;
		case 2:
			pd->type='p';
			pd->data=&sidetexture;
			strcpy(pd->name,"sidetexture");
			break;
		case 3:
			pd->type=TYPE_EXPLODE;
			pd->data=&exp;
			strcpy(pd->name,"explode");
			break;
		case 4:
			pd->type=TYPE_LIGHT;
			pd->data=&l;
			strcpy(pd->name,"light");
			break;
		case 5:
			pd->type=TYPE_SPRITE_LIGHT;
			pd->data=&s;
			strcpy(pd->name,"sprite");
			break;
		case 6:
			pd->type='f';
			pd->data=&sfact;
			strcpy(pd->name,"spritefactor");
			break;
		case 7:
			pd->type=TYPE_HITMARK;
			pd->data=&hm;
			strcpy(pd->name,"hitmark");
			break;
		case 8:
			pd->type='f';
			pd->data=&damage;
			strcpy(pd->name,"damage");
			break;
	}
	return 9;
}

void laser::fire(vector& p,vector& dir,float v,int playerid)
{
	laser *m=(laser *)clone();
	m->startpos=m->pos=p;
	m->vel=dir*v;
	m->align_z(dir);
	m->player=playerid;
	flyengine->activate(m);
}
