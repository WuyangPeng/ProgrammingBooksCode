// graphView.h : interface of the CGraphView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRAPHVIEW_H__3732B2AE_8DDB_11D3_A7DE_0080AE000001__INCLUDED_)
#define AFX_GRAPHVIEW_H__3732B2AE_8DDB_11D3_A7DE_0080AE000001__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CGraphView : public CView
{
protected: // create from serialization only
	CGraphView();
	DECLARE_DYNCREATE(CGraphView)

// Attributes
public:
	CGraphDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGraphView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGraphView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CGraphView)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in graphView.cpp
inline CGraphDoc* CGraphView::GetDocument()
   { return (CGraphDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAPHVIEW_H__3732B2AE_8DDB_11D3_A7DE_0080AE000001__INCLUDED_)
