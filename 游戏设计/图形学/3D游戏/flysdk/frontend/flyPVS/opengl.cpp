#include "../../lib/Fly3D.h"
#include "opengl.h"

HGLRC m_hRC;

unsigned char halftone[]=
{
	0xaa,0xaa,0xaa,0xaa,0x55,0x55,0x55,0x55,
	0xaa,0xaa,0xaa,0xaa,0x55,0x55,0x55,0x55,
	0xaa,0xaa,0xaa,0xaa,0x55,0x55,0x55,0x55,
	0xaa,0xaa,0xaa,0xaa,0x55,0x55,0x55,0x55,
	0xaa,0xaa,0xaa,0xaa,0x55,0x55,0x55,0x55,
	0xaa,0xaa,0xaa,0xaa,0x55,0x55,0x55,0x55,
	0xaa,0xaa,0xaa,0xaa,0x55,0x55,0x55,0x55,
	0xaa,0xaa,0xaa,0xaa,0x55,0x55,0x55,0x55,
	0xaa,0xaa,0xaa,0xaa,0x55,0x55,0x55,0x55,
	0xaa,0xaa,0xaa,0xaa,0x55,0x55,0x55,0x55,
	0xaa,0xaa,0xaa,0xaa,0x55,0x55,0x55,0x55,
	0xaa,0xaa,0xaa,0xaa,0x55,0x55,0x55,0x55,
	0xaa,0xaa,0xaa,0xaa,0x55,0x55,0x55,0x55,
	0xaa,0xaa,0xaa,0xaa,0x55,0x55,0x55,0x55,
	0xaa,0xaa,0xaa,0xaa,0x55,0x55,0x55,0x55,
	0xaa,0xaa,0xaa,0xaa,0x55,0x55,0x55,0x55,
};

int CreateView(HDC hdc)
{
	PIXELFORMATDESCRIPTOR pfd, *ppfd;
	int pixelformat;

	ppfd = &pfd;
	memset(ppfd,0,sizeof(PIXELFORMATDESCRIPTOR));

	ppfd->nSize = sizeof(PIXELFORMATDESCRIPTOR);
	ppfd->nVersion = 1;
	ppfd->dwFlags =	PFD_SUPPORT_OPENGL|PFD_DOUBLEBUFFER;
	ppfd->iPixelType = PFD_TYPE_RGBA;
	ppfd->cColorBits = 0;
	ppfd->cDepthBits = 0;
	ppfd->cAccumBits = 0;
	ppfd->cStencilBits = 0;

	pixelformat = ChoosePixelFormat(hdc, ppfd);

	if (SetPixelFormat(hdc, pixelformat, ppfd) == FALSE) 
		return FALSE;

	m_hRC = wglCreateContext( hdc );

	wglMakeCurrent( hdc, m_hRC );

	return 1;
}

void DeleteView()
{
	if (m_hRC==0)
		return;

	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(m_hRC);
	m_hRC=0;
}

void ResizeView(int sx,int sy)
{
	if (m_hRC==0)
		return;
    glViewport(0, 0, sx, sy);
}

void InitView()
{
	glShadeModel(GL_FLAT);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glDisable(GL_DITHER);
	glDisable(GL_FOG);
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);

	glDisable(GL_LINE_SMOOTH);
	glDisable(GL_POLYGON_SMOOTH);

	float f[4]={ 0,0,0,1 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,f);

	glClearColor( 1,1,1,1 );
    glClearDepth( 1 );

	glDrawBuffer(GL_BACK_LEFT);
	glReadBuffer(GL_BACK_LEFT);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective( 90, 1, NEAR_PLANE, FAR_PLANE);
    glMatrixMode( GL_MODELVIEW );

	glPolygonStipple(halftone);
}
