// flyRenderView.cpp : implementation file
//

#include "stdafx.h"
#include "flyEditor.h"
#include "flyEditorDoc.h"
#include "flyEditorView.h"
#include "flyRenderView.h"
#include "LeftView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CFlyRenderView *rv=0;
extern CFlyEditorView *lv;
extern CLeftView *tv;
extern int active_mode;
extern bsp_object *active_sel;
extern CDialogBar *dlgBar;

int anim_framerate=10;
int drawflag=0;
float zoom=100;

/////////////////////////////////////////////////////////////////////////////
// CFlyRenderView

IMPLEMENT_DYNCREATE(CFlyRenderView, CView)

CFlyRenderView::CFlyRenderView()
{
	timer=0;
	render_type=0;
	rv=this;
	rot.load_identity();
	flag=0;
	mouse=0;
}

CFlyRenderView::~CFlyRenderView()
{
	rv=0;
}

BEGIN_MESSAGE_MAP(CFlyRenderView, CView)
	//{{AFX_MSG_MAP(CFlyRenderView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFlyRenderView drawing

void CFlyRenderView::OnDraw(CDC* pDC)
{
	CListCtrl& list=lv->GetListCtrl();
	CTreeCtrl& tree=tv->GetTreeCtrl();
	HTREEITEM item=tree.GetSelectedItem();
	if (item==0) return;
	DWORD type=tree.GetItemData(item);

	switch(type)
	{
	case TREE_TYPE_TEXTURES:
		{
		POSITION pos=list.GetFirstSelectedItemPosition();
		if (pos==0)
			break;
		int i=list.GetNextSelectedItem(pos);
		if (flyengine->piclib[i]->buf)
			DrawPicture(pDC,flyengine->piclib[i]->buf[0],flyengine->piclib[i]->sx,flyengine->piclib[i]->sy,flyengine->piclib[i]->bytespixel);
		}
		break;
	case TREE_TYPE_OBJECTS:
		{
		POSITION pos=list.GetFirstSelectedItemPosition();
		if (pos==0)
			break;
		int i=list.GetNextSelectedItem(pos);
		char buf[255];
		list.GetItemText(i,0,buf,255);
		DrawObject(buf);
		}
		break;
	case TREE_TYPE_LIGHTMAPS:
		{
		POSITION pos=list.GetFirstSelectedItemPosition();
		if (pos==0)
			break;
		int i=list.GetNextSelectedItem(pos);
		DrawPicture(pDC,flyengine->lmpic[i]->bmp,flyengine->lmpic[i]->sizex,flyengine->lmpic[i]->sizey,3);
		}
		break;
	case TREE_TYPE_SOUNDS:
		break;

	default:
		if (active_mode)
		{
			if (drawflag && type>255)
				DrawObject(active_sel);
			else
			if (rend) 
				rend->DrawView();
		}
		else
		{
			if (drawflag && type>255)
				DrawObject((bsp_object *)type);
			else
			if (rend) 
				rend->DrawView();
		}
		break;
	}
}

/////////////////////////////////////////////////////////////////////////////
// CFlyRenderView diagnostics

CFlyEditorDoc* CFlyRenderView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFlyEditorDoc)));
	return (CFlyEditorDoc*)m_pDocument;
}

#ifdef _DEBUG
void CFlyRenderView::AssertValid() const
{
	CView::AssertValid();
}

void CFlyRenderView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFlyRenderView message handlers

int CFlyRenderView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}

void CFlyRenderView::OnDestroy() 
{
	CView::OnDestroy();

	if (timer)
		{
		KillTimer(rv->timer);
		timer=0;
		}
	
	GetDocument()->close_texture_cache();
	free_render();
}

void CFlyRenderView::OnTimer(UINT nIDEvent) 
{
	CListCtrl& list=lv->GetListCtrl();
	CTreeCtrl& tree=tv->GetTreeCtrl();
	HTREEITEM item=tree.GetSelectedItem();
	DWORD type=0;
	if (item!=0) 
		type=tree.GetItemData(item);

	if (type==TREE_TYPE_OBJECTS)
	{
		if (rend) Invalidate(0);
	}
	else
	if (type==TREE_TYPE_TEXTURES ||
		type==TREE_TYPE_LIGHTMAPS ||
		type==TREE_TYPE_SOUNDS)
		;
	else
	{
		flyengine->step();
	
		if (active_mode)
			lv->update_param_list();
	
		if (rend)
			Invalidate(0);
	}
	
	CView::OnTimer(nIDEvent);
}

BOOL CFlyRenderView::OnEraseBkgnd(CDC* pDC) 
{
	CTreeCtrl& tree=tv->GetTreeCtrl();
	HTREEITEM item=tree.GetSelectedItem();
	if (item==0) return CView::OnEraseBkgnd(pDC);
	DWORD type=tree.GetItemData(item);
	if (rend==0 || 
		type==TREE_TYPE_TEXTURES ||
		type==TREE_TYPE_LIGHTMAPS ||
		type==TREE_TYPE_OBJECTS ||
		type==TREE_TYPE_SOUNDS)
		return CView::OnEraseBkgnd(pDC);
	else return 1;
}

void CFlyRenderView::DrawObject(char *name)
{
	if (rend==0) return;
	
	mesh *o=(mesh *)flyengine->get_model_object(name);
	if (o==0) return;

	if (timer==1 && strstr(o->name,".fao"))
		{
		int anim_time=((anim_mesh *)o)->nframes*1000/anim_framerate;
		((anim_mesh *)o)->set_key((timeGetTime()%anim_time)/(float)anim_time);
		}

	float dist=(o->bbox.max-o->bbox.min).length();
	o->color.vec(1,1,1,1);

	glClearColor(1,1,1,1);
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective( flyengine->camangle, flyengine->aspect, flyengine->viewmindist, flyengine->viewmaxdist);
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	glTranslatef(0,0,-dist-zoom);
	glMultMatrixf((float *)&rot.m);
	
	o->draw();

	glFinish();
	SwapBuffers(((renderGL *)rend)->hdc);
}

void CFlyRenderView::DrawObject(bsp_object *obj)
{
	if (rend==0) return;

	glClearColor(1,1,1,1);
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	if (obj)
		{
		glMatrixMode( GL_PROJECTION );
		glLoadIdentity();
		gluPerspective( flyengine->camangle, flyengine->aspect, flyengine->viewmindist, flyengine->viewmaxdist);
		glMatrixMode( GL_MODELVIEW );
		glLoadIdentity();
		glTranslatef(0,0,-zoom);
		glMultMatrixf((float *)&rot.m);
		glTranslatef(-obj->pos.x,-obj->pos.y,-obj->pos.z);
		obj->draw();
		}

	glFinish();
	SwapBuffers(((renderGL *)rend)->hdc);
}

void CFlyRenderView::DrawPicture(CDC* pDC,unsigned char *buf,int sx,int sy,int bytespixel)
{
	struct tagBITMAPINFO bmi;
	memset(&bmi,0,sizeof(bmi));

	bmi.bmiHeader.biSize=sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biCompression=BI_RGB;
	bmi.bmiHeader.biXPelsPerMeter=6000;
	bmi.bmiHeader.biYPelsPerMeter=6000;
	bmi.bmiHeader.biClrUsed=0;
	bmi.bmiHeader.biClrImportant=0;
	bmi.bmiHeader.biSizeImage=0;
	bmi.bmiHeader.biWidth=sx;
	bmi.bmiHeader.biHeight=sy;
	bmi.bmiHeader.biPlanes=1;
	bmi.bmiHeader.biBitCount=bytespixel*8;

	int i,j,tx=sx*bytespixel;
	if (tx%4) tx+=(4-tx%4);
	unsigned char *buf2=new unsigned char[tx*sy],*c,cc;
	for( i=0;i<sy;i++ )
		{
		c=&buf2[tx*(sy-i-1)];
		memcpy(c,&buf[i*sx*bytespixel],sx*bytespixel);
		for( j=0;j<sx;j++,c+=bytespixel )
			{
			cc=c[2];
			c[2]=c[0];
			c[0]=cc;
			}
		}

	if (flag%2)
		{
		RECT rect;
		GetClientRect(&rect);
		StretchDIBits(pDC->m_hDC,0,0,rect.right,rect.bottom,0,0,sx,sy,buf2,&bmi,DIB_RGB_COLORS,SRCCOPY);
		}
	else StretchDIBits(pDC->m_hDC,0,0,sx,sy,0,0,sx,sy,buf2,&bmi,DIB_RGB_COLORS,SRCCOPY);

	delete buf2;
}

void CFlyRenderView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CTreeCtrl& tree=tv->GetTreeCtrl();
	HTREEITEM item=tree.GetSelectedItem();
	if (item==0) return;
	DWORD type=tree.GetItemData(item);
	if (type==TREE_TYPE_TEXTURES ||
		type==TREE_TYPE_LIGHTMAPS)
		{
		flag++;
		Invalidate(1);
		}
	else if (mouse==0 && 
			(type==TREE_TYPE_OBJECTS || (drawflag && type>255)))
	{
		mouse=1;
		mousepoint=point;
		SetCapture();
	}
	
	CView::OnLButtonDown(nFlags, point);
}

void CFlyRenderView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
	flyengine->noinput=(bActivate==0);
	CView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}

void CFlyRenderView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);

	if (rend)
		rend->ResizeView(cx,cy);
}

void CFlyRenderView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if (mouse)
	{
		mouse=0;
		ReleaseCapture();
	}
	CView::OnLButtonUp(nFlags, point);
}

void CFlyRenderView::OnMouseMove(UINT nFlags, CPoint point) 
{
	if (mouse==1)
	{
		vector x(rot.m[0][0],rot.m[1][0],rot.m[2][0]);
		vector y(rot.m[0][1],rot.m[1][1],rot.m[2][1]);
		x.normalize();
		y.normalize();
		mat4x4 r;
		r.load_identity();
		r.rotate((point.x-mousepoint.x)*0.5f,y);
		r.rotate((point.y-mousepoint.y)*0.5f,x);
		rot=r*rot;
		mousepoint=point;
		Invalidate(0);
	}
	else if (mouse==2)
	{
		zoom+=(point.x-mousepoint.x)+(point.y-mousepoint.y);
		mousepoint=point;
		Invalidate(0);
	}

	CView::OnMouseMove(nFlags, point);
}


BOOL CFlyRenderView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	zoom-=zDelta*0.1f;	
	if (zoom<10)
		zoom=10;
	else if (zoom>flyengine->viewmaxdist)
			zoom=flyengine->viewmaxdist;
	Invalidate(0);
	return CView::OnMouseWheel(nFlags, zDelta, pt);
}

void CFlyRenderView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	CTreeCtrl& tree=tv->GetTreeCtrl();
	HTREEITEM item=tree.GetSelectedItem();
	if (item==0) return;
	DWORD type=tree.GetItemData(item);
	if (mouse==0 && 
		(type==TREE_TYPE_OBJECTS || (drawflag && type>255)))	
	{
		mouse=2;
		mousepoint=point;
		SetCapture();
	}
	
	CView::OnRButtonDown(nFlags, point);
}

void CFlyRenderView::OnRButtonUp(UINT nFlags, CPoint point) 
{
	if (mouse)
	{
		mouse=0;
		ReleaseCapture();
	}
	
	CView::OnRButtonUp(nFlags, point);
}
