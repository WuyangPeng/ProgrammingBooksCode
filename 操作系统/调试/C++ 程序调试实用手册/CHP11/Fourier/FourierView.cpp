// FourierView.cpp : implementation of the CFourierView class
//

#include "stdafx.h"
#include "Fourier.h"

#include "FourierDoc.h"
#include "FourierView.h"

// additional header files needed
#include "FourierDlg.h"
#include "math.h"

CColorDialog dlg1;  // include common color dialog box

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFourierView

IMPLEMENT_DYNCREATE(CFourierView, CView)

BEGIN_MESSAGE_MAP(CFourierView, CView)
	//{{AFX_MSG_MAP(CFourierView)
	ON_WM_SIZE()
	ON_COMMAND(IDM_FOURIER, OnFourier)
	ON_COMMAND(IDM_COLOR, OnColor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFourierView construction/destruction

CFourierView::CFourierView()
{
}

CFourierView::~CFourierView()
{
}

BOOL CFourierView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);

}

/////////////////////////////////////////////////////////////////////////////
// CFourierView drawing

void CFourierView::OnDraw(CDC* pDC)
{
	CFourierDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);


	// all remaining code for Fourier Series
    int i,j,ang;
    double y, yp;
    CBrush newbrush;
    CBrush* oldbrush;
    CPen newpen;
    CPen* oldpen;

	// common color dialog box structure information
    // allow initial color value to be set
	dlg1.m_cc.Flags |= CC_FULLOPEN | CC_RGBINIT;
   	dlg1.m_cc.rgbResult = pDoc->mycolor;

    pDC->SetMapMode(MM_ISOTROPIC);
    pDC->SetWindowExt(500,500);
    pDC->SetViewportExt(m_cxClient,-m_cyClient);
    pDC->SetViewportOrg(m_cxClient/20,m_cyClient/2);

    ang=0;
    yp=0.0;

    newpen.CreatePen(BS_SOLID,1,RGB(0,0,0));
    oldpen=pDC->SelectObject(&newpen);
   
    // draw x & y coordinate axes
    pDC->MoveTo(0,240);
    pDC->LineTo(0,-240);
    pDC->MoveTo(0,0);
    pDC->LineTo(400,0);
    pDC->MoveTo(0,0);
    // draw actual Fourier waveform
    for (i=0; i<=400; i++) {
      for (j=1; j<=pDoc->myterms; j++) {
        y=(250.0/((2.0*j)-1.0))*sin(((j*2.0)-1.0)*(ang*2.0*3.14159265359/400.0)); 
        yp=yp+y;
	  }
      pDC->LineTo(i,(int) yp);
      yp-=yp;
      ang++;
	}

	// create brush from common color dialog box selection
	// for waveform fill
    newbrush.CreateSolidBrush(pDoc->mycolor); 

    oldbrush=pDC->SelectObject(&newbrush);
    pDC->ExtFloodFill(150,10,RGB(0,0,0),FLOODFILLBORDER);
    pDC->ExtFloodFill(300,-10,RGB(0,0,0),FLOODFILLBORDER);

    // delete brush objects
    pDC->SelectObject(oldbrush);
    newbrush.DeleteObject();
}

/////////////////////////////////////////////////////////////////////////////
// CFourierView diagnostics

#ifdef _DEBUG
void CFourierView::AssertValid() const
{
	CView::AssertValid();
}

void CFourierView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CFourierDoc* CFourierView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFourierDoc)));
	return (CFourierDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFourierView message handlers

void CFourierView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	// TODO: Add your message handler code here
	
	// WHM: added for sizing and scaling window
	m_cxClient = cx;
	m_cyClient = cy;
}

void CFourierView::OnFourier() 
{
	// TODO: Add your command handler code here
	
	// WHM: added to process dialog information
	FourierDlg dlg (this);
	int result = dlg.DoModal();
	
    if(result==IDOK) {
		CFourierDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);

		pDoc->myterms=dlg.m_terms;
		Invalidate();
    }
}

void CFourierView::OnColor() 
{
	// TODO: Add your command handler code here
	// WHM: added to process common color
	// dialog box information
	
	int result = dlg1.DoModal();

	if(result==IDOK) {
        CFourierDoc* pDoc = GetDocument();
        ASSERT_VALID(pDoc);

		// get returned color from dialog box       
		pDoc->mycolor = dlg1.GetColor();
       	InvalidateRect(NULL,TRUE);
		UpdateWindow();
    }
}

