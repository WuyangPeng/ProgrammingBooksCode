
// SketcherView.h : interface of the CSketcherView class
//

#pragma once
#include "atltypes.h"
#include "Element.h"
#include <memory>


class CSketcherView : public CView
{
protected: // create from serialization only
	CSketcherView();
	DECLARE_DYNCREATE(CSketcherView)

// Attributes
public:
	CSketcherDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CSketcherView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
  std::shared_ptr<CElement> CreateElement(void) const;           // Create a new element on the heap

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
  afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
  afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
  afx_msg void OnMouseMove(UINT nFlags, CPoint point);

protected:
  CPoint m_FirstPoint;                           // First point recorded for an element
  CPoint m_SecondPoint;                          // Subsequent point recorded for an element
  // Temporary element
  std::shared_ptr<CElement> m_pTempElement;
};

#ifndef _DEBUG  // debug version in SketcherView.cpp
inline CSketcherDoc* CSketcherView::GetDocument() const
   { return reinterpret_cast<CSketcherDoc*>(m_pDocument); }
#endif

