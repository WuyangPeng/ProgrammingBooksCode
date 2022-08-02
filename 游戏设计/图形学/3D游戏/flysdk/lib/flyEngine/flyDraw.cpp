#include "..\Fly3D.h"

void flyEngine::draw_static_faces_cartoon(int *fd,int nfd)
{
	int i;
	face *f;
	tc->use(cartoonpicbsp);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
	glColor3ub(255,255,255);
	glBegin(GL_TRIANGLES);
	for( i=0;i<nfd;i++ )
	{
		f=&faces[fd[i]];
		glTexCoord2f(f->uv[0][0],0.0f);
		glColor3fv((float *)&vertcolor[f->vert[0]-vert]);
		glVertex3fv((float *)f->vert[0]);
		glTexCoord2f(f->uv[1][0],0.0f);
		glColor3fv((float *)&vertcolor[f->vert[1]-vert]);
		glVertex3fv((float *)f->vert[1]);
		glTexCoord2f(f->uv[2][0],0.0f);
		glColor3fv((float *)&vertcolor[f->vert[2]-vert]);
		glVertex3fv((float *)f->vert[2]);
	}
	glEnd();
}

void flyEngine::draw_static_faces(int *fd,int nfd)
{
	int i,mapcount=0;
	face *f;

	glColor3ub(255,255,255);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LESS);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// if using multitexture
	if (multitexture && ntextureunits>1 && nlm)
	{
		// use two texture units
		glBegin(GL_TRIANGLES);
		for( i=0;i<nfd;i++ )
			{
			f=&faces[fd[i]];
			tc->use_triangles(f->texpic,0);
			if (f->lm!=-1)
				tc->use_triangles(lm[f->lm]->pic+lmbase,1);
			else tc->use_triangles(-1,1);
			glMultiTexCoord2fvARB(GL_TEXTURE0_ARB,f->uv[0]);
			glMultiTexCoord2fvARB(GL_TEXTURE1_ARB,f->lmuv[0]);
			glVertex3fv((float *)f->vert[0]);
			glMultiTexCoord2fvARB(GL_TEXTURE0_ARB,f->uv[1]);
			glMultiTexCoord2fvARB(GL_TEXTURE1_ARB,f->lmuv[1]);
			glVertex3fv((float *)f->vert[1]);
			glMultiTexCoord2fvARB(GL_TEXTURE0_ARB,f->uv[2]);
			glMultiTexCoord2fvARB(GL_TEXTURE1_ARB,f->lmuv[2]);
			glVertex3fv((float *)f->vert[2]);
			}
		glEnd();
		tc->use(-1,1);
		tc->use(-1);
		mapcount+=2;
	}
	else // not using multitexture
	{
		// texture layer
		if (mapmode&MAPPING_TEXTURE)
		{
			glDisable(GL_TEXTURE_2D);
			glBegin(GL_TRIANGLES);
			if (vertcolor)	// use vertex colors?
				for( i=0;i<nfd;i++ )
					{
					f=&faces[fd[i]];
					tc->use_triangles(f->texpic);
					glTexCoord2fv(f->uv[0]);
					glColor3fv((float *)&vertcolor[f->vert[0]-vert]);
					glVertex3fv((float *)f->vert[0]);
					glTexCoord2fv(f->uv[1]);
					glColor3fv((float *)&vertcolor[f->vert[1]-vert]);
					glVertex3fv((float *)f->vert[1]);
					glTexCoord2fv(f->uv[2]);
					glColor3fv((float *)&vertcolor[f->vert[2]-vert]);
					glVertex3fv((float *)f->vert[2]);
					}
			else
				for( i=0;i<nfd;i++ )
					{
					f=&faces[fd[i]];
					tc->use_triangles(f->texpic);
					glTexCoord2fv(f->uv[0]);
					glVertex3fv((float *)f->vert[0]);
					glTexCoord2fv(f->uv[1]);
					glVertex3fv((float *)f->vert[1]);
					glTexCoord2fv(f->uv[2]);
					glVertex3fv((float *)f->vert[2]);
					}
			glEnd();
			glColor3ub(255,255,255);
			mapcount++;
		}
		
		// detail layer
		if (mapmode&MAPPING_DETAIL)
		if (detailpic!=-1)
			{
			if (mapcount)
				{
				glBlendFunc(GL_ZERO,GL_SRC_COLOR);
				glDepthMask(GL_FALSE);
				glDepthFunc(GL_EQUAL);
				}
			tc->use(detailpic);
//			glMatrixMode( GL_TEXTURE );
//			glScalef(detailtile,detailtile,1.0f);
			glBegin(GL_TRIANGLES);
			for( i=0;i<nfd;i++ )
			{
				f=&faces[fd[i]];
				glTexCoord2f(f->uv[0][0]*detailtile,f->uv[0][1]*detailtile);
				glVertex3fv((float *)f->vert[0]);
				glTexCoord2f(f->uv[1][0]*detailtile,f->uv[1][1]*detailtile);
				glVertex3fv((float *)f->vert[1]);
				glTexCoord2f(f->uv[2][0]*detailtile,f->uv[2][1]*detailtile);
				glVertex3fv((float *)f->vert[2]);
			}
			glEnd();
//			glLoadIdentity();
//			glMatrixMode( GL_MODELVIEW );
			mapcount++;
			}

		// lightmap layer
		if (mapmode&MAPPING_LIGHTMAP)
		if (nlm!=NULL)
			{
			if (mapcount)
				{
				glBlendFunc(GL_ZERO,GL_SRC_COLOR);
				glDepthMask(GL_FALSE);
				glDepthFunc(GL_EQUAL);
				}
			glBegin(GL_TRIANGLES);
			for( i=0;i<nfd;i++ )
				{
				f=&faces[fd[i]];
				if (f->lm!=-1)
					{
					tc->use_triangles(lm[f->lm]->pic+lmbase);
					glTexCoord2fv(f->lmuv[0]);
					glVertex3fv((float *)f->vert[0]);
					glTexCoord2fv(f->lmuv[1]);
					glVertex3fv((float *)f->vert[1]);
					glTexCoord2fv(f->lmuv[2]);
					glVertex3fv((float *)f->vert[2]);
					}
				}
			glEnd();
			mapcount++;
			}
	}

	// fogmap layer
	if (mapmode&MAPPING_FOGMAP)
	if (nlm!=0)
		{
		if (mapcount)
			{
			glDepthMask(GL_FALSE);
			glDepthFunc(GL_EQUAL);
			glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
			}
		glBegin(GL_TRIANGLES);
		for( i=0;i<nfd;i++ )
			{
			f=&faces[fd[i]];
			if (f->lm!=-1)
			if (fm[f->lm]->lastupdate>=flyengine->cur_step_base)
				{
				tc->use_triangles(fm[f->lm]->pic+fmbase);
				glTexCoord2fv(f->lmuv[0]);
				glVertex3fv((float *)f->vert[0]);
				glTexCoord2fv(f->lmuv[1]);
				glVertex3fv((float *)f->vert[1]);
				glTexCoord2fv(f->lmuv[2]);
				glVertex3fv((float *)f->vert[2]);
				}
			}
		glEnd();
		}

	tc->use(-1);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LESS);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void mesh::draw()
{
	lastdraw=flyengine->cur_frame;
	int i;
	glBegin(GL_TRIANGLES);
	for( i=0;i<nf;i++ )
		{
		tc->use_triangles(localfaces[i].texpic);

		glColor4f(
			color.x*localfaces[i].color.x,
			color.y*localfaces[i].color.y,
			color.z*localfaces[i].color.z,
			color.w*localfaces[i].color.w);
	
		glNormal3fv(&localfaces[i].vertnormal[0].x);
		glTexCoord2f(localfaces[i].uv[0][0]+scrollu,localfaces[i].uv[0][1]+scrollv);
		glVertex3fv(&localfaces[i].vert[0]->x);

		glNormal3fv(&localfaces[i].vertnormal[1].x);
		glTexCoord2f(localfaces[i].uv[1][0]+scrollu,localfaces[i].uv[1][1]+scrollv);
		glVertex3fv(&localfaces[i].vert[1]->x);

		glNormal3fv(&localfaces[i].vertnormal[2].x);
		glTexCoord2f(localfaces[i].uv[2][0]+scrollu,localfaces[i].uv[2][1]+scrollv);
		glVertex3fv(&localfaces[i].vert[2]->x);
		}
	glEnd();
}

void flyEngine::start_text_mode()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,screen_sx,0,screen_sy,-1,1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_FOG);
	glDepthMask(GL_FALSE);
	glBlendFunc(GL_ONE,GL_ONE);
	glColor3ub(255,255,255);
}

int flyEngine::draw_text(int x,int y,char *text)
{
	int len=strlen(text),i,s=0;
	float xx,yy,xy=1.0f/FONTS_NUM;

	y=screen_sy-y-FONTS_SIZE;
	for( i=0;i<len;i++ )
		s+=flyengine->fonts_width[text[i]-32];

	tc->use(fontspic);

	for( i=0;i<len;i++ )
		{
		xx=((text[i]-32)%FONTS_NUM)*xy;
		yy=((text[i]-32)/FONTS_NUM)*xy;

		glColor3ub(255,255,255);
		glBegin(GL_QUADS);
		glTexCoord2f(xx+xy,yy+xy);
		glVertex2i(x+FONTS_SIZE,y);

		glTexCoord2f(xx+xy,yy);
		glVertex2i(x+FONTS_SIZE,y+FONTS_SIZE);

		glTexCoord2f(xx,yy);
		glVertex2i(x,y+FONTS_SIZE);

		glTexCoord2f(xx,yy+xy);
		glVertex2i(x,y);
		glEnd();

		x+=flyengine->fonts_width[text[i]-32];
		}
	
	return s;
}

int flyEngine::draw_text_center(int x,int y,char *text)
{
	int len=strlen(text),i,s=0;
	float xx,yy,xy=1.0f/FONTS_NUM;

	y=screen_sy-y-FONTS_SIZE;
	for( i=0;i<len;i++ )
		s+=flyengine->fonts_width[text[i]-32];
	x-=s/2;

	tc->use(fontspic);

	for( i=0;i<len;i++ )
		{
		xx=((text[i]-32)%FONTS_NUM)*xy;
		yy=((text[i]-32)/FONTS_NUM)*xy;
		glColor3ub(255,255,255);
		glBegin(GL_QUADS);
		glTexCoord2f(xx+xy,yy+xy);
		glVertex2i(x+FONTS_SIZE,y);

		glTexCoord2f(xx+xy,yy);
		glVertex2i(x+FONTS_SIZE,y+FONTS_SIZE);

		glTexCoord2f(xx,yy);
		glVertex2i(x,y+FONTS_SIZE);

		glTexCoord2f(xx,yy+xy);
		glVertex2i(x,y);
		glEnd();

		x+=flyengine->fonts_width[text[i]-32];
		}
	
	return s;
}

void flyEngine::end_text_mode()
{
	glBlendFunc(GL_ONE,GL_ONE);
	glColor3ub(255,255,255);

	if (crosshairpic!=-1)
		{
		int i,j;
		i=screen_sx>>1;
		j=screen_sy>>1;
		tc->use(crosshairpic);
		glBegin(GL_QUADS);
			glTexCoord2f(0,1);
			glVertex2i(i-crosshairsize,j-crosshairsize);
			glTexCoord2f(1,1);
			glVertex2i(i+crosshairsize,j-crosshairsize);
			glTexCoord2f(1,0);
			glVertex2i(i+crosshairsize,j+crosshairsize);
			glTexCoord2f(0,0);
			glVertex2i(i-crosshairsize,j+crosshairsize);
		glEnd();
		}
	
	if (cur_time - status_msg_time < 2000)
		draw_text( screen_sx/2, 0, status_msg );

	if (filter.x>0 || filter.y>0 || filter.z>0)
		{
		tc->use(-1);
		glColor3fv(&filter.x);
		glRecti(0, 0, screen_sx, screen_sy);
		glColor3ub(255,255,255);
		}
	
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	if (introtime>0 && intropic!=-1)
	{
		int i;
		if (introtime>1000)
			i=0;
		else i=screen_sy-introtime*screen_sy/1000;
		introtime-=flyengine->cur_dt;
		tc->use(intropic);
		glBegin(GL_QUADS);
			glTexCoord2f(0,1);
			glVertex2i(0,i);
			glTexCoord2f(1,1);
			glVertex2i(screen_sx,i);
			glTexCoord2f(1,0);
			glVertex2i(screen_sx,i+screen_sy);
			glTexCoord2f(0,0);
			glVertex2i(0,i+screen_sy);
		glEnd();
	}
	
	if (flyengine->con.mode)
		flyengine->con.draw();

	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	if (fog)
		glEnable(GL_FOG);
	tc->use(-1);
}

void anim_mesh::draw()
{
	int i,j,k,n;
	tc->use(texpic);
	if (nstripfan)
		{
			glCullFace(GL_FRONT);
			glColor3fv(&color.x);
			k=0;
			for( i=0;i<nstripfan;i++ )
			{
				n=abs(stripfancount[i]);
				if (stripfancount[i]>0)
					glBegin(GL_TRIANGLE_STRIP);
				else glBegin(GL_TRIANGLE_FAN);

				for( j=0;j<n;j++,k++ )
					{
					glTexCoord2fv(&vertdata[k].u);
					glNormal3fv(&vertnorm[stripfanvert[k]].x);
					glVertex3fv((float *)&vert[stripfanvert[k]]);
					}

				glEnd();
			}
			glCullFace(GL_BACK);
		}
	else 
		{
			glColor3fv(&color.x);
			glBegin(GL_TRIANGLES);
			for( i=0;i<nf;i++ )
			{
				glTexCoord2fv(localfaces[i].uv[0]);
				glNormal3fv(&localfaces[i].vertnormal[0].x);
				glVertex3fv((float *)localfaces[i].vert[0]);

				glTexCoord2fv(localfaces[i].uv[1]);
				glNormal3fv(&localfaces[i].vertnormal[1].x);
				glVertex3fv((float *)localfaces[i].vert[1]);

				glTexCoord2fv(localfaces[i].uv[2]);
				glNormal3fv(&localfaces[i].vertnormal[2].x);
				glVertex3fv((float *)localfaces[i].vert[2]);
			}
			glEnd();
		}
}

void bsp_object::draw()
{
	mesh *objmesh=get_mesh();
	if (objmesh)
	{
		glPushMatrix();
		glTranslatef(pos.x,pos.y,pos.z);
		glMultMatrixf((float *)&mat);
		objmesh->draw();
		glPopMatrix();
	}
}

void mesh::draw_cartoon(vector& campos,vector& light,light_vertex& lights,float edgewidth)
{
	int i,j;
	float dot;
	vector dir;
	static float vtc[MAX_VERT];

	// compute light factor for each mesh vertex
	memset(vtc,0,sizeof(float)*nv);
	for( j=0;j<lights.nlights;j++ )
	{
		// compute color change
		dot=lights.pos[j].length()/lights.radius[j];
		if (dot<1.0f)
			light+=lights.color[j]*(1.0f-dot);

		// compute vertex intensity
		for( i=0;i<nv;i++ )
		{
			dir=lights.pos[j]-vert[i];
			dir.normalize();
			dot=vec_dot(dir,vertnorm[i]);
			if (FP_SIGN_BIT(dot)==0)
				vtc[i]+=dot;
		}
	}

	// draw using the 1D texture and vertex light factors
	tc->use(flyengine->cartoonpic);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
	glBegin(GL_TRIANGLES);
	for( i=0;i<nf;i++ )
	{
		glColor3f(
			localfaces[i].color.x*light.x,
			localfaces[i].color.y*light.y,
			localfaces[i].color.z*light.z);

		glTexCoord2f(vtc[localfaces[i].vert[0]-vert],0);
		glVertex3fv((float *)localfaces[i].vert[0]);

		glTexCoord2f(vtc[localfaces[i].vert[1]-vert],0);
		glVertex3fv((float *)localfaces[i].vert[1]);

		glTexCoord2f(vtc[localfaces[i].vert[2]-vert],0);
		glVertex3fv((float *)localfaces[i].vert[2]);
	}
	glEnd();

	// draw outline as lines without texture
	tc->use(-1);
	glDepthMask(GL_FALSE);
	glLineWidth(edgewidth);
	glColor3fv(&flyengine->cartooncolor.x);

	glBegin(GL_LINES);
	// for each edge
	for( i=j=0;i<nedges;i++,j+=4 )
	{
		// check is edge is shared by a frontface and a backface
		dir=campos-vert[edges[j]];
		if (edges[j+3]==-1 || 
			vec_dot(dir,localfaces[edges[j+2]].normal)*
			vec_dot(dir,localfaces[edges[j+3]].normal)<0.0f)
		{
			// if so, draw edge
			glVertex3fv((float *)&vert[edges[j]]);
			glVertex3fv((float *)&vert[edges[j+1]]);
		}
	}
	glEnd();

	glLineWidth(1.0f);
	glColor3ub(255,255,255);
	glDepthMask(GL_TRUE);
}

void flyEngine::draw_bsp_edges()
{
	int i,j,e;
	vector dir;
	
	tc->use(-1);
	glDepthMask(GL_FALSE);
	glLineWidth(cartoonwidth);
	glColor3fv(&cartooncolor.x);

	glBegin(GL_LINES);
	for( j=0;j<3;j++ )
		for( i=0;i<nfacedraw;i++ )
		{
		e=faceedges[facedraw[i]*3+j]*5;
		if (edges[e+4]<cur_frame)
			{
			edges[e+4]=cur_frame;
			dir=flyengine->cam->pos-vert[edges[e]];
			if (edges[e+3]==-1 || 
				vec_dot(dir,faces[edges[e+2]].normal)*
				vec_dot(dir,faces[edges[e+3]].normal)<0.0f)
				{
				glVertex3fv(&vert[edges[e]].x);
				glVertex3fv(&vert[edges[e+1]].x);
				}
			}
		}
	glEnd();

	glLineWidth(1.0f);
	glColor3ub(255,255,255);
	glDepthMask(GL_TRUE);
}

void mesh::draw_shadow_volume(vector& lightdir)
{
	static vector v[8];

	tc->use(-1);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_ALWAYS,0,~0);
	glColorMask(GL_FALSE,GL_FALSE,GL_FALSE,GL_FALSE);
	glDepthMask(GL_FALSE);

	for( int i=0;i<nf;i++ )
	if (vec_dot(localfaces[i].normal,lightdir)>0)
		{
		v[0]=*localfaces[i].vert[0];
		v[1]=v[0]-lightdir;
		v[2]=*localfaces[i].vert[1];
		v[3]=v[2]-lightdir;
		v[4]=*localfaces[i].vert[2];
		v[5]=v[4]-lightdir;
		v[6]=v[0];
		v[7]=v[1];

		glVertexPointer(3,GL_FLOAT,sizeof(vector),v);

		glStencilOp(GL_KEEP,GL_KEEP,GL_INCR);
		glCullFace(GL_BACK);
		glDrawArrays(GL_QUAD_STRIP,0,8);

		glStencilOp(GL_KEEP,GL_KEEP,GL_DECR);
		glCullFace(GL_FRONT);
		glDrawArrays(GL_QUAD_STRIP,0,8);
		}

	glDisableClientState(GL_VERTEX_ARRAY);
	glStencilOp(GL_KEEP,GL_KEEP,GL_KEEP);
	glDisable(GL_STENCIL_TEST);
	glCullFace(GL_BACK);
	glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE);
	glDepthMask(GL_TRUE);
}
