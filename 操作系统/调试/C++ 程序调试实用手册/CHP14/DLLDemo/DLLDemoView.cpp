// DLLDemoView.cpp : implementation of the CDLLDemoView class
//

#include "stdafx.h"
#include "DLLDemo.h"

#include "DLLDemoDoc.h"
#include "DLLDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDLLDemoView

IMPLEMENT_DYNCREATE(CDLLDemoView, CView)

BEGIN_MESSAGE_MAP(CDLLDemoView, CView)
	//{{AFX_MSG_MAP(CDLLDemoView)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDLLDemoView construction/destruction

CDLLDemoView::CDLLDemoView()
{
}

CDLLDemoView::~CDLLDemoView()
{
}

BOOL CDLLDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDLLDemoView drawing

void CDLLDemoView::OnDraw(CDC* pDC)
{
	CDLLDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

    // Call ThickPixel() several times
	for (int i=50;i<900;i+=100)
		ThickPixel(pDC,i,75);

	// Call ThickRectangle() several times
	ThickRectangle(pDC,50,300,75,350,20);
	ThickRectangle(pDC,150,350,250,450,25);
	ThickRectangle(pDC,400,200,700,600,25);

	// Call ThickEllipse() several times
    ThickEllipse(pDC,50,100,75,150,10);
	ThickEllipse(pDC,150,150,250,250,15);
	ThickEllipse(pDC,450,250,650,550,10);
}

/////////////////////////////////////////////////////////////////////////////
// CDLLDemoView diagnostics

#ifdef _DEBUG
void CDLLDemoView::AssertValid() const
{
	CView::AssertValid();
}

void CDLLDemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDLLDemoDoc* CDLLDemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDLLDemoDoc)));
	return (CDLLDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDLLDemoView message handlers
