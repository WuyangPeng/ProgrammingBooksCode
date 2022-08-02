// VectorsView.cpp : implementation of the CVectorsView class
//

#include "stdafx.h"
#include "Vectors.h"

#include "VectorsDoc.h"
#include "VectorsView.h"

#include <complex>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVectorsView

IMPLEMENT_DYNCREATE(CVectorsView, CView)

BEGIN_MESSAGE_MAP(CVectorsView, CView)
	//{{AFX_MSG_MAP(CVectorsView)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVectorsView construction/destruction

CVectorsView::CVectorsView()
{
}

CVectorsView::~CVectorsView()
{
}

BOOL CVectorsView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CVectorsView drawing

void CVectorsView::OnDraw(CDC* pDC)
{
	CVectorsDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

    CPen bluepen, greenpen, yellowpen, redpen;
    CPen* oldpen;

    complex<double> x1, x2, x3, temp;

    // Hard wire the three phasor values

    // phasor one
    x2.real(-85.5);                  //-85.5 - j55.2
    x2.imag(-55.2);

    // phasor two
    x1 = polar(63.7, -0.523598);    //63.7 /_ -30 deg
        
    // phasor three
    x3.real(-75.0);                 //-75.0 + j117.9
    x3.imag(117.9);        
  
     // set mapping modes and viewport
    pDC->SetMapMode(MM_ISOTROPIC); 
    pDC->SetWindowExt(300,300);
    pDC->SetViewportExt(m_cxClient,-m_cyClient);
    pDC->SetViewportOrg(m_cxClient/2,m_cyClient/2);

    // draw coordinate axes
    pDC->MoveTo(-150,0);
    pDC->LineTo(150,0);
    pDC->MoveTo(0,-125);
    pDC->LineTo(0,125);

    // draw first phasor with green pen
    greenpen.CreatePen(PS_SOLID,2,RGB(0,255,0));
    oldpen = pDC->SelectObject(&greenpen);
    pDC->MoveTo(0,0);
    pDC->LineTo(real(x1),imag(x1));
    DeleteObject(oldpen);

    temp = x1 + x2;  // add first two phasors

    // draw second phasor with blue pen
    bluepen.CreatePen(PS_SOLID,2,RGB(0,0,255));
    oldpen = pDC->SelectObject(&bluepen);
    pDC->LineTo(real(temp),imag(temp));
    DeleteObject(oldpen);

    temp += x3;     // add in last phasor

    // draw third phasor with yellow pen
    yellowpen.CreatePen(PS_SOLID,2,RGB(255,255,0));
    oldpen = pDC->SelectObject(&yellowpen);
    pDC->LineTo(real(temp),imag(temp));
    DeleteObject(oldpen);

    // draw sum of phasors with wide red pen
    redpen.CreatePen(PS_SOLID,4,RGB(255,0,0));
    oldpen = pDC->SelectObject(&redpen);
    pDC->LineTo(0,0);
    DeleteObject(oldpen); 
}

/////////////////////////////////////////////////////////////////////////////
// CVectorsView diagnostics

#ifdef _DEBUG
void CVectorsView::AssertValid() const
{
	CView::AssertValid();
}

void CVectorsView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CVectorsDoc* CVectorsView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CVectorsDoc)));
	return (CVectorsDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CVectorsView message handlers

void CVectorsView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	m_cxClient = cx;
	m_cyClient = cy;	
}
