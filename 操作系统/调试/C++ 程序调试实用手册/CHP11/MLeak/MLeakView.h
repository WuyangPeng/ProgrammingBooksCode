// MLeakView.h : interface of the CMLeakView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MLEAKVIEW_H__7D597DAC_8B14_11D3_A7DE_0080AE000001__INCLUDED_)
#define AFX_MLEAKVIEW_H__7D597DAC_8B14_11D3_A7DE_0080AE000001__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMLeakView : public CView
{
protected: // create from serialization only
	CMLeakView();
	DECLARE_DYNCREATE(CMLeakView)

// Attributes
public:
	CMLeakDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMLeakView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMLeakView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMLeakView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MLeakView.cpp
inline CMLeakDoc* CMLeakView::GetDocument()
   { return (CMLeakDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MLEAKVIEW_H__7D597DAC_8B14_11D3_A7DE_0080AE000001__INCLUDED_)
