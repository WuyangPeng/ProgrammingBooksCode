
// SketcherDoc.h : interface of the CSketcherDoc class
//
#include "ElementType.h"
#include "ElementColor.h"
#include "Element.h"
#include <list>
#include <memory>

using SketchIterator = std::list<std::shared_ptr<CElement>>::const_iterator;

#pragma once


class CSketcherDoc : public CDocument
{
protected: // create from serialization only
	CSketcherDoc();
	DECLARE_DYNCREATE(CSketcherDoc)

// Attributes
public:

// Operations
public:
  ElementType GetElementType() const { return m_Element; }
  ElementColor GetElementColor() const { return m_Color; }

  // Provide a begin iterator for the sketch
  SketchIterator begin() const { return std::begin(m_Sketch); }

  // Provide an end iterator for the sketch
  SketchIterator end() const { return std::end(m_Sketch); }

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
	virtual ~CSketcherDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
  // Add a sketch element
  void AddElement(std::shared_ptr<CElement>& pElement)
  {
    m_Sketch.push_back(pElement);
  }

  // Delete a sketch element
  void DeleteElement(std::shared_ptr<CElement>& pElement)
  {
    m_Sketch.remove(pElement);
  }

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
  afx_msg void OnColorBlack();
  afx_msg void OnColorRed();
  afx_msg void OnColorGreen();
  afx_msg void OnColorBlue();
  afx_msg void OnElementLine();
  afx_msg void OnElementRectangle();
  afx_msg void OnElementCircle();
  afx_msg void OnElementCurve();
protected:
  ElementType m_Element { ElementType::LINE };               // Current element type
  ElementColor m_Color { ElementColor::BLACK };              // Current element type
  std::list<std::shared_ptr<CElement>> m_Sketch;             // A list containing the sketch
public:
  afx_msg void OnUpdateColorBlack(CCmdUI *pCmdUI);
  afx_msg void OnUpdateColorRed(CCmdUI *pCmdUI);
  afx_msg void OnUpdateColorGreen(CCmdUI *pCmdUI);
  afx_msg void OnUpdateColorBlue(CCmdUI *pCmdUI);
  afx_msg void OnUpdateElementLine(CCmdUI *pCmdUI);
  afx_msg void OnUpdateElementRectangle(CCmdUI *pCmdUI);
  afx_msg void OnUpdateElementCircle(CCmdUI *pCmdUI);
  afx_msg void OnUpdateElementCurve(CCmdUI *pCmdUI);
  afx_msg void OnElementEllipse();
  afx_msg void OnUpdateElementEllipse(CCmdUI *pCmdUI);
};
