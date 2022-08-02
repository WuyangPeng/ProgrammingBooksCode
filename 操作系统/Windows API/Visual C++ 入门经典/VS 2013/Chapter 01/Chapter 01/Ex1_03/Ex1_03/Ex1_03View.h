
// Ex1_03View.h : interface of the CEx1_03View class
//

#pragma once


class CEx1_03View : public CView
{
protected: // create from serialization only
	CEx1_03View();
	DECLARE_DYNCREATE(CEx1_03View)

// Attributes
public:
	CEx1_03Doc* GetDocument() const;

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
	virtual ~CEx1_03View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Ex1_03View.cpp
inline CEx1_03Doc* CEx1_03View::GetDocument() const
   { return reinterpret_cast<CEx1_03Doc*>(m_pDocument); }
#endif

