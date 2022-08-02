// graphView.cpp : implementation of the CGraphView class
//

#include "stdafx.h"
#include "graph.h"

#include "graphDoc.h"
#include "graphView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGraphView

IMPLEMENT_DYNCREATE(CGraphView, CView)

BEGIN_MESSAGE_MAP(CGraphView, CView)
	//{{AFX_MSG_MAP(CGraphView)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGraphView construction/destruction

CGraphView::CGraphView()
{
}

CGraphView::~CGraphView()
{
}

BOOL CGraphView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CGraphView drawing

void CGraphView::OnDraw(CDC* pDC)
{
	CGraphDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
}

/////////////////////////////////////////////////////////////////////////////
// CGraphView diagnostics

#ifdef _DEBUG
void CGraphView::AssertValid() const
{
	CView::AssertValid();
}

void CGraphView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGraphDoc* CGraphView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGraphDoc)));
	return (CGraphDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGraphView message handlers

void CGraphView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	// Do not call CView::OnPaint() for painting messages

    static DWORD dwColor[9]={RGB(0,0,0),         //black
                             RGB(255,0,0),       //red
                             RGB(0,255,0),       //green
                             RGB(0,0,255),       //blue
                             RGB(255,255,0),     //yellow
                             RGB(255,0,255),     //magenta
                             RGB(0,255,255),     //cyan
                             RGB(127,127,127),   //gray
                             RGB(255,255,255)};  //white

    POINT polylpts[4],polygpts[5];
    int xcoord;

    CBrush newbrush;
    CBrush* oldbrush;
    CPen newpen;
    CPen* oldpen;  
  
    // draws and fills a circle
    newpen.CreatePen(PS_SOLID,2,dwColor[3]);
    oldpen=dc.SelectObject(&newpen);
    newbrush.CreateSolidBrush(dwColor[3]);
    oldbrush=dc.SelectObject(&newbrush);
    dc.Ellipse(400,20,650,270);
    dc.TextOut(500,150,"circle",6);    
    dc.SelectObject(oldbrush);
    newbrush.DeleteObject( );
    dc.SelectObject(oldpen);
    newpen.DeleteObject( );

    // draws and fills an ellipse
    newpen.CreatePen(PS_SOLID,2,dwColor[1]);
    oldpen=dc.SelectObject(&newpen);
    newbrush.CreateSolidBrush(dwColor[1]);
    oldbrush=dc.SelectObject(&newbrush);
    dc.Ellipse(325,300,425,250);
    dc.TextOut(260,265,"ellipse",7); 
    dc.SelectObject(oldbrush);
    newbrush.DeleteObject( );
    dc.SelectObject(oldpen);
    newpen.DeleteObject( );

    // draws several pixels
    for(xcoord=500;xcoord<600;xcoord+=5)
      dc.SetPixel(xcoord,400,0L);
    dc.TextOut(540,410,"pixels",6);

    // draws a wide diagonal line
    newpen.CreatePen(PS_SOLID,10,dwColor[0]);
    oldpen=dc.SelectObject(&newpen);
    dc.MoveTo(20,20);
    dc.LineTo(100,100);
    dc.TextOut(60,20,"<- diagonal line",16);  
    dc.SelectObject(oldpen);
    newpen.DeleteObject( );

    // draws an arc
    newpen.CreatePen(PS_DASH,1,dwColor[3]);
    oldpen=dc.SelectObject(&newpen);
    dc.Arc(25,125,175,225,175,225,100,125);
    dc.TextOut(50,150,"small arc ->",12);   
    dc.SelectObject(oldpen);
    newpen.DeleteObject( );

    // draws a wide chord
    newpen.CreatePen(PS_SOLID,10,dwColor[2]);
    oldpen=dc.SelectObject(&newpen);
    dc.Chord(125,125,275,225,275,225,200,125);
    dc.TextOut(280,150,"<- chord",8);
    dc.SelectObject(oldpen);
    newpen.DeleteObject( );

    // draws a pie slice and fills
    newpen.CreatePen(PS_SOLID,2,dwColor[0]);
    oldpen=dc.SelectObject(&newpen);
    newbrush.CreateSolidBrush(dwColor[2]);
    oldbrush=dc.SelectObject(&newbrush);
    dc.Pie(200,0,300,100,200,50,250,100);
    dc.TextOut(260,80,"<- pie wedge",12);
    dc.SelectObject(oldbrush);
    newbrush.DeleteObject( );
    dc.SelectObject(oldpen);
    newpen.DeleteObject( );

    // draws a rectangle and fills
    newbrush.CreateSolidBrush(dwColor[7]);
    oldbrush=dc.SelectObject(&newbrush);
    dc.Rectangle(25,350,150,425);
    dc.TextOut(50,440,"rectangle",9);
    dc.SelectObject(oldbrush);
    newbrush.DeleteObject( );
  
    // draws a rounded rectangle and fills
    newbrush.CreateHatchBrush(HS_CROSS,dwColor[3]);
    oldbrush=dc.SelectObject(&newbrush);
    dc.RoundRect(400,320,550,360,20,20);
    dc.TextOut(410,300,"rounded rectangle",17);
    dc.SelectObject(oldbrush);
    newbrush.DeleteObject( );

   // draws a wide polygon and fills
    newpen.CreatePen(PS_SOLID,5,dwColor[6]);
    oldpen=dc.SelectObject(&newpen);
    newbrush.CreateHatchBrush(HS_FDIAGONAL,dwColor[4]);
    oldbrush=dc.SelectObject(&newbrush);
    polygpts[0].x=40;
    polygpts[0].y=200;
    polygpts[1].x=100;
    polygpts[1].y=270;
    polygpts[2].x=80;
    polygpts[2].y=290;
    polygpts[3].x=20;
    polygpts[3].y=220;
    polygpts[4].x=40;
    polygpts[4].y=200;
    dc.Polygon(polygpts,5);
    dc.TextOut(80,230,"<- polygon",10);
    dc.SelectObject(oldbrush);
    newbrush.DeleteObject( );
    dc.SelectObject(oldpen);
    newpen.DeleteObject( );

    // draws several wide lines with polyline
    newpen.CreatePen(PS_SOLID,4,dwColor[5]);
    oldpen=dc.SelectObject(&newpen);
    polylpts[0].x=210;
    polylpts[0].y=330;
    polylpts[1].x=210;
    polylpts[1].y=400;
    polylpts[2].x=250;
    polylpts[2].y=400;
    polylpts[3].x=210;
    polylpts[3].y=330;
    dc.Polyline(polylpts,4);
    dc.TextOut(250,350,"polyline",8);  
    dc.SelectObject(oldpen);
    newpen.DeleteObject( );
	
}
