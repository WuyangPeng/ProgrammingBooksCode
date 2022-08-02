// FourierDoc.cpp : implementation of the CFourierDoc class
//

#include "stdafx.h"
#include "Fourier.h"

#include "FourierDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFourierDoc

IMPLEMENT_DYNCREATE(CFourierDoc, CDocument)

BEGIN_MESSAGE_MAP(CFourierDoc, CDocument)
	//{{AFX_MSG_MAP(CFourierDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFourierDoc construction/destruction

CFourierDoc::CFourierDoc()
{
	// WHM: initial values drawn to screen
	myterms = 4;
	mycolor = RGB(255,255,0);
}

CFourierDoc::~CFourierDoc()
{
}

BOOL CFourierDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CFourierDoc serialization

void CFourierDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
	}
	else
	{
	}
}

/////////////////////////////////////////////////////////////////////////////
// CFourierDoc diagnostics

#ifdef _DEBUG
void CFourierDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFourierDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFourierDoc commands
