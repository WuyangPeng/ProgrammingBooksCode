#if !defined(AFX_FLYRENDERVIEW_H__EDE386E0_B9BB_11D2_9263_0080AD426F27__INCLUDED_)
#define AFX_FLYRENDERVIEW_H__EDE386E0_B9BB_11D2_9263_0080AD426F27__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// flyRenderView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFlyRenderView view

class CFlyRenderView : public CView
{
protected:
	CFlyRenderView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CFlyRenderView)

// Attributes
public:
	int timer,render_type,flag;
	mat4x4 rot;
	int mouse;
	CPoint mousepoint;

// Operations
public:
	void DrawObject(char *name);
	void DrawObject(bsp_object *obj);
	void DrawPicture(CDC* pDC,unsigned char *buf,int sx,int sy,int bytespixel);
	CFlyEditorDoc* GetDocument();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFlyRenderView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CFlyRenderView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CFlyRenderView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FLYRENDERVIEW_H__EDE386E0_B9BB_11D2_9263_0080AD426F27__INCLUDED_)
