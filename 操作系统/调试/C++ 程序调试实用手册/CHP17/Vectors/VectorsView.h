// VectorsView.h : interface of the CVectorsView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_VECTORSVIEW_H__EC3E4A9E_382F_11D3_9D69_00A0C994D2F0__INCLUDED_)
#define AFX_VECTORSVIEW_H__EC3E4A9E_382F_11D3_9D69_00A0C994D2F0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CVectorsView : public CView
{
private:   // member variables for resized window
    int	m_cxClient;
	int m_cyClient;

protected: // create from serialization only
	CVectorsView();
	DECLARE_DYNCREATE(CVectorsView)

// Attributes
public:
	CVectorsDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVectorsView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CVectorsView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CVectorsView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in VectorsView.cpp
inline CVectorsDoc* CVectorsView::GetDocument()
   { return (CVectorsDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VECTORSVIEW_H__EC3E4A9E_382F_11D3_9D69_00A0C994D2F0__INCLUDED_)
