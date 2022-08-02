// graphDoc.cpp : implementation of the CGraphDoc class
//

#include "stdafx.h"
#include "graph.h"

#include "graphDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGraphDoc

IMPLEMENT_DYNCREATE(CGraphDoc, CDocument)

BEGIN_MESSAGE_MAP(CGraphDoc, CDocument)
	//{{AFX_MSG_MAP(CGraphDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGraphDoc construction/destruction

CGraphDoc::CGraphDoc()
{
}

CGraphDoc::~CGraphDoc()
{
}

BOOL CGraphDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CGraphDoc serialization

void CGraphDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
	}
	else
	{
	}
}

/////////////////////////////////////////////////////////////////////////////
// CGraphDoc diagnostics

#ifdef _DEBUG
void CGraphDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGraphDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGraphDoc commands
