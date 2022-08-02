
// SketchViewDoc.cpp : implementation of the CSketchViewDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Soln20_01.h"
#endif

#include "SketchViewDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CSketchViewDoc

IMPLEMENT_DYNCREATE(CSketchViewDoc, CDocument)

BEGIN_MESSAGE_MAP(CSketchViewDoc, CDocument)
END_MESSAGE_MAP()


// CSketchViewDoc construction/destruction

CSketchViewDoc::CSketchViewDoc()
{
	// TODO: add one-time construction code here

}

CSketchViewDoc::~CSketchViewDoc()
{
  // Delete the element pointed to by each list entry
  for(auto iter = m_ElementList.begin() ; iter != m_ElementList.end() ; ++iter)
    delete *iter;

   m_ElementList.clear();   // Finally delete all pointers
}

BOOL CSketchViewDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CSketchViewDoc serialization

void CSketchViewDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
    clear();                           // Clear the current list of elements
    int elementType(0);                // Stores element type
    ar >> m_Color                      // Retrieve the current color
       >> elementType                  // the current element type as an integer
       >> m_PenWidth                   // and the current pen width
       >> m_DocSize;                   // and the current document size

    m_Element = static_cast<ElementType>(elementType);

    size_t elementCount(0);            // Count of number of elements
    CObject* pElement(nullptr);        // Element pointer
    ar >> elementCount;                // retrieve the element count
    // Now retrieve all the elements and store in the list
    for(size_t i = 0 ; i < elementCount ; ++i)
    {
      ar >> pElement;
      m_ElementList.push_back(static_cast<CElement*>(pElement));
    }
	}
}

// Get the rectangle enclosing the entire document
CRect CSketchViewDoc::GetDocExtent()
{
  CRect docExtent(0,0,1,1);            // Initial document extent
  for(auto iter = m_ElementList.begin() ; iter != m_ElementList.end() ; ++iter)
    docExtent.UnionRect(docExtent, (*iter)->GetBoundRect());

  docExtent.NormalizeRect();
  return docExtent;
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CSketchViewDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CSketchViewDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CSketchViewDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CSketchViewDoc diagnostics

#ifdef _DEBUG
void CSketchViewDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSketchViewDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CSketchViewDoc commands
