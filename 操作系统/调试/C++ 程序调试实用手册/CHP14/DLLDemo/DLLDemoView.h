// DLLDemoView.h : interface of the CDLLDemoView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DLLDEMOVIEW_H__D906B1D7_93B3_11D3_A7E0_0080AE000001__INCLUDED_)
#define AFX_DLLDEMOVIEW_H__D906B1D7_93B3_11D3_A7E0_0080AE000001__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

extern void WINAPI ThickRectangle(CDC* pDC,int x1,int y1,
								  int x2,int y2,int t);
extern void WINAPI ThickEllipse(CDC* pDC,int x1,int y1,
								int x2,int y2,int t);
extern void WINAPI ThickPixel(CDC* pDC,int x1,int y1);

class CDLLDemoView : public CView
{
protected: // create from serialization only
	CDLLDemoView();
	DECLARE_DYNCREATE(CDLLDemoView)

// Attributes
public:
	CDLLDemoDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDLLDemoView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDLLDemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDLLDemoView)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in DLLDemoView.cpp
inline CDLLDemoDoc* CDLLDemoView::GetDocument()
   { return (CDLLDemoDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLLDEMOVIEW_H__D906B1D7_93B3_11D3_A7E0_0080AE000001__INCLUDED_)
