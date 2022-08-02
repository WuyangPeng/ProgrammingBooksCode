
// SketcherDoc.cpp : implementation of the CSketcherDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Sketcher.h"
#include "PenDialog.h"
#endif

#include "SketcherDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CSketcherDoc

IMPLEMENT_DYNCREATE(CSketcherDoc, CDocument)

BEGIN_MESSAGE_MAP(CSketcherDoc, CDocument)
ON_COMMAND(ID_COLOR_BLACK, &CSketcherDoc::OnColorBlack)
ON_COMMAND(ID_COLOR_RED, &CSketcherDoc::OnColorRed)
ON_COMMAND(ID_COLOR_GREEN, &CSketcherDoc::OnColorGreen)
ON_COMMAND(ID_ELEMENT_LINE, &CSketcherDoc::OnElementLine)
ON_COMMAND(ID_ELEMENT_RECTANGLE, &CSketcherDoc::OnElementRectangle)
ON_COMMAND(ID_ELEMENT_CIRCLE, &CSketcherDoc::OnElementCircle)
ON_COMMAND(ID_ELEMENT_CURVE, &CSketcherDoc::OnElementCurve)
ON_COMMAND(ID_COLOR_BLUE, &CSketcherDoc::OnColorBlue)
ON_UPDATE_COMMAND_UI(ID_COLOR_BLACK, &CSketcherDoc::OnUpdateColorBlack)
ON_UPDATE_COMMAND_UI(ID_COLOR_RED, &CSketcherDoc::OnUpdateColorRed)
ON_UPDATE_COMMAND_UI(ID_COLOR_GREEN, &CSketcherDoc::OnUpdateColorGreen)
ON_UPDATE_COMMAND_UI(ID_COLOR_BLUE, &CSketcherDoc::OnUpdateColorBlue)
ON_UPDATE_COMMAND_UI(ID_ELEMENT_LINE, &CSketcherDoc::OnUpdateElementLine)
ON_UPDATE_COMMAND_UI(ID_ELEMENT_RECTANGLE, &CSketcherDoc::OnUpdateElementRectangle)
ON_UPDATE_COMMAND_UI(ID_ELEMENT_CIRCLE, &CSketcherDoc::OnUpdateElementCircle)
ON_UPDATE_COMMAND_UI(ID_ELEMENT_CURVE, &CSketcherDoc::OnUpdateElementCurve)
ON_COMMAND(ID_PEN_WIDTH, &CSketcherDoc::OnPenWidth)
ON_COMMAND(ID_ELEMENT_TEXT, &CSketcherDoc::OnElementText)
ON_UPDATE_COMMAND_UI(ID_ELEMENT_TEXT, &CSketcherDoc::OnUpdateElementText)
END_MESSAGE_MAP()


// CSketcherDoc construction/destruction

CSketcherDoc::CSketcherDoc() :
   m_Element(LINE)
,  m_Color(BLACK)
,  m_PenWidth(0)
, m_DocSize(CSize(3000,3000))

{
	// TODO: add one-time construction code here

}

CSketcherDoc::~CSketcherDoc()
{
  // Delete the element pointed to by each list entry
  for(auto iter = m_ElementList.begin() ; iter != m_ElementList.end() ; ++iter)
    delete *iter;

   m_ElementList.clear();   // Finally delete all pointers
}

BOOL CSketcherDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CSketcherDoc serialization

void CSketcherDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
    ar << m_Color                      // Store the current color
       << static_cast<int>(m_Element)  // the current element type as an integer
       << m_PenWidth                   // and the current pen width
       << m_DocSize;                   // and the current document size
       
    ar << m_ElementList.size();        // Store the number of elements in the list

    // Now store the elements from the list
    for(auto iter =  m_ElementList.begin() ; iter != m_ElementList.end() ; ++iter)
      ar << *iter;                     // Store the element
	}
	else
	{
    int elementType(0);                // Stores element type
    ar >> m_Color                      // Retrieve the current color
       >> elementType                  // the current element type as an integer
       >> m_PenWidth                   // and the current pen width
       >> m_DocSize;                   // and the current document size

    m_Element = static_cast<ElementType>(elementType);

    size_t elementCount(0);            // Count of number of elements
    CElement* pElement(nullptr);       // Element pointer
    ar >> elementCount;                // retrieve the element count
    // Now retrieve all the elements and store in the list
    for(size_t i = 0 ; i < elementCount ; ++i)
    {
      ar >> pElement;
      m_ElementList.push_back(pElement);
    }
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CSketcherDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void CSketcherDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CSketcherDoc::SetSearchContent(const CString& value)
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

// CSketcherDoc diagnostics

#ifdef _DEBUG
void CSketcherDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSketcherDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CSketcherDoc commands


void CSketcherDoc::OnColorBlack()
{
   m_Color = BLACK;          // Set the drawing color to black
}


void CSketcherDoc::OnColorRed()
{
   m_Color = RED;            // Set the drawing color to red
}


void CSketcherDoc::OnColorGreen()
{
   m_Color = GREEN;          // Set the drawing color to green
}


void CSketcherDoc::OnColorBlue()
{
   m_Color = BLUE;           // Set the drawing color to blue
}


void CSketcherDoc::OnElementLine()
{
   m_Element = LINE;         // Set element type as a line
}


void CSketcherDoc::OnElementRectangle()
{
   m_Element = RECTANGLE;    // Set element type as a rectangle
}


void CSketcherDoc::OnElementCircle()
{
   m_Element = CIRCLE;       // Set element type as a circle
}


void CSketcherDoc::OnElementCurve()
{
   m_Element = CURVE;        // Set element type as a curve
}



void CSketcherDoc::OnUpdateColorBlack(CCmdUI *pCmdUI)
{
   // Set menu item Checked if the current color is black
   pCmdUI->SetCheck(m_Color==BLACK);
}


void CSketcherDoc::OnUpdateColorRed(CCmdUI *pCmdUI)
{
   // Set menu item Checked if the current color is red
   pCmdUI->SetCheck(m_Color==RED);
}


void CSketcherDoc::OnUpdateColorGreen(CCmdUI *pCmdUI)
{
   // Set menu item Checked if the current color is green
   pCmdUI->SetCheck(m_Color==GREEN);
}


void CSketcherDoc::OnUpdateColorBlue(CCmdUI *pCmdUI)
{
   // Set menu item Checked if the current color is blue
   pCmdUI->SetCheck(m_Color==BLUE);
}


void CSketcherDoc::OnUpdateElementLine(CCmdUI *pCmdUI)
{
   // Set Checked if the current element is a line
   pCmdUI->SetCheck(m_Element==LINE);
}


void CSketcherDoc::OnUpdateElementRectangle(CCmdUI *pCmdUI)
{
   // Set Checked if the current element is a rectangle
   pCmdUI->SetCheck(m_Element==RECTANGLE);
}


void CSketcherDoc::OnUpdateElementCircle(CCmdUI *pCmdUI)
{
   // Set Checked if the current element is a circle
   pCmdUI->SetCheck(m_Element==CIRCLE);
}


void CSketcherDoc::OnUpdateElementCurve(CCmdUI *pCmdUI)
{
   // Set Checked if the current element is a curve
   pCmdUI->SetCheck(m_Element==CURVE);
}


// Finds the element under the point
CElement* CSketcherDoc::FindElement(const CPoint point) const
{
  for(auto rIter = m_ElementList.rbegin() ; rIter != m_ElementList.rend() ; ++rIter)
  {
    if((*rIter)->GetBoundRect().PtInRect(point))
      return *rIter;
  }
      return NULL;
}

// Delete an element from the sketch
void CSketcherDoc::DeleteElement(CElement* pElement)
{
  if(pElement)
  {
    m_ElementList.remove(pElement);    // Remove the pointer from the list
    SetModifiedFlag();                 // Set the modified flag
    delete pElement;                   // Delete the element from the heap
  }
}

// Move the element to the beginning of the list
void CSketcherDoc::SendToBack(CElement* pElement)
{
  if(pElement)
  {
    m_ElementList.remove(pElement);     // Remove the element from the list
    m_ElementList.push_front(pElement);  // Put it back at the beginning of the list
  }
} 


void CSketcherDoc::OnPenWidth()
{
   CPenDialog aDlg;                    // Create a local dialog object

   // Set the pen width in the dialog to that stored in the document
   aDlg.m_PenWidth = m_PenWidth;

   // Display the dialog as modal
   // When closed with OK, get the pen width
   if(aDlg.DoModal() == IDOK)
   {
      m_PenWidth = aDlg.m_PenWidth;
   }
}


void CSketcherDoc::OnElementText()
{
  m_Element = TEXT;
}


void CSketcherDoc::OnUpdateElementText(CCmdUI *pCmdUI)
{
  // Set checked if the current element is text
  pCmdUI->SetCheck(m_Element == TEXT);
}

// Get the rectangle enclosing the entire document
CRect CSketcherDoc::GetDocExtent()
{
  CRect docExtent(0,0,1,1);            // Initial document extent
  for(auto iter = m_ElementList.begin() ; iter != m_ElementList.end() ; ++iter)
    docExtent.UnionRect(docExtent, (*iter)->GetBoundRect());

  docExtent.NormalizeRect();
  return docExtent;
}
