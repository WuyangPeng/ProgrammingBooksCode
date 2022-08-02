// VectorsDoc.cpp : implementation of the CVectorsDoc class
//

#include "stdafx.h"
#include "Vectors.h"

#include "VectorsDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVectorsDoc

IMPLEMENT_DYNCREATE(CVectorsDoc, CDocument)

BEGIN_MESSAGE_MAP(CVectorsDoc, CDocument)
	//{{AFX_MSG_MAP(CVectorsDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVectorsDoc construction/destruction

CVectorsDoc::CVectorsDoc()
{
}

CVectorsDoc::~CVectorsDoc()
{
}

BOOL CVectorsDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CVectorsDoc serialization

void CVectorsDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
	}
	else
	{
	}
}

/////////////////////////////////////////////////////////////////////////////
// CVectorsDoc diagnostics

#ifdef _DEBUG
void CVectorsDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CVectorsDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CVectorsDoc commands
