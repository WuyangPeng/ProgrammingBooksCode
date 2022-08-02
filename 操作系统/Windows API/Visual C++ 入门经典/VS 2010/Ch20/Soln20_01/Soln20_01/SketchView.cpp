
// SketchView.cpp : implementation of the CSketchView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Soln20_01.h"
#endif

#include "SketchViewDoc.h"
#include "SketchView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSketchView

IMPLEMENT_DYNCREATE(CSketchView, CView)

BEGIN_MESSAGE_MAP(CSketchView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CSketchView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CSketchView construction/destruction

CSketchView::CSketchView()
{
	// TODO: add construction code here

}

CSketchView::~CSketchView()
{
}

BOOL CSketchView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CSketchView drawing

void CSketchView::OnDraw(CDC* pDC)
{
	CSketchViewDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;


  CElement* pElement(0);
  for(auto iter = pDoc->begin() ; iter != pDoc->end() ; ++iter)
  {
    pElement = *iter;
    if(pDC->RectVisible(pElement->GetBoundRect())) // If the element is visible
         pElement->Draw(pDC, nullptr);             // ...draw it
  }
}


// CSketchView printing


void CSketchView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CSketchView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSketchView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSketchView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CSketchView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CSketchView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CSketchView diagnostics

#ifdef _DEBUG
void CSketchView::AssertValid() const
{
	CView::AssertValid();
}

void CSketchView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSketchViewDoc* CSketchView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSketchViewDoc)));
	return (CSketchViewDoc*)m_pDocument;
}
#endif //_DEBUG


// CSketchView message handlers


void CSketchView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{
  // Here we adjust the mapping mode and the viewport & window extents before drawing the sketch.
  // We adjust the window extent so the document fits in the current client area

  CView::OnPrepareDC(pDC, pInfo);
      CRect rect;
      GetClientRect (&rect);                                   // Get current client area

  pDC->SetMapMode(MM_ISOTROPIC);                               // Map mode with equally scaled axes
  CRect docExtent = GetDocument()->GetDocExtent();             // Get the extent of the document
  pDC->SetWindowExt(docExtent.Width(), -docExtent.Height());   // Set the window extent for the document size
  pDC->SetViewportExt(rect.Width(), -rect.Height());           // Set the viewport extent for MM_ISOTROPIC
}
