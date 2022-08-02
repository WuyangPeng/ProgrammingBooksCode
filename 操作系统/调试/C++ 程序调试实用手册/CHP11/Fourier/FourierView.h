// FourierView.h : interface of the CFourierView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FOURIERVIEW_H__1CA31E1E_D9F6_11D2_9D69_0080AE000001__INCLUDED_)
#define AFX_FOURIERVIEW_H__1CA31E1E_D9F6_11D2_9D69_0080AE000001__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CFourierView : public CView
{
protected: // create from serialization only
	CFourierView();
	DECLARE_DYNCREATE(CFourierView)

    // sizing parameters
    int m_cxClient, m_cyClient;

// Attributes
public:
	CFourierDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFourierView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFourierView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:


// Generated message map functions
protected:
	//{{AFX_MSG(CFourierView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnFourier();
	afx_msg void OnColor();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in FourierView.cpp
inline CFourierDoc* CFourierView::GetDocument()
   { return (CFourierDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FOURIERVIEW_H__1CA31E1E_D9F6_11D2_9D69_0080AE000001__INCLUDED_)
