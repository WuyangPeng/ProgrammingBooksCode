// MLeakDoc.cpp : implementation of the CMLeakDoc class
//

#include "stdafx.h"
#include "MLeak.h"

#include "MLeakDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMLeakDoc

IMPLEMENT_DYNCREATE(CMLeakDoc, CDocument)

BEGIN_MESSAGE_MAP(CMLeakDoc, CDocument)
	//{{AFX_MSG_MAP(CMLeakDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMLeakDoc construction/destruction

CMLeakDoc::CMLeakDoc()
{
	myCString = "This program doesn't have a leak";
}

CMLeakDoc::~CMLeakDoc()
{
}

BOOL CMLeakDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMLeakDoc serialization

void CMLeakDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
	}
	else
	{
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMLeakDoc diagnostics

#ifdef _DEBUG
void CMLeakDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMLeakDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMLeakDoc commands
