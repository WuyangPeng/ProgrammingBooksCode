// DLLDemoDoc.cpp : implementation of the CDLLDemoDoc class
//

#include "stdafx.h"
#include "DLLDemo.h"

#include "DLLDemoDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDLLDemoDoc

IMPLEMENT_DYNCREATE(CDLLDemoDoc, CDocument)

BEGIN_MESSAGE_MAP(CDLLDemoDoc, CDocument)
	//{{AFX_MSG_MAP(CDLLDemoDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDLLDemoDoc construction/destruction

CDLLDemoDoc::CDLLDemoDoc()
{
}

CDLLDemoDoc::~CDLLDemoDoc()
{
}

BOOL CDLLDemoDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CDLLDemoDoc serialization

void CDLLDemoDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
	}
	else
	{
	}
}

/////////////////////////////////////////////////////////////////////////////
// CDLLDemoDoc diagnostics

#ifdef _DEBUG
void CDLLDemoDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDLLDemoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDLLDemoDoc commands
