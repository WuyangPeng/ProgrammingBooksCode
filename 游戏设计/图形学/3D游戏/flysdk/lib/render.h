#define FLY_RENDER_NONE 0 
#define FLY_RENDER_OPENGL 1 

class FLY_API render;
class FLY_API renderGL;

class FLY_API render
{
public:
	int type;

	virtual ~render()
	{ ; };

	virtual int CreateView()=0;
	virtual void DeleteView()=0;
	virtual void ResizeView(int sx,int sy)=0;
	virtual void InitView()=0;
	virtual void DrawView()=0;
	virtual void SetFullScreen()=0;
};

class FLY_API renderGL : public render
{
public:

	HGLRC m_hRC;
	HDC hdc;

	renderGL() 
	{ type=FLY_RENDER_OPENGL; hdc=0; m_hRC=0; };
	virtual ~renderGL()	
	{ DeleteView(); };

	int CreateView();
	void DeleteView();
	void ResizeView(int sx,int sy);
	void InitView();
	void DrawView();
	void SetFullScreen();
	void GetExtensions();
};

FLY_API void init_render(int type);
FLY_API void free_render();

extern FLY_API render *rend;

extern FLY_API PIXELFORMATDESCRIPTOR rendermodes[256];
extern FLY_API int rendermodesindx[256];
extern FLY_API DEVMODE videomodes[256];
extern FLY_API int numvideomodes;
extern FLY_API int numrendermodes;
extern FLY_API int selvideomode;
extern FLY_API int selrendermode;

extern FLY_API int ntextureunits;
extern FLY_API int nhwlights;
extern FLY_API int nregcomb;
extern FLY_API int screen_sx,screen_sy;
extern FLY_API int fullscreen;
extern FLY_API int colorbits;
extern FLY_API int stencilbits;
extern FLY_API int depthbits;
extern FLY_API int accumbits;
extern FLY_API int alphabits;
extern FLY_API float brightness;
extern FLY_API RECT winrect;

/* ARB_multitexture command function pointers */
extern FLY_API PFNGLMULTITEXCOORD2IARBPROC glMultiTexCoord2iARB;
extern FLY_API PFNGLMULTITEXCOORD2FARBPROC glMultiTexCoord2fARB;
extern FLY_API PFNGLMULTITEXCOORD3FARBPROC glMultiTexCoord3fARB;
extern FLY_API PFNGLMULTITEXCOORD2FVARBPROC glMultiTexCoord2fvARB;
extern FLY_API PFNGLMULTITEXCOORD3FVARBPROC glMultiTexCoord3fvARB;
extern FLY_API PFNGLACTIVETEXTUREARBPROC glActiveTextureARB;

/* NV_register_combiners command function pointers */
extern FLY_API PFNGLCOMBINERPARAMETERFVNVPROC glCombinerParameterfvNV;
extern FLY_API PFNGLCOMBINERPARAMETERIVNVPROC glCombinerParameterivNV;
extern FLY_API PFNGLCOMBINERPARAMETERFNVPROC glCombinerParameterfNV;
extern FLY_API PFNGLCOMBINERPARAMETERINVPROC glCombinerParameteriNV;
extern FLY_API PFNGLCOMBINERINPUTNVPROC glCombinerInputNV;
extern FLY_API PFNGLCOMBINEROUTPUTNVPROC glCombinerOutputNV;
extern FLY_API PFNGLFINALCOMBINERINPUTNVPROC glFinalCombinerInputNV;
extern FLY_API PFNGLGETCOMBINERINPUTPARAMETERFVNVPROC glGetCombinerInputParameterfvNV;
extern FLY_API PFNGLGETCOMBINERINPUTPARAMETERIVNVPROC glGetCombinerInputParameterivNV;
extern FLY_API PFNGLGETCOMBINEROUTPUTPARAMETERFVNVPROC glGetCombinerOutputParameterfvNV;
extern FLY_API PFNGLGETCOMBINEROUTPUTPARAMETERIVNVPROC glGetCombinerOutputParameterivNV;
extern FLY_API PFNGLGETFINALCOMBINERINPUTPARAMETERFVNVPROC glGetFinalCombinerInputfvNV;
extern FLY_API PFNGLGETFINALCOMBINERINPUTPARAMETERIVNVPROC glGetFinalCombinerInputivNV;
