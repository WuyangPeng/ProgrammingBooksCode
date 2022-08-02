
// SketchViewDoc.h : interface of the CSketchViewDoc class
//


#pragma once
#include <list>
#include "Elements.h"
#include "SketcherConstants.h"


class CSketchViewDoc : public CDocument
{
protected: // create from serialization only
	CSketchViewDoc();
	DECLARE_DYNCREATE(CSketchViewDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CSketchViewDoc();
   std::list<CElement*>::const_iterator begin() const // Get list begin iterator
                   { return m_ElementList.begin(); }
   std::list<CElement*>::const_iterator end() const   // Get list end iterator
                   { return m_ElementList.end(); }
   void clear() { m_ElementList.clear(); }            // Clear the list of elements
  CRect GetDocExtent();                               // Get the bounding rectangle for the whole document

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
  int m_PenWidth;                                     // Current pen width
  CSize m_DocSize;                                    // Document size
  ElementType m_Element;                              // Current element type
  COLORREF m_Color;                                   // Current element color
  std::list<CElement*> m_ElementList;                 // List of elements in the sketch

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
