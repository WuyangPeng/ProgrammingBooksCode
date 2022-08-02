
// SketcherDoc.h : interface of the CSketcherDoc class
//

#pragma once
#include "ElementType.h"
#include "ElementColor.h"
#include "Element.h"
#include <list>
#include <memory>

using SketchIterator = std::list<std::shared_ptr<CElement>>::const_iterator;
class CSketcherDoc : public CDocument
{
protected: // create from serialization only
	CSketcherDoc();
	DECLARE_DYNCREATE(CSketcherDoc)

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
	virtual ~CSketcherDoc();

    // Add a sketch element
  void AddElement(std::shared_ptr<CElement>& pElement) {  m_Sketch.push_back(pElement);  }

  // Delete a sketch element
  void DeleteElement(std::shared_ptr<CElement>& pElement) {  m_Sketch.remove(pElement);  }

  int GetLineStyle() { return m_LineStyle; }

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

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

  ElementType GetElementType()const { return m_Element; }
  ElementColor GetElementColor() const { return m_Color; }
  SketchIterator begin() const { return std::begin(m_Sketch);  }            // Provide a begin iterator for the sketch
  SketchIterator end() const { return std::end(m_Sketch);  }                // Provide an end iterator for the sketch

protected:
  ElementType m_Element{ ElementType::LINE };               // Current element type
  ElementColor m_Color{ ElementColor::BLACK };              // Current element type
  int m_LineStyle{ PS_SOLID };                              // Current line style
std::list<std::shared_ptr<CElement>> m_Sketch;              // A list containing the sketch

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
  afx_msg void OnLinestyleSolid();
  afx_msg void OnLinestyleDashed();
  afx_msg void OnLinestyleDotted();
  afx_msg void OnLinestyleDashDotDotted();
  afx_msg void OnLinestyleDashDotted();
  afx_msg void OnUpdateLinestyleSolid(CCmdUI *pCmdUI);
  afx_msg void OnUpdateLinestyleDashed(CCmdUI *pCmdUI);
  afx_msg void OnUpdateLinestyleDotted(CCmdUI *pCmdUI);
  afx_msg void OnUpdateLinestyleDashDotted(CCmdUI *pCmdUI);
  afx_msg void OnUpdateLinestyleDashdotdotted(CCmdUI *pCmdUI);
};
