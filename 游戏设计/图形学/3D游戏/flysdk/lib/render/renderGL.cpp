#include "../Fly3D.h"

/* ARB_multitexture command function pointers */
FLY_API PFNGLMULTITEXCOORD2IARBPROC glMultiTexCoord2iARB;
FLY_API PFNGLMULTITEXCOORD2FARBPROC glMultiTexCoord2fARB;
FLY_API PFNGLMULTITEXCOORD3FARBPROC glMultiTexCoord3fARB;
FLY_API PFNGLMULTITEXCOORD2FVARBPROC glMultiTexCoord2fvARB;
FLY_API PFNGLMULTITEXCOORD3FVARBPROC glMultiTexCoord3fvARB;
FLY_API PFNGLACTIVETEXTUREARBPROC glActiveTextureARB;

/* NV_register_combiners command function pointers */
FLY_API PFNGLCOMBINERPARAMETERFVNVPROC glCombinerParameterfvNV;
FLY_API PFNGLCOMBINERPARAMETERIVNVPROC glCombinerParameterivNV;
FLY_API PFNGLCOMBINERPARAMETERFNVPROC glCombinerParameterfNV;
FLY_API PFNGLCOMBINERPARAMETERINVPROC glCombinerParameteriNV;
FLY_API PFNGLCOMBINERINPUTNVPROC glCombinerInputNV;
FLY_API PFNGLCOMBINEROUTPUTNVPROC glCombinerOutputNV;
FLY_API PFNGLFINALCOMBINERINPUTNVPROC glFinalCombinerInputNV;
FLY_API PFNGLGETCOMBINERINPUTPARAMETERFVNVPROC glGetCombinerInputParameterfvNV;
FLY_API PFNGLGETCOMBINERINPUTPARAMETERIVNVPROC glGetCombinerInputParameterivNV;
FLY_API PFNGLGETCOMBINEROUTPUTPARAMETERFVNVPROC glGetCombinerOutputParameterfvNV;
FLY_API PFNGLGETCOMBINEROUTPUTPARAMETERIVNVPROC glGetCombinerOutputParameterivNV;
FLY_API PFNGLGETFINALCOMBINERINPUTPARAMETERFVNVPROC glGetFinalCombinerInputfvNV;
FLY_API PFNGLGETFINALCOMBINERINPUTPARAMETERIVNVPROC glGetFinalCombinerInputivNV;

void FlyGetProfile(LPTSTR section, LPTSTR key, LPBYTE lpData, DWORD cbData);

int renderGL::CreateView()
{
	int i,j;
	
	hdc=GetDC(hFlyWnd);
	colorbits=GetDeviceCaps(hdc,BITSPIXEL);

	int color;
	FlyGetProfile("Settings","colorbits", (unsigned char *)&color, sizeof(int));
	if (colorbits!=color)
	{
		MessageBox(hFlyWnd,"Fly3D render configuration not set or display color depth has been changed.\nShould run flyConfig.exe to select a new render mode.","Fly3D",MB_OK|MB_ICONINFORMATION);
		selrendermode=0;
	}

	i=0;
	numvideomodes=0;
	while (EnumDisplaySettings(NULL,i,&videomodes[numvideomodes]))
	{
		if ((int)videomodes[numvideomodes].dmBitsPerPel==colorbits)
			numvideomodes++;
		i++;
	}

	i=1;
	j=DescribePixelFormat(hdc,i,sizeof(PIXELFORMATDESCRIPTOR),&rendermodes[i]);
	numrendermodes=0;
	while(i<j)
	{
		DescribePixelFormat(hdc,i,sizeof(PIXELFORMATDESCRIPTOR),&rendermodes[numrendermodes]);
		if (rendermodes[numrendermodes].iPixelType==0 && 
			rendermodes[numrendermodes].cColorBits==colorbits &&
			(rendermodes[numrendermodes].dwFlags&PFD_DOUBLEBUFFER))
			rendermodesindx[numrendermodes++]=i;
		i++;
	}

	if (selvideomode>numvideomodes)
		selvideomode=0;
	if (selrendermode>numrendermodes)
		selrendermode=0;

	if (SetPixelFormat(hdc, rendermodesindx[selrendermode], &rendermodes[selrendermode]) == FALSE) 
		return FALSE;

	m_hRC = wglCreateContext( hdc );
	wglMakeCurrent( hdc, m_hRC );

	RECT rect;
	GetClientRect(hFlyWnd,&rect);
	ResizeView(rect.right,rect.bottom);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
	glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);
	glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);

	glDisable(GL_LIGHTING);
	glEnable(GL_POINT_SMOOTH);

	glPixelTransferf(GL_RED_SCALE,brightness);
	glPixelTransferf(GL_GREEN_SCALE,brightness);
	glPixelTransferf(GL_BLUE_SCALE,brightness);
	
	GetExtensions();

	glGetIntegerv(GL_MAX_GENERAL_COMBINERS_NV,&nregcomb);
	glGetIntegerv(GL_MAX_LIGHTS,&nhwlights);
	if (nhwlights>MAX_HWLIGHTS)
		nhwlights=MAX_HWLIGHTS;

	glGetIntegerv(GL_DEPTH_BITS,&depthbits);
	glGetIntegerv(GL_STENCIL_BITS,&stencilbits);
	
	glGetIntegerv(GL_ALPHA_BITS,&alphabits);
	glGetIntegerv(GL_ACCUM_ALPHA_BITS,&i);
	accumbits=i;
	glGetIntegerv(GL_ACCUM_RED_BITS,&i);
	accumbits+=i;
	glGetIntegerv(GL_ACCUM_BLUE_BITS,&i);
	accumbits+=i;
	glGetIntegerv(GL_ACCUM_GREEN_BITS,&i);
	accumbits+=i;

	return 1;
}

void renderGL::DeleteView()
{
	if (m_hRC==0)
		return;

	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(m_hRC);
	m_hRC=0;

	ReleaseDC(hFlyWnd,hdc);
	hdc=0;
}

void renderGL::ResizeView(int sx,int sy)
{
	if (m_hRC==0)
		return;
    glViewport(0, 0, sx, sy);
	if (sy==0)
		flyengine->aspect=1;
	else flyengine->aspect=(float)sx/sy;
	screen_sx=sx;
	screen_sy=sy;
}

void renderGL::InitView()
{
	glClearColor( flyengine->background.x, flyengine->background.y, flyengine->background.z, 1 );
    glClearDepth( 1 );

	if (flyengine->antialias)
		glEnable(GL_LINE_SMOOTH);
		
	else
		glDisable(GL_LINE_SMOOTH);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
	glDepthMask(GL_TRUE);

	glShadeModel(GL_SMOOTH);
	glPolygonMode(GL_FRONT,flyengine->wireframe?GL_LINE:GL_FILL);
	glPolygonMode(GL_BACK,flyengine->wireframe?GL_LINE:GL_FILL);
	glPointSize(1.0f);

	glEnable(GL_TEXTURE_2D);

	vector c(1,1,1,1);
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,&c.x);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,&c.x);
	glMateriali(GL_FRONT_AND_BACK,GL_SHININESS,16);

	if (flyengine->fog)
		{
		glEnable(GL_FOG);
		glFogi(GL_FOG_MODE,GL_LINEAR );
		glFogf(GL_FOG_START,flyengine->viewmaxdist*0.7f);
		glFogf(GL_FOG_END,flyengine->viewmaxdist);
		flyengine->background.w=1;
		glFogfv(GL_FOG_COLOR,&flyengine->background.x );
		}
	else glDisable(GL_FOG);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
}

void renderGL::DrawView()
{
	if (m_hRC==0)
		return;
	
	int clear=GL_DEPTH_BUFFER_BIT;
	if (flyengine->clearbk)
		clear|=GL_COLOR_BUFFER_BIT;
	if (flyengine->stencil)
		clear|=GL_STENCIL_BUFFER_BIT;
	InitView();
	glClear( clear );

	if (flyengine->bsp && flyengine->cam && flyengine->player)
		{
		flyengine->cur_frame_base=++flyengine->cur_frame;
		flyengine->dll.send_message(FLYM_DRAWSCENE,0,0);
		
		flyengine->start_text_mode();
		if (flyengine->status)
			flyengine->dll.send_message(FLYM_DRAWTEXT,0,0);
		flyengine->end_text_mode();
		}

	glFinish();
	SwapBuffers(hdc);
}

void renderGL::SetFullScreen()
{
	if (videomodes && selvideomode<numvideomodes)
	{
	if (fullscreen)
		{
		GetWindowRect(hFlyWnd,&winrect);
		if (DISP_CHANGE_SUCCESSFUL==ChangeDisplaySettings(&videomodes[selvideomode],CDS_FULLSCREEN))
			{
			screen_sx=videomodes[selvideomode].dmPelsWidth;
			screen_sy=videomodes[selvideomode].dmPelsHeight;
			SetWindowLong(hFlyWnd,GWL_STYLE,WS_POPUP|WS_CLIPSIBLINGS|WS_CLIPCHILDREN);
			ShowWindow(hFlyWnd,SW_SHOWMAXIMIZED);
			}
		else fullscreen=0;
		}
	else
		{
		ChangeDisplaySettings(NULL,CDS_FULLSCREEN);
		SetWindowLong(hFlyWnd,GWL_STYLE,WS_OVERLAPPEDWINDOW|WS_CLIPCHILDREN|WS_CLIPSIBLINGS);
		ShowWindow(hFlyWnd,SW_RESTORE);
		SetWindowPos(hFlyWnd,HWND_TOP,winrect.left,winrect.top,winrect.right-winrect.left,winrect.bottom-winrect.top,SWP_SHOWWINDOW);
		}
	}
}

void renderGL::GetExtensions()
{
	char* pszExt;
	pszExt = (char*)glGetString( GL_EXTENSIONS );
	if (pszExt==0) return;

	if ( strstr(pszExt,"GL_ARB_multitexture") == 0 )
		ntextureunits=1;
	else
	{
	glGetIntegerv(GL_MAX_TEXTURE_UNITS_ARB,&ntextureunits);
	glMultiTexCoord2iARB =
		(PFNGLMULTITEXCOORD2IARBPROC)
		wglGetProcAddress("glMultiTexCoord2iARB");
	glMultiTexCoord3fARB =
		(PFNGLMULTITEXCOORD3FARBPROC)
		wglGetProcAddress("glMultiTexCoord3fARB");
	glMultiTexCoord3fvARB =
		(PFNGLMULTITEXCOORD3FVARBPROC)
		wglGetProcAddress("glMultiTexCoord3fvARB");
	glActiveTextureARB =
		(PFNGLACTIVETEXTUREARBPROC)
		wglGetProcAddress("glActiveTextureARB");
	glMultiTexCoord2fvARB = 
		(PFNGLMULTITEXCOORD2FVARBPROC)
		wglGetProcAddress("glMultiTexCoord2fvARB");
	glMultiTexCoord2fARB = 
		(PFNGLMULTITEXCOORD2FARBPROC)
		wglGetProcAddress("glMultiTexCoord2fARB");
	}

	if ( strstr(pszExt,"GL_NV_register_combiners") )
	{
	glCombinerParameterfvNV =
		(PFNGLCOMBINERPARAMETERFVNVPROC)
		wglGetProcAddress("glCombinerParameterfvNV");
	glCombinerParameterivNV =
		(PFNGLCOMBINERPARAMETERIVNVPROC)
		wglGetProcAddress("glCombinerParameterivNV");
	glCombinerParameterfNV =
		(PFNGLCOMBINERPARAMETERFNVPROC)
		wglGetProcAddress("glCombinerParameterfNV");
	glCombinerParameteriNV =
		(PFNGLCOMBINERPARAMETERINVPROC)
		wglGetProcAddress("glCombinerParameteriNV");
	glCombinerInputNV =
		(PFNGLCOMBINERINPUTNVPROC)
		wglGetProcAddress("glCombinerInputNV");
	glCombinerOutputNV =
		(PFNGLCOMBINEROUTPUTNVPROC)
		wglGetProcAddress("glCombinerOutputNV");
	glFinalCombinerInputNV =
		(PFNGLFINALCOMBINERINPUTNVPROC)
		wglGetProcAddress("glFinalCombinerInputNV");
	glGetCombinerInputParameterfvNV =
		(PFNGLGETCOMBINERINPUTPARAMETERFVNVPROC)
		wglGetProcAddress("glGetCombinerInputParameterfvNV");
	glGetCombinerInputParameterivNV =
		(PFNGLGETCOMBINERINPUTPARAMETERIVNVPROC)
		wglGetProcAddress("glGetCombinerInputParameterivNV");
	glGetCombinerOutputParameterfvNV =
		(PFNGLGETCOMBINEROUTPUTPARAMETERFVNVPROC)
		wglGetProcAddress("glGetCombinerOutputParameterfvNV");
	glGetCombinerOutputParameterivNV =
		(PFNGLGETCOMBINEROUTPUTPARAMETERIVNVPROC)
		wglGetProcAddress("glGetCombinerOutputParameterivNV");
	glGetFinalCombinerInputfvNV =
		(PFNGLGETFINALCOMBINERINPUTPARAMETERFVNVPROC)
		wglGetProcAddress("glGetFinalCombinerInputfvNV");
	glGetFinalCombinerInputivNV =
		(PFNGLGETFINALCOMBINERINPUTPARAMETERIVNVPROC)
		wglGetProcAddress("glGetFinalCombinerInputivNV");
	}
}