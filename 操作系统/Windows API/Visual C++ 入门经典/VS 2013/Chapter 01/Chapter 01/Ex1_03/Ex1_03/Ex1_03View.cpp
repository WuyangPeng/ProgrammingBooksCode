
// Ex1_03View.cpp : implementation of the CEx1_03View class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Ex1_03.h"
#endif

#include "Ex1_03Doc.h"
#include "Ex1_03View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEx1_03View

IMPLEMENT_DYNCREATE(CEx1_03View, CView)

BEGIN_MESSAGE_MAP(CEx1_03View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CEx1_03View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CEx1_03View construction/destruction

CEx1_03View::CEx1_03View()
{
	// TODO: add construction code here

}

CEx1_03View::~CEx1_03View()
{
}

BOOL CEx1_03View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CEx1_03View drawing

void CEx1_03View::OnDraw(CDC* /*pDC*/)
{
	CEx1_03Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CEx1_03View printing


void CEx1_03View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CEx1_03View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CEx1_03View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CEx1_03View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CEx1_03View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CEx1_03View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CEx1_03View diagnostics

#ifdef _DEBUG
void CEx1_03View::AssertValid() const
{
	CView::AssertValid();
}

void CEx1_03View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEx1_03Doc* CEx1_03View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx1_03Doc)));
	return (CEx1_03Doc*)m_pDocument;
}
#endif //_DEBUG


// CEx1_03View message handlers
