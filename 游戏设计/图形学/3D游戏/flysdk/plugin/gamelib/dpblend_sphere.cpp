#include "..\..\lib\Fly3D.h"
#include "gamelib.h"

void dpblend_sphere::init()
{
	// initialize creating a normal map if one does not exists
	if (normalmap==-1)
	{
		build_normalmap("sphere_normals.tga");
		normalmap=flyengine->get_picture("sphere_normals.tga");
	}
}

void dpblend_sphere::build_normalmap(char *file)
{
	// creates a normal map for a dpblend_sphere
	// and saves it as a 32 bits/pixel TGA image
	if (pxlsize==0)
		return;
	
	int i,j;
	float x,y;
	double d;

	// create picture
	picture p;
	p.CreatePicture32(pxlsize,pxlsize);
	unsigned char *uc=p.buf[0];

	// for each pixel
	for( j=0;j<pxlsize;j++ )
	{
		y=(float)(j-pxlsize/2)/(pxlsize/2);
		for( i=0;i<pxlsize;i++ )
		{
			x=(float)(i-pxlsize/2)/(pxlsize/2);

			// if pixel insied dpblend_sphere
			d=sqrt(x*x+y*y);
			if (d<1.0f)
			{
				// store pixel normal
				uc[0]=(int)(x*127)+128;
				uc[1]=(int)(y*127)+128;
				uc[2]=(int)(cos(d)*127)+128;
				uc[3]=255;
			}
			else 
				uc[0]=uc[1]=uc[2]=uc[3]=0;
			uc+=4;
		}
	}

	// save TGA image in maps subdir
	char name[256];
	strcpy(name,flyengine->flydatapath);
	strcat(name,"maps\\");
	strcat(name,file);
	p.SaveTGA(name);
}

int dpblend_sphere::step(int dt)
{
	// move as subclass particle
	return particle::step(dt);
}

int dpblend_sphere::message(vector& p,float rad,int msg,int param,void *data)
{
	// get closest light illuminating object
	if (msg==FLYOBJM_ILLUM || msg==FLYOBJM_DYNILLUM)
	{
		float dist=(pos-p).length();
		if (dist<rad && dist<lightdist) 
		{
			lightpos=p;
			lightcolor=*((vector *)data);
			lightradius=rad;
			lightdist=dist;
		}
	}

	return 0;
}

void dpblend_sphere::draw()
{
	// draw object as single quad polygon
	// always facing the camera

	static vector x,y;
	x=flyengine->cam->X*radius;
	y=flyengine->cam->Y*radius;

	// select normal map texture
	tc->use(normalmap);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	
	// alpha test for removing points not in
	// dpblend_sphere but in the quad polygon
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER,0);

	// if mode 0 or no register combiner extension
	if (mode==0 || glCombinerParameterfvNV==0)
	{
		// just draw polygon with normal map as texture
		glColor3f(1,1,1);
		
		glBegin(GL_QUADS);
		glTexCoord2f(1,0);
		glVertex3f(pos.x+x.x-y.x, pos.y+x.y-y.y, pos.z+x.z-y.z);
		glTexCoord2f(1,1);
		glVertex3f(pos.x+x.x+y.x, pos.y+x.y+y.y, pos.z+x.z+y.z);
		glTexCoord2f(0,1);
		glVertex3f(pos.x+y.x-x.x, pos.y+y.y-x.y, pos.z+y.z-x.z);
		glTexCoord2f(0,0);
		glVertex3f(pos.x-x.x-y.x, pos.y+-x.y-y.y, pos.z-x.z-y.z);
		glEnd();
	}
	else
	{
		vector dir,color;

		// initialize register combiners
		init_combiners();
		glCombinerParameterfvNV(GL_CONSTANT_COLOR0_NV, &ambient.x);
		glEnable(GL_REGISTER_COMBINERS_NV);

		// if no lights near
		if (lightdist>1e9)
		{
			// clear color (just ambinet)
			glColor4f(0,0,0,0);
			color.null();
		}
		else
		{
			// compute light direction
			dir=(lightpos-pos)*flyengine->cam->mat_t;
			dir.normalize();
			
			// store light dir in the primary color
			glColor4f(
				(dir.x+1.0f)*0.5f,
				(dir.y+1.0f)*0.5f,
				(dir.z+1.0f)*0.5f,
				1.0f);
				
			// set up color based on object diffuse color 
			// and light distance factor
			color=diffuse*lightcolor*(1.0f-lightdist/lightradius);
		}
		glCombinerParameterfvNV(GL_CONSTANT_COLOR1_NV,&color.x);

		// draw quad polygon
		glBegin(GL_QUADS);
		glTexCoord2f(1,0);
		glVertex3f(pos.x+x.x-y.x, pos.y+x.y-y.y, pos.z+x.z-y.z);
		glTexCoord2f(1,1);
		glVertex3f(pos.x+x.x+y.x, pos.y+x.y+y.y, pos.z+x.z+y.z);
		glTexCoord2f(0,1);
		glVertex3f(pos.x+y.x-x.x, pos.y+y.y-x.y, pos.z+y.z-x.z);
		glTexCoord2f(0,0);
		glVertex3f(pos.x-x.x-y.x, pos.y+-x.y-y.y, pos.z-x.z-y.z);
		glEnd();

		// sets no light
		lightdist=1e10;
		// disable redister combiners
		glDisable(GL_REGISTER_COMBINERS_NV);
	}

	// disabe alpha test
	glDisable(GL_ALPHA_TEST);
}

void dpblend_sphere::init_combiners()
{
	// sets up one combiner for dot product of L and N,
	// then multiply diffuse and add ambinet
	glCombinerParameteriNV(GL_NUM_GENERAL_COMBINERS_NV, 1);
	
	/* Argb = expand(texture0rgb) = N */
	glCombinerInputNV(GL_COMBINER0_NV, GL_RGB, GL_VARIABLE_A_NV,
		GL_TEXTURE0_ARB, GL_EXPAND_NORMAL_NV, GL_RGB);

	/* Brgb = expand(primaryrgb) = L */
	glCombinerInputNV(GL_COMBINER0_NV, GL_RGB, GL_VARIABLE_B_NV,
		GL_PRIMARY_COLOR_NV, GL_EXPAND_NORMAL_NV, GL_RGB);
	
	/* spare0rgb = Argb dot Brgb*/
	glCombinerOutputNV(GL_COMBINER0_NV, GL_RGB,
		GL_SPARE0_NV, GL_DISCARD_NV, GL_DISCARD_NV,
		GL_NONE, GL_NONE, GL_TRUE, GL_FALSE, GL_FALSE);

	/* A = one */
	glFinalCombinerInputNV(GL_VARIABLE_A_NV,
		GL_ONE, GL_UNSIGNED_IDENTITY_NV, GL_ALPHA);
	/* B = EF */
	glFinalCombinerInputNV(GL_VARIABLE_B_NV,
		GL_E_TIMES_F_NV, GL_UNSIGNED_IDENTITY_NV, GL_RGB);
	/* C = zero */
	glFinalCombinerInputNV(GL_VARIABLE_C_NV,
		GL_ZERO, GL_UNSIGNED_IDENTITY_NV, GL_RGB);
	/* D = C0 = ambient illumination contribution */
	glFinalCombinerInputNV(GL_VARIABLE_D_NV,
		GL_CONSTANT_COLOR0_NV, GL_UNSIGNED_IDENTITY_NV, GL_RGB);
	/* E = C1 = diffuse material characteristic */
	glFinalCombinerInputNV(GL_VARIABLE_E_NV,
		GL_CONSTANT_COLOR1_NV, GL_UNSIGNED_IDENTITY_NV, GL_RGB);
	/* F = spare0rgb = diffuse illumination contribution = L dot N */
	glFinalCombinerInputNV(GL_VARIABLE_F_NV,
		GL_SPARE0_NV, GL_UNSIGNED_IDENTITY_NV, GL_RGB);
	/* G = one */
	glFinalCombinerInputNV(GL_VARIABLE_G_NV,
		GL_TEXTURE0_ARB, GL_UNSIGNED_IDENTITY_NV, GL_ALPHA);
}

bsp_object *dpblend_sphere::clone()
{
	dpblend_sphere *tmp=new dpblend_sphere;
	*tmp=*this;
	tmp->source=this;
	return tmp;
}

int dpblend_sphere::get_custom_param_desc(int i,param_desc *pd)
{
	if (pd!=0)
	switch(i)
	{
	case 0: 
		pd->type='i';
		pd->data=&mode;
		strcpy(pd->name,"mode");
		break;
	case 1:
		pd->type='i';
		pd->data=&pxlsize;
		strcpy(pd->name,"pxlsize");
		break;
	case 2:
		pd->type='p';
		pd->data=&normalmap;
		strcpy(pd->name,"normalmap");
		break;
	case 3:
		pd->type='c';
		pd->data=&ambient;
		strcpy(pd->name,"ambient");
		break;
	case 4:
		pd->type='c';
		pd->data=&diffuse;
		strcpy(pd->name,"diffuse");
		break;
	}
	return 5;
}

