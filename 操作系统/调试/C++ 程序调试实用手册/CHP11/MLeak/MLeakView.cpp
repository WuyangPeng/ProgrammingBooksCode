// MLeakView.cpp : implementation of the CMLeakView class
//

#include "stdafx.h"
#include "MLeak.h"

#include "MLeakDoc.h"
#include "MLeakView.h"

CMemoryState oldMemState, newMemState, diffMemState;
CFont NFont;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMLeakView

IMPLEMENT_DYNCREATE(CMLeakView, CView)

BEGIN_MESSAGE_MAP(CMLeakView, CView)
	//{{AFX_MSG_MAP(CMLeakView)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMLeakView construction/destruction

CMLeakView::CMLeakView()
{
}

CMLeakView::~CMLeakView()
{
}

BOOL CMLeakView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMLeakView drawing

void CMLeakView::OnDraw(CDC* pDC)
{

	CMLeakDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

    CFont* pOFont;

	pOFont = pDC->SelectObject(&NFont); 

	pDC->TextOut(20, 200, pDoc->myCString);
	
	pDC->SelectObject(pOFont);
	DeleteObject(pOFont);

#ifdef _DEBUG
	newMemState.Checkpoint();
	if (diffMemState.Difference(oldMemState,newMemState))
	{
	    TRACE("\n\nDifference between start and finish!");
		newMemState.DumpStatistics();
	}
#endif 

}

/////////////////////////////////////////////////////////////////////////////
// CMLeakView diagnostics

#ifdef _DEBUG
void CMLeakView::AssertValid() const
{
	CView::AssertValid();
}

void CMLeakView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMLeakDoc* CMLeakView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMLeakDoc)));
	return (CMLeakDoc*)m_pDocument;
}
#endif //_DEBUG

int CMLeakView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here

    LOGFONT lf;
    memset(&lf,0,sizeof(LOGFONT));

	lf.lfHeight = 50;
	lf.lfWeight=FW_NORMAL;
	lf.lfEscapement=0;       
	lf.lfOrientation=0;      
	lf.lfItalic=false;
	lf.lfUnderline = false;
	lf.lfStrikeOut = false;
	lf.lfCharSet=ANSI_CHARSET;
	lf.lfPitchAndFamily=34;  //Arial

	NFont.CreateFontIndirect(&lf);
    
	#ifdef _DEBUG
		oldMemState.Checkpoint();
	#endif

	return 0;
}



