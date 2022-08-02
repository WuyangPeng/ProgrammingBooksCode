// LeftView.h : interface of the CLeftView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_LEFTVIEW_H__5A2CCB2D_B946_11D2_8077_D12CBD47771D__INCLUDED_)
#define AFX_LEFTVIEW_H__5A2CCB2D_B946_11D2_8077_D12CBD47771D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CFlyEditorDoc;

class CLeftView : public CTreeView
{
protected: // create from serialization only
	CLeftView();
	DECLARE_DYNCREATE(CLeftView)

// Attributes
public:
	CFlyEditorDoc* GetDocument();
	CPoint mouse;
	HTREEITEM SelectObject(HTREEITEM item,bsp_object *o);
// Operations
public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLeftView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CLeftView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CLeftView)
	afx_msg void OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBeginlabeledit(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKeydown(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemexpanded(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRclick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEditDelete();
	afx_msg void OnEditInsert();
	afx_msg void OnUpdateEditDelete(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditInsert(CCmdUI* pCmdUI);
	afx_msg void OnEditRename();
	afx_msg void OnUpdateEditRename(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDown(CCmdUI* pCmdUI);
	afx_msg void OnDown();
	afx_msg void OnUpdateUp(CCmdUI* pCmdUI);
	afx_msg void OnUp();
	afx_msg void OnEditCopy();
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	afx_msg void OnEditCut();
	afx_msg void OnUpdateEditCut(CCmdUI* pCmdUI);
	afx_msg void OnEditDuplicate();
	afx_msg void OnUpdateEditDuplicate(CCmdUI* pCmdUI);
	afx_msg void OnEditPaste();
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in LeftView.cpp
inline CFlyEditorDoc* CLeftView::GetDocument()
   { return (CFlyEditorDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LEFTVIEW_H__5A2CCB2D_B946_11D2_8077_D12CBD47771D__INCLUDED_)
