#include "../Fly3D.h"

FLY_API flyEngine *flyengine=0;
FLY_API HWND hFlyWnd=0;
FLY_API HINSTANCE hFlyInst=0;

FLY_API void init_engine(HWND hWnd,HINSTANCE hInst,int appid)
{
	free_engine();
	set_engine(new flyEngine,hWnd,hInst,appid);
}

FLY_API void set_engine(flyEngine *eng,HWND hWnd,HINSTANCE hInst,int appid)
{
	flyengine=eng;
	flyengine->appid=appid;
	hFlyWnd=hWnd;
	hFlyInst=hInst;
}

FLY_API void free_engine()
{
	if (flyengine)
		delete flyengine;
	flyengine=0;
}

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
    }
    return TRUE;
}

flyEngine::flyEngine()
{
	cur_step=cur_step_base=0;
	cur_frame=cur_frame_base=0;
	start_time=cur_time=cur_dt=0;
	intropic=introtime=0;

	player=0;
	cam=0;
	excludecollision=0;
	stepobj=0;

	nelemdraw=0;
	facedraw=0;
	nfacedraw=0;
	facedrawtransp=0;
	nfacedrawtransp=0;

	status_msg_time=0;
		
	bboxdiag=viewmaxdist=viewmindist=camangle=aspect=geomdetail=
		curveerr=lmpxsize=detailtile=cartoonwidth=shadowdepth=0;
	
	nodedrawcount=nodeonly=pvsoff=fog=mpdelay=antialias=
		amblight=mapmode=shadows=noinput=wireframe=mute=mouse=
		clearbk=moving=crosshairpic=crosshairsize=appid=multitexture=
		detailpic=hwlights=stencil=cartoonpic=cartoonpicbsp=0;

	active_obj0=last_active_obj=0;
	stock_obj0=0;
	model_obj0=0;
	sound_obj0=0;
	bezier_curve0=0;
	bezier_patch0=0;
	shadow_obj=0;
	hitobj=0;
	hitmesh=0;
	hitface=0;

	status=0;
	fontspic=0;
	consolepic=0;

	vert=vertcolor=vertnormal=0;
	nvert=0;

	faces=0;
	nfaces=0;

	edges=0;
	nedges=0;
	faceedges=0;

	bsp=0;
	npiclib=0;
	nlm=lmbase=nlmpic=0;
	fmbase=0;

	pvs=0;
	leaf=0;
	nleaf=pvssize=pvsrowsize=0;
	
	reset();

	appid=FLYAPPID_NONE;
	start_time=timeGetTime();

	strcpy(flysdkpath,GetCommandLine());
	if (flysdkpath[0]=='\"')
	{
		strcpy(flysdkpath,&flysdkpath[1]);
		if (strchr(flysdkpath,'\"')) 
			*strchr(flysdkpath,'\"')=0;
	}
	if (strrchr(flysdkpath,'\\'))
		*(strrchr(flysdkpath,'\\')+1)=0;
	else 
	{
		GetCurrentDirectory(255,flysdkpath);
		strcat(flysdkpath,"\\");
	}
	strlwr(flysdkpath);
}

void flyEngine::reset()
{
	int i;
	bsp_object *d;
	mesh *o;
	sound *s;
	bezier_curve *c;
	bezier_patch *p;

	while(active_obj0)
		{
		d=(bsp_object *)active_obj0->next_obj;
		delete active_obj0;
		active_obj0=d;
		}
	last_active_obj=0;
	while(stock_obj0)
		{
		d=(bsp_object *)stock_obj0->next_obj;
		delete stock_obj0;
		stock_obj0=d;
		}
	while(model_obj0)
		{
		o=(mesh *)model_obj0->next_obj;
		delete model_obj0;
		model_obj0=o;
		}
	while(sound_obj0)
		{
		s=(sound *)sound_obj0->next_obj;
		delete sound_obj0;
		sound_obj0=s;
		}
	while(bezier_curve0)
		{
		c=(bezier_curve *)bezier_curve0->next_obj;
		delete bezier_curve0;
		bezier_curve0=c;
		}
	while(bezier_patch0)
		{
		p=(bezier_patch *)bezier_patch0->next_obj;
		delete bezier_patch0;
		bezier_patch0=p;
		}

	if (bsp) 
		delete bsp;
	bsp=0;

	if (vert)
		delete vert;
	vert=0;

	if (vertnormal)
		delete vertnormal;
	vertnormal=0;

	if (vertcolor)
		delete vertcolor;
	vertcolor=0;

	if (faces)
		delete faces;
	faces=0;

	if (edges)
		delete edges;
	edges=0;

	if (faceedges)
		delete faceedges;
	faceedges=0;

	nvert=0;
	nfaces=0;
	nedges=0;

	if (npiclib)
		for( i=0;i<npiclib;i++ )
			delete piclib[i];
	npiclib=0;

	if (pvs)
		delete pvs;
	pvs=0;
	pvssize=0;
	pvsrowsize=0;

	if (leaf)
		delete leaf;
	leaf=0;
	nleaf=0;

	if (facedraw)
		delete facedraw;
	facedraw=0;

	if (facedrawtransp)
		delete facedrawtransp;
	facedrawtransp=0;

	for( i=0;i<nlmpic;i++ )
		{
		delete lmpic[i];
		delete fmpic[i];
		}
	for( i=0;i<nlm;i++ )
		{
		delete lm[i];
		delete fm[i];
		}
	nlm=0;
	nlmpic=0;
	lmbase=0;
	fmbase=0;

	dll.reset();

	fontspic=-1;
	crosshairpic=-1;
	detailpic=-1;
	intropic=-1;
	consolepic=-1;
	cartoonpicbsp=-1;
	cartoonpic=-1;

	bspfile[0]=0;
	flydatapath[0]=0;
	flyfile[0]=0;
	flyfilename[0]=0;
	console_command[0]=0;
	status_msg[0]=0;
	status_msg_time=0;

	nodedrawcount=nfacedraw=nfacedrawtransp=0;

	cur_frame=cur_frame_base=0;
	cur_step=cur_step_base=0;
	cur_time=cur_dt=0;

	filter.vec(0,0,0);
	background.vec(0,0,0);
	clearbk=1;
	introtime=2000;

	cam=0;
	player=0;
}

void flyEngine::compute_normals()
{
	// simple and fast vertex normals
	int i,j;
	if (vertnormal)
		delete vertnormal;
	vertnormal=new vector[nvert];
	memset(vertnormal,0,sizeof(vector)*nvert);
	for( j=0;j<nfaces;j++ )
	{
		vertnormal[faces[j].vert[0]-vert]+=faces[j].normal;
		vertnormal[faces[j].vert[1]-vert]+=faces[j].normal;
		vertnormal[faces[j].vert[2]-vert]+=faces[j].normal;
	}
	for( i=0;i<nvert;i++ )
		vertnormal[i].normalize();

	for( i=0;i<nfaces;i++ )
		for( j=0;j<3;j++ )
			faces[i].vertnormal[j]=vertnormal[faces[i].vert[j]-vert];
/*
	// more accurate and slower vertex normals
	if (vertnormal)
		delete vertnormal;
	vector *nn=new vector[nfaces];
	vertnormal=new vector[nvert];
	int i,j,k,nc;
	for( i=0;i<nvert;i++ )
		{
		nc=0;
		for( j=0;j<nfaces;j++ )
			if (faces[j].vert[0]==&vert[i] ||
				faces[j].vert[1]==&vert[i] ||
				faces[j].vert[2]==&vert[i])
				{
				for( k=0;k<nc;k++ )
					if (vec_dot(faces[j].normal,nn[k])>0.999848f)
						break;
				if (k==nc)
					nn[nc++]=faces[j].normal;
				}
		vertnormal[i].null();
		if (nc)
			{
			for( k=0;k<nc;k++ )
				vertnormal[i]+=nn[k];
			vertnormal[i].normalize();
			}
		}
	for( i=0;i<nfaces;i++ )
		for( j=0;j<3;j++ )
			faces[i].vertnormal[j]=vertnormal[faces[i].vert[j]-vert];
	delete nn;
*/
	// bound box
	bbox1.vec(BIG,BIG,BIG);
	bbox2.vec(-BIG,-BIG,-BIG);

	for( i=0;i<nvert;i++ )
	{
		if (vert[i].x>bbox2.x)
			bbox2.x=vert[i].x;
		if (vert[i].y>bbox2.y)
			bbox2.y=vert[i].y;
		if (vert[i].z>bbox2.z)
			bbox2.z=vert[i].z;

		if (vert[i].x<bbox1.x)
			bbox1.x=vert[i].x;
		if (vert[i].y<bbox1.y)
			bbox1.y=vert[i].y;
		if (vert[i].z<bbox1.z)
			bbox1.z=vert[i].z;
	}

	bboxdiag=(bbox2-bbox1).length();
	bboxC=(bbox1+bbox2)*0.5f;
}

int flyEngine::collision_bsp(bsp_node *n,vector& p1,vector& p2,int elemtype,float rad)
{
	if (n->leaf!=-1)
	{
		bsp_object *e=n->elem;
		vector rd=p2-p1;
		float dist=1.0f,d;
		mesh *m;
		vector ip;
		int f;
		
		hitobj=0;

		while(e)
		{
			if	(e!=flyengine->excludecollision && 
				(elemtype==0 || e->type==elemtype))
			{
				m=e->ray_intersect(p1,rd,ip,d,f,rad);
				if (m && d<dist)
				{
					dist=d;
					hitobj=e;
					hitip=ip;
					hitface=f;
					hitmesh=m;
				}
			}
			e=e->next_elem;
		}

		if (hitobj)
			return 1;
		else return 0;
	}

	float d1=vec_dot(n->normal,p1)+n->d0, 
		d2=vec_dot(n->normal,p2)+n->d0;
	
	if(d1<-rad && d2<-rad)
		if (n->child[1])
			return collision_bsp(n->child[1],p1,p2,elemtype,rad);
		else return 0;
	else 
	if(d1>rad && d2>rad)
		if (n->child[0])
			return collision_bsp(n->child[0],p1,p2,elemtype,rad);
		else return 0;
	else 
		{
		if (d1>0)
			{
			if (n->child[0])
				if (collision_bsp(n->child[0],p1,p2,elemtype,rad))
					return 1;
			if (n->child[1])
				if (collision_bsp(n->child[1],p1,p2,elemtype,rad))
					return 1;
			}
		else
			{
			if (n->child[1])
				if (collision_bsp(n->child[1],p1,p2,elemtype,rad))
					return 1;
			if (n->child[0])
				if (collision_bsp(n->child[0],p1,p2,elemtype,rad))
					return 1;
			}

		return 0;
		}
}

void flyEngine::compute_edges()
{
	if (edges)
		delete edges;
	edges=new int[nfaces*3*5];
	if (faceedges)
		delete faceedges;
	faceedges=new int[nfaces*3];
	nedges=0;
	int i1,i2;
	int i,j,nc,k;

	for( i=0;i<nfaces;i++ )
		for( j=0;j<3;j++ )
		{
			i1=faces[i].vert[j]-vert;
			i2=faces[i].vert[(j+1)%3]-vert;
			nc=0;
			for( k=0;k<nedges;k++,nc+=5 )
				if ((i1==edges[nc] && i2==edges[nc+1]) ||
					(i1==edges[nc+1] && i2==edges[nc]))
					break;
			if (k==nedges)
			{
				edges[nc]=i1;
				edges[nc+1]=i2;
				edges[nc+2]=i;
				edges[nc+3]=-1;
				edges[nc+4]=0;
				faceedges[i*3+j]=nedges;
				nedges++;
			}
			else 
			{
				faceedges[i*3+j]=k;
				if ((faces[i].color-faces[edges[nc+2]].color).length()<0.1f)
					edges[nc+3]=i;
			}
		}
}

void flyEngine::draw_bsp(int mode)
{
	nodedrawcount=0;
	nelemdraw=0;
	memset(nelemlatedraw,0,sizeof(int)*MAX_LATEDRAW_LAYERS);
	nfacedraw=0;
	nfacedrawtransp=0;
	
	draw_bsp(bsp);

	if (mode)
	{
		if (edges==0)
			compute_edges();
		draw_static_faces_cartoon(facedraw,nfacedraw);
		draw_bsp_edges();
	}
	else
	{
		if (nfacedraw)
			draw_static_faces(facedraw,nfacedraw);
		if (nfacedrawtransp)
			draw_static_faces(facedrawtransp,nfacedrawtransp);
	}

	int i,j;
	for( i=0;i<nelemdraw;i++ )
		elemdraw[i]->draw();
	for( j=0;j<MAX_LATEDRAW_LAYERS;j++ )
		for( i=0;i<nelemlatedraw[j];i++ )
			elemlatedraw[j][i]->draw();
}

void flyEngine::draw_bsp(bsp_node *n)
{
	if (n->leaf!=-1)
		{
		if (cam->node==0 || (nodeonly && n!=cam->node))
			return;
		if (pvsoff || PVS_TEST(cam->node->leaf,n->leaf))
			{
			bsp_object *e=n->elem;
			while(e)
				{
				if (e->type==TYPE_STATIC_MESH)
					{
					static_mesh *o=(static_mesh *)e;
					o->objmesh->lastdraw=cur_frame;
					for( int i=0;i<o->objmesh->nf;i++ )
						if (o->objmesh->faces[i]->lastdraw!=cur_frame)
						{
						if (FP_BITS(o->objmesh->faces[i]->color.w)==FP_ONE_BITS)
							facedraw[nfacedraw++]=o->objmesh->faces[i]->indx;
						else if (FP_BITS(o->objmesh->faces[i]->color.w)!=0)
							facedrawtransp[nfacedrawtransp++]=o->objmesh->faces[i]->indx;
						o->objmesh->faces[i]->lastdraw=cur_frame;
						}
					}
				else 
					elemlatedraw[e->latedraw&7][nelemlatedraw[e->latedraw&7]++]=e;
				e=e->next_elem;
				}
			nodedrawcount++;
			}
		return;
		}

	float x1,x2;
	int i;

	x1=n->distance(frustrum[0]);
	for( i=1;i<5;i++ )
		{
		x2=n->distance(frustrum[i]);
		if (x1*x2<=0)
			break;
		}
	if (i==5)
		if (x1>0)
		{
			if (n->child[0]) 
				draw_bsp(n->child[0]);
		}
		else 
		{ 
			if (n->child[1]) 
				draw_bsp(n->child[1]);
		}
	else 
		if (x1<0)
			{
			if (n->child[1]) 
				draw_bsp(n->child[1]);
			if (n->child[0]) 
				draw_bsp(n->child[0]);
			}
		else 
			{
			if (n->child[0]) 
				draw_bsp(n->child[0]);
			if (n->child[1]) 
				draw_bsp(n->child[1]);
			}
}

int flyEngine::step()
{		
	static int dt,t0=timeGetTime()-start_time;

	// compute elapsed time
	cur_time=timeGetTime()-start_time;
	dt=cur_time-t0;
	if (dt>0)
		{
		t0=cur_time;
		if (dt<1000)
			{
			step(dt);
			return dt;
			}
		}
	return 0;
}

void flyEngine::step(int dt)
{
	if (flyengine->player==0 || flyengine->cam==0 || flyengine->bsp==0)
		return;

	// process console commands
	if (flyengine->console_command[0])
		{
		char *c=flyengine->console_command;
		do
			{
			flyengine->con.command_exec(c);
			c=strchr(c,';');
			if (c)
				*(c++)=0;
			} 
		while(c);
		}
	flyengine->console_command[0]=0;

	int i;
	// if not in server mode
	if (directx->mpmode!=FLYMP_SERVER)
	{
	// get input
	if (noinput)
		{
		memset(directx->diks,0,sizeof(directx->diks));
		memset(&directx->dims,0,sizeof(directx->dims));
		}
	else directx->get_input();

	// attebuate filter
	if (FP_BITS(filter.x)!=0)
		{
		filter.x-=dt/500.0f;
		if (FP_SIGN_BIT(filter.x)) filter.x=0;
		}
	if (FP_BITS(filter.y)!=0)
		{
		filter.y-=dt/500.0f;
		if (FP_SIGN_BIT(filter.y)) filter.y=0;
		}
	if (FP_BITS(filter.z)!=0)
		{
		filter.z-=dt/500.0f;
		if (FP_SIGN_BIT(filter.z)) filter.z=0;
		}

	// if a texture cache available
	if (tc)
	for( i=0;i<nlm;i++ )
		{
		// update changed lightmaps
		if (lm[i]->lastupdate)
			{
			lm[i]->load(lmpic[lm[i]->pic]);
			lm[i]->lastupdate=-1;
			}
		// update changed fogmaps
		if (fm[i]->lastupdate)
			{
			memset(fm[i]->bmp,0,fm[i]->bytesxy);
			fm[i]->lastupdate=-1;
			}
		}
	}

	bsp_object *o=active_obj0,*op=0;
	cur_step_base=cur_step+1;
	cur_dt=dt;

	// loop all active objects
	while(o)
		{
		stepobj=o;

		// if object life is negative, destroy it
		if (o->life<0)
			{
			if (last_active_obj==o)
				last_active_obj=op;
			bsp_object *n=(bsp_object *)o->next_obj;
			delete o;
			if (op==0)
				active_obj0=n;
			else op->next_obj=n;
			o=n;
			continue;
			}
		else
			{
			// step object and reposition in bsp if needed
			cur_step++;
			if (o->step(dt))
				if (o->node)
					{
					o->remove_from_bsp();
					o->add_to_bsp();
					}
			}
		op=o;
		o=(bsp_object *)o->next_obj;
		}
	stepobj=0;

	// if a texture cache is available and not in server mode
	if (tc && directx->mpmode!=FLYMP_SERVER)
	{
	for( i=0;i<nlm;i++ )
		{
		// update changed lightmap
		if (lm[i]->lastupdate)
			{
			if (lm[i]->lastupdate==-1)
				lm[i]->lastupdate=0;
			tc->update_sub_picture(
				lm[i]->pic+lmbase,lm[i]->offsetx,lm[i]->offsety,
				lm[i]->sizex,lm[i]->sizey,3,lm[i]->bmp);
			}
		// update changed fogmap
		if (fm[i]->lastupdate)
			{
			if (fm[i]->lastupdate==-1)
				fm[i]->lastupdate=0;
			tc->update_sub_picture(
				fm[i]->pic+fmbase,fm[i]->offsetx,fm[i]->offsety,
				fm[i]->sizex,fm[i]->sizey,4,fm[i]->bmp);
			}
		}
	}

	// step all running plugins
	dll.send_message(FLYM_UPDATESCENE,dt,0);

	// if in multiplayer, check multiplayer messages
	if (directx->mpmode!=FLYMP_NOMP)
		check_multiplayer();

	// if in client multiplayer mode
	if (directx->mpmode==FLYMP_CLIENT)
		{
		// update client objects to server at slower intervals
		static int last_mp_update=0;
		if (cur_time-last_mp_update>mpdelay)
			{
			last_mp_update=flyengine->cur_time;
			dll.send_message(FLYM_MPUPDATE,0,0);
			}
		}

	// step console
	if (con.mode)
		con.step(dt);
}

void flyEngine::apply_bsp(bsp_node *n,vector& p,float rad,void *data,void (*func)(void *data,bsp_object *e))
{
	if (n->leaf!=-1)
		{
		if (n->elem)
			{
			bsp_object *e=n->elem;
			rad*=rad;
			vector v;
			if (e->type==TYPE_STATIC_MESH)
				{
				func(data,e);
				e=e->next_elem;
				}
			while(e)
				{
				v.x=e->pos.x-p.x;
				v.y=e->pos.y-p.y;
				v.z=e->pos.z-p.z;
				if (v.x*v.x+v.y*v.y+v.z*v.z<rad)
					func(data,e);
				e=e->next_elem;
				}
			}
		return;
		}

	float d=n->distance(p);

	if (fabs(d)<rad)
		{
		if (n->child[0])
			apply_bsp(n->child[0],p,rad,data,func);
		if (n->child[1])
			apply_bsp(n->child[1],p,rad,data,func);
		}
	else 
		if (d>0)
			{
			if (n->child[0])
				apply_bsp(n->child[0],p,rad,data,func);
			}
		else 
			if (n->child[1])
				apply_bsp(n->child[1],p,rad,data,func);
}

void flyEngine::apply_bsp(bsp_node *n,vector *p,int np,void *data,void (*func)(void *data,bsp_object *e))
{
	if (n->leaf!=-1)
		{
		bsp_object *e=n->elem;
		while(e)
			{
			func(data,e);
			e=e->next_elem;
			}
		return;
		}

	float x1,x2;
	int i;

	x1=n->distance(p[0]);
	for( i=1;i<np;i++ )
		{
			x2=n->distance(p[i]);
			if (x1*x2<=0)
				break;
		}
	if (i==5)
		if (x1>0)
		{
			if (n->child[0])
				apply_bsp(n->child[0],p,np,data,func);
		}
		else 
		{
			if (n->child[1])
				apply_bsp(n->child[1],p,np,data,func);
		}
	else 
	{
		if (n->child[0])
			apply_bsp(n->child[0],p,np,data,func);
		if (n->child[1])
			apply_bsp(n->child[1],p,np,data,func);
	}
}

void flyEngine::send_bsp_message(bsp_node *n,vector& p,float rad,int msg,int param,void *data)
{
	static float d;

	if (n->leaf!=-1)
		{
		bsp_object *e=n->elem;
		while(e)
			{
			e->message(p,rad,msg,param,data);
			e=e->next_elem;
			}
		return;
		}

	d=n->distance(p);

	if (fabs(d)<rad)
		{
		if (n->child[0])
			send_bsp_message(n->child[0],p,rad,msg,param,data);
		if (n->child[1])
			send_bsp_message(n->child[1],p,rad,msg,param,data);
		}
	else 
		if (d>0)
			if (n->child[0])
				send_bsp_message(n->child[0],p,rad,msg,param,data);
			else ;
		else
			if (n->child[1])
				send_bsp_message(n->child[1],p,rad,msg,param,data);
}

int flyEngine::collision_test(bsp_node *n,vector& p1,vector& p2,int elemtype,float rad)
{
	if (n->leaf!=-1)
		{
		bsp_object *e=n->elem;
		while(e)
			{
			if	(e!=excludecollision && 
				(elemtype==0 || e->type==elemtype))
				if (e->ray_intersect_test(p1,p2-p1,rad))
					return 1;
			e=e->next_elem;
			}
		return 0;
		}

	float d1=vec_dot(n->normal,p1)+n->d0, 
		d2=vec_dot(n->normal,p2)+n->d0;

	if(d1<SMALL && d2<SMALL)
		if (n->child[1])
			return collision_test(n->child[1],p1,p2,elemtype,rad);
		else return 0;
	else if(d1>SMALL && d2>SMALL)
		if (n->child[0])
			return collision_test(n->child[0],p1,p2,elemtype,rad);
		else return 0;
	else 
		{
		if (n->child[0])
			if (collision_test(n->child[0],p1,p2,elemtype,rad))
				return 1;
		if (n->child[1])
			if (collision_test(n->child[1],p1,p2,elemtype,rad))
				return 1;

		return 0;
		}
}

void flyEngine::find_leaf(bsp_node *n)
{
	if (n->child[0]==0 && n->child[1]==0)
		{
		if (n->leaf!=-1)
			if (leaf)
				leaf[n->leaf]=n;
			else nleaf++;
		return;
		}
	n->leaf=-1;
	if (n->child[0])
		find_leaf(n->child[0]);
	if (n->child[1])
		find_leaf(n->child[1]);
}

void flyEngine::alloc_pvs(char value)
{
	if (pvs)
		delete pvs;
	pvs=0;
	pvssize=0;
	pvsrowsize=0;
	if (leaf)
		delete leaf;
	leaf=0;
	nleaf=0;

	if (bsp)
	{
		find_leaf(bsp);
		if (nleaf==0)
			return;
		leaf=new bsp_node *[nleaf];
		memset(leaf,0,nleaf*sizeof(bsp_node *));
		find_leaf(bsp);
	}

	if (nleaf)
		{
		pvsrowsize=nleaf/8+1;
		if (pvsrowsize&3)
			pvsrowsize+=4-(pvsrowsize&3);
		pvssize=pvsrowsize*nleaf;
		pvs=new char[pvssize];
		memset(pvs,value,pvssize);
		}
}

bsp_node *flyEngine::find_node(bsp_node *n,vector& v,float mindist)
{
	float dist;
	while(n->child[0]!=0 || n->child[1]!=0)
	{
	dist=n->distance(v);
	if (fabs(dist)<mindist)
		return 0;
	if (dist>=0)
		if (n->child[0])
			n=n->child[0];
		else return 0;
	else if (n->child[1])
			n=n->child[1];
		else return 0;
	}
	return n;
}

bsp_node *flyEngine::get_random_point(vector& v,float mindist)
{
	if (bsp==0)
	{
		v.null();
		return 0;
	}

	vector diag=bbox2-bbox1;
	bsp_node *n;
	int maxpoints=100;

	new_point:
		if (--maxpoints==0)
		{
			v.null();
			return 0;
		}
		v.x=bbox1.x+FABSRAND*diag.x;
		v.y=bbox1.y+FABSRAND*diag.y;
		v.z=bbox1.z+FABSRAND*diag.z;
		n=find_node(bsp, v, mindist);
		if (n==0 || n->leaf==-1)
			goto new_point;
		return n;
}

void flyEngine::set_status_msg(char *fmt, ...)
{
    char ach[128];
    va_list va;
    va_start( va, fmt );
    wvsprintf( ach, fmt, va );
    va_end( va );

	strcpy(status_msg,ach);
	status_msg_time=cur_time;

	con.add_string(ach);
}

void flyEngine::activate(bsp_object *d,int flag)
{
	if (bsp==0 || d==0) 
		return;
	
	d->next_obj=0;
	if (last_active_obj)
		last_active_obj->next_obj=d;
	else
		active_obj0=d;
	last_active_obj=d;

	d->node=0;
	if (flag)
		d->add_to_bsp();
}

int flyEngine::open_fly_file(char *file)
{
	char str[256];
	
	close_fly_file();

	strcpy(str,file);
	strlwr(str);

	strcpy(flyfile,str);

	strcpy(flydatapath,flysdkpath);
	strcat(flydatapath,"data\\");

	strcpy(flyfilename,flydatapath);
	strcat(flyfilename,flyfile);

	char *c=strrchr(str,'\\');
	if (c==0) c=strrchr(str,'/');
	if (c) { *(c+1)=0; strcat(flydatapath,str); }

	if (load_data()==0)
	{
		reset();
		return 0;
	}

	init_texture_cache();

	return 1;
}

int flyEngine::save_fly_file(char *file)
{
	strlwr(file);
	strcpy(flyfile,file);
	strcpy(flydatapath,flysdkpath);
	strcat(flydatapath,"data\\");
	strcpy(flyfilename,flydatapath);
	strcat(flyfilename,flyfile);
	char *c=strrchr(file,'\\');
	if (c==0) c=strrchr(file,'/');
	if (c) { *(c+1)=0; strcat(flydatapath,file); }
	FILE *fp=fopen(flyfilename,"wt");
	if (fp==0) 
	{
		flydatapath[0]=0;
		flyfilename[0]=0;
		flyfile[0]=0;
		return 0;
	}
	
	char *name;
	int i,j,n,type;
	bsp_object *o;
	param_desc pd;

	fprintf(fp,"[classes]\n");
	for( i=0;i<dll.ndll;i++ )
		fprintf(fp,"dll%i=%s\n",i,dll.dll[i]->dll_filename);

	for( i=0;i<dll.ncd;i++ )
		{
		name=dll.cd[i]->get_name();
		type=dll.cd[i]->get_type();
		o=stock_obj0;
		n=0;
		while(o)
			{
			if (o->type==type)
				sprintf(o->name,"%s%i",name,n++);
			o=(bsp_object *)o->next_obj;
			}
		}
	o=active_obj0;
	while(o)
		{
		if (o->source)
			strcpy(o->name,o->source->name);
		o=(bsp_object *)o->next_obj;
		}

	for( i=0;i<dll.ncd;i++ )
		{
		name=dll.cd[i]->get_name();
		type=dll.cd[i]->get_type();
		o=stock_obj0;
		n=0;
		while(o)
			{
			if (o->type==type)
				{
				fprintf(fp,"\n");
				fprintf(fp,"[%s]\nlongname=%s\n",o->name,o->long_name);
				n=o->get_param_desc(0,0);
				for( j=0;j<n;j++ )
					{
					o->get_param_desc(j,&pd);
					fprintf(fp,"%s=%s\n",pd.name,pd.get_string());
					}
				}
			o=(bsp_object *)o->next_obj;
			}
		}

	fprintf(fp,"\n");
	fprintf(fp,"[fly]\n");
	n=get_global_param_desc(0,0);
	for( i=0;i<n;i++ )
		{
		get_global_param_desc(i,&pd);
		if (pd.type!=' ')
			fprintf(fp,"%s=%s\n",pd.name,pd.get_string());
		}

	fclose(fp);
	return 1;
}

void flyEngine::close_fly_file()
{
	dll.send_message(FLYM_CLOSESCENE,0,0);
	close_texture_cache();
	reset();
}

void flyEngine::init_texture_cache()
{
	if (rend==0)
		return;

	if (tc) delete tc;
	tc=new textcacheGL();
	tc->init(npiclib,piclib);
	
	int i;
	lmbase=tc->npic;
	for( i=0;i<nlmpic;i++ )
		tc->add_picture(lmpic[i]->sizex,lmpic[i]->sizey,3,lmpic[i]->bmp);
	fmbase=tc->npic;
	for( i=0;i<nlmpic;i++ )
		tc->add_picture(fmpic[i]->sizex,fmpic[i]->sizey,4,fmpic[i]->bmp);
}

void flyEngine::close_texture_cache()
{
	if (tc) delete tc;
	tc=0;
}

void flyEngine::set_camera(bsp_object *d)
{
	cam=d;
	float disty=viewmaxdist*(float)tan(camangle*0.5f*PiOver180);
	float distx=disty*aspect;
	if (cam)
		{
		frustrum[0]=cam->pos;
		
		frustrum[1].x = cam->pos.x - viewmaxdist*cam->Z.x +
					distx*cam->X.x + disty*cam->Y.x;
		frustrum[1].y = cam->pos.y - viewmaxdist*cam->Z.y +
					distx*cam->X.y + disty*cam->Y.y;
		frustrum[1].z = cam->pos.z - viewmaxdist*cam->Z.z +
					distx*cam->X.z + disty*cam->Y.z;

		frustrum[2].x = cam->pos.x - viewmaxdist*cam->Z.x +
					distx*cam->X.x - disty*cam->Y.x;
		frustrum[2].y = cam->pos.y - viewmaxdist*cam->Z.y +
					distx*cam->X.y - disty*cam->Y.y;
		frustrum[2].z = cam->pos.z - viewmaxdist*cam->Z.z +
					distx*cam->X.z - disty*cam->Y.z;

		frustrum[3].x = cam->pos.x - viewmaxdist*cam->Z.x -
					distx*cam->X.x - disty*cam->Y.x;
		frustrum[3].y = cam->pos.y - viewmaxdist*cam->Z.y -
					distx*cam->X.y - disty*cam->Y.y;
		frustrum[3].z = cam->pos.z - viewmaxdist*cam->Z.z -
					distx*cam->X.z - disty*cam->Y.z;

		frustrum[4].x = cam->pos.x - viewmaxdist*cam->Z.x -
					distx*cam->X.x + disty*cam->Y.x;
		frustrum[4].y = cam->pos.y - viewmaxdist*cam->Z.y -
					distx*cam->X.y + disty*cam->Y.y;
		frustrum[4].z = cam->pos.z - viewmaxdist*cam->Z.z -
					distx*cam->X.z + disty*cam->Y.z;

		glMatrixMode( GL_PROJECTION );
		glLoadIdentity();
		gluPerspective( flyengine->camangle, flyengine->aspect, flyengine->viewmindist,flyengine->viewmaxdist*1.5f);
		glMatrixMode( GL_MODELVIEW );
		glLoadIdentity();
		glMultMatrixf((float *)&cam->mat_t);
		glTranslatef(-cam->pos.x,-cam->pos.y,-cam->pos.z);
		}
}

int flyEngine::get_picture(char *file)
{
	if (file[0]==0)
		return -1;

	int j;
	for( j=0;j<npiclib;j++ )
		if (!stricmp(piclib[j]->name,file))
			break;

	if (j==npiclib)
		{
		picture *p=new picture;
		char name[256];
		strcpy(name,flydatapath);
		strcat(name,"maps\\");
		strcat(name,file);
		if (p->LoadPIC(name))
			{
			piclib[npiclib]=p;
			strcpy(piclib[npiclib]->name,file);
			return npiclib++;
			}
		else
			{
			delete p;
			return -1;
			}
		}

	return j;
}

int flyEngine::load_pictures(char *namef)
{
	fly_pak fp;
	int i,n;
	char name[256],str[256];

	if(!fp.open(namef))
		return 0;

	n=fp.get_int();
	fp.get_string(str);
	for(i=0;i<n;i++)
		{
		fp.get_string(str);
		piclib[i]=new picture;
		strcpy(name,flydatapath);
		strcat(name,"maps\\");
		strcat(name,str);
		piclib[npiclib+i]->LoadPIC(name);
		strcpy(piclib[npiclib+i]->name,str);
		}
	npiclib+=n;

	return 1;
}

int flyEngine::load_bsp(char *file) 
{
	unsigned char uc;
	int w[3];
	int i,nv;

	fly_pak fp;

	if (!fp.open(file))
		return 0;

	fp.read(&nv,sizeof(int));
	nvert=abs(nv);
	
	vert=new vector[nvert];

	for( i=0;i<nvert;i++ )
		fp.read(&vert[i],3*sizeof(float));
	if (nv<0)
	{
	vertcolor=new vector[nvert];
	for( i=0;i<nvert;i++ )
		{
		fp.read(&uc,1);
		vertcolor[i].x=uc/255.0f;
		fp.read(&uc,1);
		vertcolor[i].y=uc/255.0f;
		fp.read(&uc,1);
		vertcolor[i].z=uc/255.0f;
		fp.read(&uc,1);
		vertcolor[i].w=1.0f;
		}
	}

	fp.read(&nfaces,sizeof(int));
	faces=new face[nfaces];
	facedraw=new int[nfaces];
	facedrawtransp=new int[nfaces];
	for( i=0;i<nfaces;i++ )
		{
		fp.read(w,sizeof(int)*3);
		faces[i].vert[0]=&vert[w[0]];
		faces[i].vert[1]=&vert[w[1]];
		faces[i].vert[2]=&vert[w[2]];
		fp.read(&faces[i].texpic,sizeof(int));
		fp.read(&faces[i].emmradius,sizeof(float));
		fp.read(faces[i].uv,sizeof(float)*6);
		fp.read(&uc,1);
		faces[i].color.x=uc/255.0f;
		fp.read(&uc,1);
		faces[i].color.y=uc/255.0f;
		fp.read(&uc,1);
		faces[i].color.z=uc/255.0f;
		fp.read(&uc,1);
		faces[i].color.w=uc/255.0f;
		faces[i].indx=i;
		}

	load_bsp(&bsp,&fp);
	fp.close();

	compute_normals();

	return 1;
}

void flyEngine::load_bsp(bsp_node **n,fly_pak *fp)
{
	char c;
	int f,i;
	int w;

	fp->read(&c,1);
	if (c==0)
		return;

	*n=new bsp_node;

	fp->read(&(*n)->leaf,sizeof(int));

	fp->read(&(*n)->normal,3*sizeof(float));
	fp->read(&(*n)->d0,sizeof(float));

	fp->read(&f,sizeof(int));
	if (f)
		{
		static_mesh *so=new static_mesh;
		so->objmesh->pivotpos.null();
		so->objmesh->nf=f;
		so->objmesh->faces=new face *[so->objmesh->nf];
		for( i=0;i<so->objmesh->nf;i++ )
			{
			fp->read(&w,sizeof(int));
			so->objmesh->faces[i]=&faces[w];
			so->objmesh->faces[i]->lastdraw=0;
			}
		so->objmesh->compute_normals(MESH_FACENORM|MESH_VERTNORM|MESH_BBOX);
		so->next_elem=(*n)->elem;
		(*n)->elem=so;
		(*n)->last_elem=&so->next_elem;
		}

	load_bsp(&(*n)->child[0],fp);
	load_bsp(&(*n)->child[1],fp);
}

void flyEngine::save_bsp(bsp_node *n,FILE *fp)
{
	char c;
	int i;
	int w;

	if (n==0)
		{
		c=0;
		fwrite(&c,1,1,fp);
		return;
		}

	c=1;
	fwrite(&c,1,1,fp);

	fwrite(&n->leaf,1,sizeof(int),fp);

	fwrite(&n->normal, 3, sizeof(float), fp);
	fwrite(&n->d0, 1, sizeof(float), fp);

	bsp_object *e=n->elem;
	while(e)
		{
		if (e->type==TYPE_STATIC_MESH)
			break;
		e=e->next_elem;
		}
	static_mesh *so=(static_mesh *)e;
	if (so)
		{
		fwrite(&so->objmesh->nf,1,sizeof(int),fp);
		for( i=0;i<so->objmesh->nf;i++ )
			{
			w=so->objmesh->faces[i]->indx;
			fwrite(&w,1,sizeof(int),fp);
			}
		}
	else 
		{
		i=0;
		fwrite(&i,1,sizeof(int),fp);
		}

	save_bsp(n->child[0],fp);
	save_bsp(n->child[1],fp);
}

int flyEngine::save_bsp(char *file)
{
	if (bsp==0)
		return 0;

	FILE *fp;
	unsigned char uc;
	int w[3];
	int i,nv;

	fp=fopen(file,"wb");
	if (!fp)
		return 0;

	if (vertcolor)
		nv=-nvert;
	else nv=nvert;

	fwrite(&nv,1,sizeof(int),fp);

	for( i=0;i<nvert;i++ )
		fwrite(&vert[i],3,sizeof(float),fp);
	if (nv<0)
	for( i=0;i<nvert;i++ )
	{
		uc=(unsigned char)(vertcolor[i].x*255);
		fwrite(&uc,1,1,fp);
		uc=(unsigned char)(vertcolor[i].y*255);
		fwrite(&uc,1,1,fp);
		uc=(unsigned char)(vertcolor[i].z*255);
		fwrite(&uc,1,1,fp);
		uc=255;
		fwrite(&uc,1,1,fp);
	}

	fwrite(&nfaces,1,sizeof(int),fp);
	for( i=0;i<nfaces;i++ )
		{
		faces[i].indx=i;

		w[0]=(int)(faces[i].vert[0]-vert);
		w[1]=(int)(faces[i].vert[1]-vert);
		w[2]=(int)(faces[i].vert[2]-vert);
		fwrite(w,sizeof(int),3,fp);
		fwrite(&faces[i].texpic,sizeof(int),1,fp);
		fwrite(&faces[i].emmradius,sizeof(float),1,fp);
		
		fwrite(faces[i].uv,sizeof(float),6,fp);

		uc=(unsigned char)(faces[i].color.x*255);
		fwrite(&uc,1,1,fp);
		uc=(unsigned char)(faces[i].color.y*255);
		fwrite(&uc,1,1,fp);
		uc=(unsigned char)(faces[i].color.z*255);
		fwrite(&uc,1,1,fp);
		uc=(unsigned char)(faces[i].color.w*255);
		fwrite(&uc,1,1,fp);
		}

	save_bsp(bsp,fp);

	fclose(fp);

	return 1;
}

int flyEngine::load_lightmaps(char *file)
{
	if (nfaces==0)
		return 0;
	int i,x,y,sx,sy,f,p;
	fly_pak fp;
	
	if (!fp.open(file)) return 0;

	fp.read(&i,sizeof(int));
	if (i!=nfaces) 
	{ fp.close(); return 0;};
	
	for( i=0;i<nfaces;i++ )
		{
		fp.read(&faces[i].lm,sizeof(int));
		fp.read(&faces[i].lmuv,sizeof(float)*6);
		}

	fp.read(&nlmpic,sizeof(int));
	for( i=0;i<nlmpic;i++ )
		{
		fp.read(&sx,sizeof(int));
		fp.read(&sy,sizeof(int));
		lmpic[i]=new light_map_pic(sx,sy);
		fp.read(lmpic[i]->bmp,lmpic[i]->bytesxy);
		}

	fp.read(&nlm,sizeof(int));
	for( i=0;i<nlm;i++ )
	{
		fp.read(&f,sizeof(int));
		fp.read(&p,sizeof(int));
		fp.read(&x,sizeof(int));
		fp.read(&y,sizeof(int));
		fp.read(&sx,sizeof(int));
		fp.read(&sy,sizeof(int));
		lm[i]=new light_map(f,p,x,y,sx,sy,3);
		lm[i]->load(lmpic[p]);
	}

	fp.close();

	for( i=0;i<nlmpic;i++ )
	{
		fmpic[i]=new light_map_pic(lmpic[i]->sizex,lmpic[i]->sizey,4);
		memset(fmpic[i]->bmp,0,fmpic[i]->bytesxy);
	}
	for( i=0;i<nlm;i++ )
	{
		fm[i]=new light_map(lm[i]->facenum,lm[i]->pic,lm[i]->offsetx,lm[i]->offsety,lm[i]->sizex,lm[i]->sizey,4);
		memset(fm[i]->bmp,0,fm[i]->bytesxy);
		if (lm[i]->facenum!=-1)
			lm[i]->set_base(&faces[lm[i]->facenum],lmpic[lm[i]->pic]);
		if (fm[i]->facenum!=-1)
			fm[i]->set_base(&faces[fm[i]->facenum],fmpic[fm[i]->pic]);
	}

	return 1;
}
int flyEngine::save_lightmaps(char *file)
{
	if (nfaces==0)
		return 0;
	FILE *fp;
	int i;
	
	fp=fopen(file,"wb");
	if (fp==0) return 0;

	fwrite(&nfaces,1,sizeof(int),fp);
	
	for (i=0;i<nfaces;i++ )
		{
		fwrite(&faces[i].lm,sizeof(int),1,fp);
		fwrite(&faces[i].lmuv,sizeof(int),6,fp);
		}

	fwrite(&nlmpic,1,sizeof(int),fp);
	for( i=0;i<nlmpic;i++ )
	{
		fwrite(&lmpic[i]->sizex,sizeof(int),1,fp);
		fwrite(&lmpic[i]->sizey,sizeof(int),1,fp);
		fwrite(lmpic[i]->bmp,lmpic[i]->bytesxy,1,fp);
	}

	fwrite(&nlm,1,sizeof(int),fp);
	for( i=0;i<nlm;i++ )
		{
		fwrite(&lm[i]->facenum,sizeof(int),1,fp);
		fwrite(&lm[i]->pic,sizeof(int),1,fp);
		fwrite(&lm[i]->offsetx,sizeof(int),2,fp);
		fwrite(&lm[i]->sizex,sizeof(int),2,fp);
		}

	fclose(fp);
	return 1;
}

int flyEngine::load_pvs(char *file)
{
	int i;
	fly_pak fp;

	alloc_pvs((char)255);
	if (pvssize==0) return 0;

	if (!fp.open(file)) return 0;

	fp.read(&i,sizeof(int));
	if (i==nleaf)
		fp.read(pvs,pvssize);
	
	fp.close();

	for( i=0;i<nleaf;i++ )
		if (leaf[i]->leaf!=i)
			break;

	return 1;
}

int flyEngine::save_pvs(char *file)
{
	FILE *fp;
	if (pvssize==0) return 0;
	fp=fopen(file,"wb");
	if (fp==0) return 0;
	fwrite(&nleaf,1,sizeof(int),fp);
	fwrite(pvs,pvssize,1,fp);
	fclose(fp);
	return 1;
}

void WriteProfileInt(char *sec,char *key,int value)
{
	char str[256];
	sprintf(str,"%i",value);
	WriteProfileString(sec,key,str);
}

int GetProfileInt(char *sec,char *key,int value)
{
	char str[256];
	GetProfileString(sec,key,"",str,128);
	if (str[0]!=0)
		sscanf(str,"%i",&value);
	
	return value;
}

bsp_object *flyEngine::get_active_object(char *name)
{
	bsp_object *o=active_obj0;
	
	while(o)
		{
		if (!stricmp(name,o->name))
			break;
		o=(bsp_object *)o->next_obj;
		}
	
	return o;
}

bsp_object *flyEngine::get_stock_object(char *name)
{
	if (name[0]==0) return 0;
	bsp_object *o=stock_obj0;
	while(o)
		{
		if (!stricmp(name,o->name))
			break;
		o=(bsp_object *)o->next_obj;
		}

	return o;
}

bezier_curve *flyEngine::get_bezier_curve(char *name)
{
	if (name[0]==0) return 0;
	bezier_curve *o=bezier_curve0;
	while(o)
		{
		if (!stricmp(name,o->name))
			break;
		o=(bezier_curve *)o->next_obj;
		}

	if (o==0)
		{
		char tmp[256];
		o=new bezier_curve;
		strcpy(o->name,name);
		strcpy(o->long_name,name);
		strcpy(tmp,flydatapath);
		strcat(tmp,"objects\\");
		strcat(tmp,name);
		if (o->load_bez(tmp)==0)
			{
			delete o;
			return 0;
			}
		o->next_obj=bezier_curve0;
		bezier_curve0=o;
		}

	return o;
}

bezier_patch *flyEngine::get_bezier_patch(char *name)
{
	if (name[0]==0) return 0;
	bezier_patch *o=bezier_patch0;
	while(o)
		{
		if (!stricmp(name,o->name))
			break;
		o=(bezier_patch *)o->next_obj;
		}

	if (o==0)
		{
		char tmp[256];
		o=new bezier_patch;
		strcpy(o->name,name);
		strcpy(o->long_name,name);
		strcpy(tmp,flydatapath);
		strcat(tmp,"objects\\");
		strcat(tmp,name);
		if (o->load_pch(tmp)==0)
			{
			delete o;
			return 0;
			}
		o->next_obj=bezier_patch0;
		bezier_patch0=o;
		}

	return o;
}

mesh *flyEngine::get_model_object(char *name)
{
	if (name[0]==0) return 0;
	mesh *o=model_obj0;
	while(o)
		{
		if (!stricmp(name,o->name))
			break;
		o=(mesh *)o->next_obj;
		}

	if (o==0)
		{
		if (strrchr(name,'.'))
			if (!stricmp(strrchr(name,'.'),".3ds"))
			{
			char tmp[256];
			o=new mesh;
			strcpy(o->name,name);
			strcpy(o->long_name,name);
			strcpy(tmp,flydatapath);
			strcat(tmp,"objects\\");
			strcat(tmp,name);
			if (o->load_3ds(tmp)==0)
				{
				delete o;
				return 0;
				}
			o->next_obj=model_obj0;
			model_obj0=o;
			}
			else
			if (!stricmp(strrchr(name,'.'),".fao"))
			{
			char tmp[256];
			o=new anim_mesh;
			strcpy(o->name,name);
			strcpy(o->long_name,name);
			strcpy(tmp,flydatapath);
			strcat(tmp,"objects\\");
			strcat(tmp,name);
			if (((anim_mesh *)o)->load_fao(tmp)==0)
				{
				delete o;
				return 0;
				}
			o->next_obj=model_obj0;
			model_obj0=o;
			}
		}

	return o;
}

sound *flyEngine::get_sound_object(char *name)
{
	if (name[0]==0) return 0;
	sound *s=sound_obj0;
	while(s)
		{
		if (!stricmp(name,s->name))
			break;
		s=(sound *)s->next_obj;
		}

	if (s==0)
		{
		if (strrchr(name,'.'))
			if (!stricmp(strrchr(name,'.'),".wav"))
			{
			char tmp[256];
			s=new sound;
			strcpy(s->name,name);
			strcpy(s->long_name,name);
			strcpy(tmp,flydatapath);
			strcat(tmp,"sounds\\");
			strcat(tmp,name);
			if (s->load_wav(tmp)==0)
				{
				delete s;
				return 0;
				}
			s->next_obj=sound_obj0;
			sound_obj0=s;
			}
		}

	return s;
}

bsp_object *flyEngine::get_next_stock_object(bsp_object *o,int type)
{
	if (o==0) 
		o=stock_obj0;
	else o=(bsp_object *)o->next_obj;

	while(o)
		{
		if (type==0 || type==o->type)
			break;
		o=(bsp_object *)o->next_obj;
		}
	
	return o;
}

bsp_object *flyEngine::get_next_active_object(bsp_object *o,int type)
{
	if (o==0) 
		o=active_obj0;
	else o=(bsp_object *)o->next_obj;
	
	while(o)
		{
		if (type==0 || type==o->type)
			break;
		o=(bsp_object *)o->next_obj;
		}
	
	return o;
}

void flyEngine::compute_node_light()
{
	int i,x,y;
	unsigned char *uc;
	vector point;
	bsp_node *node;
	light_map_pic *lmp;

	if (nlm==0)
	{
	for( i=0;i<nleaf;i++ )
		leaf[i]->color.vec(1,1,1,1);
	return;
	}

	for( i=0;i<nleaf;i++ )
		{
		leaf[i]->color.null();
		leaf[i]->leaf=0;
		}

	for( i=0;i<nlm;i++ )
	{
	lmp=lmpic[lm[i]->pic];
	for( y=0;y<lm[i]->sizey;y++ )
		{
		uc=&lmp->bmp[(y+lm[i]->offsety)*lmp->bytesx+lm[i]->offsetx];
		for( x=0;x<lm[i]->sizex;x++ )
			{
			lm[i]->map_point((float)x/lm[i]->sizex+1.0f/(lm[i]->sizex*2),(float)y/lm[i]->sizey+1.0f/(lm[i]->sizey*2),point);
			node=find_node(bsp,point,0);
			if (node)
				{
				node->color.x+=*(uc++);
				node->color.y+=*(uc++);
				node->color.z+=*(uc++);
				node->leaf++;
				}
			else uc+=3;
			}
		}
	}

	for( i=0;i<nleaf;i++ )
		{
		if (leaf[i]->leaf)
			leaf[i]->color/=leaf[i]->leaf*255.0f;
		leaf[i]->color.w=1.0f;
		leaf[i]->leaf=i;
		}
}

void flyEngine::load_level()
{
	char str[256];

	strcpy(str,flydatapath);
	strcat(str,bspfile);
	strcat(str,".tex");
	load_pictures(str);

	strcpy(str,flydatapath);
	strcat(str,bspfile);
	strcat(str,".bsp");
	load_bsp(str);

	strcpy(str,flydatapath);
	strcat(str,bspfile);
	strcat(str,".pvs");
	load_pvs(str);

	strcpy(str,flydatapath);
	strcat(str,bspfile);
	strcat(str,".lmp");
	load_lightmaps(str);
}

int flyEngine::load_data()
{
	char ret[256],str[256];
	int i,j;
	param_desc pd;

	fly_pak fly_file;
	if (!fly_file.open(flyfilename))
		return 0;

	fly_file.get_profile_string("fly", "bspfile", bspfile);

	load_level();

	j=get_global_param_desc(0,0);
	for( i=0;i<j;i++ )
	{
	get_global_param_desc(i,&pd);
	fly_file.get_profile_string("fly",pd.name,ret);
	pd.set_string(ret);
	}

	if (fontspic!=-1)
		{
		strcpy(str,flydatapath);
		strcat(str,"maps\\");
		strcat(str,piclib[fontspic]->name);
		if (strrchr(str,'.'))
			*strrchr(str,'.')=0;
		strcat(str,".txt");
		fly_pak fp;
		if (fp.open(str))
			for( int i=0;i<64;i++ )
				fonts_width[i]=fp.get_int();
		else 
			for( int i=0;i<64;i++ )
				fonts_width[i]=FONTS_SIZE/2;
		}

	i=0;
	while(1)
		{
		sprintf(str,"dll%i",i++);
		fly_file.get_profile_string("classes",str,ret);
		if (ret[0]==0) break;
		dll.add_dll(ret);
		}

	dll.load_all_classes(&fly_file);
	bsp_object *o=active_obj0;
	while(o)
		{
		o->load_params(&fly_file,o->name);
		o=(bsp_object *)o->next_obj;
		}
	o=stock_obj0;
	while(o)
		{
		o->load_params(&fly_file,o->name);
		o=(bsp_object *)o->next_obj;
		}

	fly_file.get_profile_string("fly","camera",ret);
	cam=get_active_object(ret);
	fly_file.get_profile_string("fly","player",ret);
	player=get_active_object(ret);
	
	if (directx)
		directx->players[0].data=player;

	bsp_object *s=0,*n;
	o=stock_obj0;
	while(o)
		{
		n=(bsp_object *)o->next_obj;
		o->next_obj=s;
		s=o;
		o=n;
		}
		
	stock_obj0=s;

	o=stock_obj0;
	while(o)
		{
		cur_step++;
		o->init();
		o=(bsp_object *)o->next_obj;
		}
	o=active_obj0;
	while(o)
		{
		cur_step++;
		o->init();
		o->add_to_bsp();
		o=(bsp_object *)o->next_obj;
		}

	compute_node_light();

	dll.send_message(FLYM_INITSCENE,0,0);

	return 1;
}

int flyEngine::add_lightmap(int sx,int sy)
{
	int x=0,y=0,i,j;
	int sizes[]={ 1,2,4,8,16,32,64,128,256 };
	for( i=0,j=256;i<9;i++ )
		if (abs(sizes[i]-sx)<j)
			{
			j=abs(sizes[i]-sx);
			x=i;
			}
	for( i=0,j=256;i<9;i++ )
		if (abs(sizes[i]-sy)<j)
			{
			j=abs(sizes[i]-sy);
			y=i;
			}

	lmpic[nlmpic]=new light_map_pic(sizes[x],sizes[y],3);
	fmpic[nlmpic]=new light_map_pic(sizes[x],sizes[y],4);
	lm[nlm]=new light_map(-1,nlmpic,0,0,sizes[x],sizes[y],3);
	fm[nlm]=new light_map(-1,nlmpic,0,0,sizes[x],sizes[y],4);

	nlmpic++;
	return nlm++;
}

int flyEngine::get_obj_param(char *objname,char *param,char *value)
{
	value[0]=0;
	bsp_object *obj;
	obj=active_obj0;
	while(obj)
		{
		if (!stricmp(objname,obj->long_name))
			break;
		obj=(bsp_object *)obj->next_obj;
		}
	if (obj==0)
		{
		obj=stock_obj0;
		while(obj)
			{
			if (!stricmp(objname,obj->long_name))
				break;
			obj=(bsp_object *)obj->next_obj;
			}
		}
	if (obj==0) return 1;
	int i,n;
	param_desc pd;
	n=obj->get_param_desc(0,0);
	for( i=0;i<n;i++ )
		{
		obj->get_param_desc(i,&pd);
		if (!stricmp(pd.name,param))
			break;
		}
	if (i==n)
		return 2;

	strcpy(value,pd.get_string());

	return 0;
}

int flyEngine::set_global_param(char *name,char *value)
{
	param_desc pd;
	int i,n;

	n=get_global_param_desc(0,0);
	for( i=0;i<n;i++ )
		{
		get_global_param_desc(i,&pd);
		if (!stricmp(name,pd.name))
			break;
		}
	if (i==n)
		return 0;
	
	pd.set_string(value);
	if (pd.type=='p' || pd.type=='3' || pd.type=='m')
	{
		close_texture_cache();
		init_texture_cache();
	}

	bsp_object *obj;
	obj=stock_obj0;
	while(obj)
	{
		obj->message(vector(0,0,0),0,FLYOBJM_CHANGEPARAM,-i-1,&pd);
		obj=(bsp_object *)obj->next_obj;
	}
	obj=active_obj0;
	while(obj)
	{
		obj->message(vector(0,0,0),0,FLYOBJM_CHANGEPARAM,-i-1,&pd);
		obj=(bsp_object *)obj->next_obj;
	}

	return 1;
}

int flyEngine::set_obj_param(char *objname,char *param,char *value)
{
	bsp_object *obj=stock_obj0;
	int ret=0;
	while(obj)
		{
		if (!stricmp(objname,obj->long_name))
			break;
		obj=(bsp_object *)obj->next_obj;
		}
	if (obj==0) return 1;

	param_desc pd;
	int i,j,n;
	n=obj->get_param_desc(0,0);
	for( i=0;i<n;i++ )
		{
		obj->get_param_desc(i,&pd);
		if (!stricmp(pd.name,param))
			break;
		}
	if (i==n)
		return 2;

	j=4;
	if (pd.type=='d' || pd.type<-255)
	{
		bsp_object *o=active_obj0;
		while(o)
		{
			if (!stricmp(o->long_name,value))
				break;
			o=(bsp_object *)o->next_obj;
		}
		*((bsp_object **)pd.data)=o;
	}
	else
	if (pd.type=='o' || pd.type>255)
	{
		bsp_object *o=stock_obj0;
		while(o)
		{
			if (!stricmp(o->long_name,value))
				break;
			o=(bsp_object *)o->next_obj;
		}
		*((bsp_object **)pd.data)=o;
	}
	else pd.set_string(value);

	switch(pd.type)
	{
	case 'i':
	case 'f':
	case 'a':
	case 'w':
	case 'd':
	case 'o':
	case 'z':
	case 'h':
		break;
	case 'v':
	case 'c':
		j=12;
		break;
	case 's':
		j=strlen(value)+1;
		break;
	case 'p':
	case '3':
	case 'm':
		close_texture_cache();
		init_texture_cache();
		break;
	default:
		return 3;
	}

	obj->message(vector(0,0,0),0,FLYOBJM_CHANGEPARAM,0,0);
	char *data=(char *)pd.data;
	obj=active_obj0;
	while(obj)
		{
		if (!stricmp(objname,obj->long_name))
			{
			obj->get_param_desc(i,&pd);
			memcpy(pd.data,data,j);
			obj->message(vector(0,0,0),0,FLYOBJM_CHANGEPARAM,i,&pd);
			}
		obj=(bsp_object *)obj->next_obj;
		}
	
	return ret;
}

int flyEngine::get_global_param_desc(int i,param_desc *pd)
{
	if (pd!=0)
	switch(i)
	{
		case 0:
			pd->type='c';
			pd->data=&background;
			strcpy(pd->name,"background");
			break;
		case 1:
			pd->type='b';
			pd->data=&bspfile;
			strcpy(pd->name,"bspfile");
			break;
		case 2:
			pd->type='f';
			pd->data=&viewmindist;
			strcpy(pd->name,"viewmindist");
			break;
		case 3:
			pd->type='f';
			pd->data=&viewmaxdist;
			strcpy(pd->name,"viewmaxdist");
			break;
		case 4:
			pd->type='f';
			pd->data=&camangle;
			strcpy(pd->name,"camangle");
			break;
		case 5:
			pd->type='d';
			pd->data=&cam;
			strcpy(pd->name,"camera");
			break;
		case 6:
			pd->type='d';
			pd->data=&player;
			strcpy(pd->name,"player");
			break;

		case 7:
			pd->type=' ';
			pd->data=0;
			strcpy(pd->name,"");
			break;

		case 8:
			pd->type='i';
			pd->data=&amblight;
			strcpy(pd->name,"amblight");
			break;
		case 9:
			pd->type='f';
			pd->data=&curveerr;
			strcpy(pd->name,"curveerr");
			break;
		case 10:
			pd->type='f';
			pd->data=&geomdetail;
			strcpy(pd->name,"geomdetail");
			break;
		case 11:
			pd->type='f';
			pd->data=&lmpxsize;
			strcpy(pd->name,"lmpxsize");
			break;
		case 12:
			pd->type='i';
			pd->data=&mapmode;
			strcpy(pd->name,"mapmode");
			break;
		case 13:
			pd->type='i';
			pd->data=&mpdelay;
			strcpy(pd->name,"mpdelay");
			break;
		case 14:
			pd->type='c';
			pd->data=&shadowcolor;
			strcpy(pd->name,"shadowcolor");
			break;
		case 15:
			pd->type='f';
			pd->data=&shadowdepth;
			strcpy(pd->name,"shadowdepth");
			break;

		case 16:
			pd->type=' ';
			pd->data=0;
			strcpy(pd->name,"");
			break;

		case 17:
			pd->type='p';
			pd->data=&consolepic;
			strcpy(pd->name,"consolepic");
			break;
		case 18:
			pd->type='p';
			pd->data=&fontspic;
			strcpy(pd->name,"fontspic");
			break;
		case 19:
			pd->type='p';
			pd->data=&intropic;
			strcpy(pd->name,"intropic");
			break;
		case 20:
			pd->type='p';
			pd->data=&crosshairpic;
			strcpy(pd->name,"crosshairpic");
			break;
		case 21:
			pd->type='i';
			pd->data=&crosshairsize;
			strcpy(pd->name,"crosshairsize");
			break;
		case 22:
			pd->type='p';
			pd->data=&cartoonpicbsp;
			strcpy(pd->name,"cartoonpicbsp");
			break;
		case 23:
			pd->type='p';
			pd->data=&cartoonpic;
			strcpy(pd->name,"cartoonpic");
			break;
		case 24:
			pd->type='c';
			pd->data=&cartooncolor;
			strcpy(pd->name,"cartooncolor");
			break;
		case 25:
			pd->type='f';
			pd->data=&cartoonwidth;
			strcpy(pd->name,"cartoonwidth");
			break;
		case 26:
			pd->type='p';
			pd->data=&detailpic;
			strcpy(pd->name,"detailpic");
			break;
		case 27:
			pd->type='f';
			pd->data=&detailtile;
			strcpy(pd->name,"detailtile");
			break;

		case 28:
			pd->type=' ';
			pd->data=0;
			strcpy(pd->name,"");
			break;

		case 29:
			pd->type='i';
			pd->data=&antialias;
			strcpy(pd->name,"antialias");
			break;
		case 30:
			pd->type='i';
			pd->data=&clearbk;
			strcpy(pd->name,"clearbk");
			break;
		case 31:
			pd->type='i';
			pd->data=&fog;
			strcpy(pd->name,"fog");
			break;
		case 32:
			pd->type='i';
			pd->data=&hwlights;
			strcpy(pd->name,"hwlights");
			break;
		case 33:
			pd->type='i';
			pd->data=&mouse;
			strcpy(pd->name,"mouse");
			break;
		case 34:
			pd->type='i';
			pd->data=&mipmap;
			strcpy(pd->name,"mipmap");
			break;
		case 35:
			pd->type='i';
			pd->data=&multitexture;
			strcpy(pd->name,"multitexture");
			break;
		case 36:
			pd->type='i';
			pd->data=&mute;
			strcpy(pd->name,"mute");
			break;
		case 37:
			pd->type='i';
			pd->data=&nodeonly;
			strcpy(pd->name,"nodeonly");
			break;
		case 38:
			pd->type='i';
			pd->data=&pvsoff;
			strcpy(pd->name,"pvsoff");
			break;
		case 39:
			pd->type='i';
			pd->data=&shadows;
			strcpy(pd->name,"shadows");
			break;
		case 40:
			pd->type='i';
			pd->data=&status;
			strcpy(pd->name,"status");
			break;
		case 41:
			pd->type='i';
			pd->data=&stencil;
			strcpy(pd->name,"stencil");
			break;
		case 42:
			pd->type='i';
			pd->data=&textfilter;
			strcpy(pd->name,"textfilter");
			break;
		case 43:
			pd->type='i';
			pd->data=&wireframe;
			strcpy(pd->name,"wireframe");
			break;
	}
	return 44;
}

