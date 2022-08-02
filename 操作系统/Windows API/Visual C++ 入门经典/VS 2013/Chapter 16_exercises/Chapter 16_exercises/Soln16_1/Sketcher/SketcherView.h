
// SketcherView.h : interface of the CSketcherView class
//

#pragma once
#include "atltypes.h"
#include "Element.h"
#include <memory>


class CSketcherView : public CScrollView
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
  std::shared_ptr<CElement> CreateElement() const;         // Create a new element on the heap

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
  afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
  afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
  afx_msg void OnMouseMove(UINT nFlags, CPoint point);
protected:
  
  CPoint m_FirstPoint;                                     // First point recorded for an element
  CPoint m_SecondPoint;                                    // Subsequent point recorded for an element

  CPoint m_CursorPos;                                      // Cursor position
  CPoint m_FirstPos;                                       // Original position in a move
  int m_Scale { 1 };                                       // Current view scale
  std::shared_ptr<CElement> m_pTempElement;
  std::shared_ptr<CElement> m_pSelected;                   // Records element under the cursor
  bool m_MoveMode { false };                               // Move element flag

  virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
  void MoveElement(CClientDC& aDC, const CPoint& point);   // Move an element

public:
  virtual void OnInitialUpdate();
  afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
  afx_msg void OnElementMove();
  afx_msg void OnElementDelete();
  afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
  afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
  afx_msg void OnElementSendtoback();
  afx_msg void OnViewScale();
  virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
  void ResetScrollSizes();
};

#ifndef _DEBUG  // debug version in SketcherView.cpp
inline CSketcherDoc* CSketcherView::GetDocument() const
   { return reinterpret_cast<CSketcherDoc*>(m_pDocument); }
#endif

