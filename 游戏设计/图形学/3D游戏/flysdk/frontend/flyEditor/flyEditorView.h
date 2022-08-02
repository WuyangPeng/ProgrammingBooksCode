// flyEditorView.h : interface of the CFlyEditorView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FLYEDITORVIEW_H__5A2CCB2B_B946_11D2_8077_D12CBD47771D__INCLUDED_)
#define AFX_FLYEDITORVIEW_H__5A2CCB2B_B946_11D2_8077_D12CBD47771D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MAX_PARAM 128

class CFlyEditorView : public CListView
{
protected: // create from serialization only
	CFlyEditorView();
	DECLARE_DYNCREATE(CFlyEditorView)

// Attributes
public:
	CFlyEditorDoc* GetDocument();
	int nparam;
	param_desc pd[MAX_PARAM];
	int colsizes[3],ncol;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFlyEditorView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	void update_instances(int i);
	void edit_value(int i);
	void edit_list(int i);
	char *edit_files(char *ext,char *filter,char *cur);
	void edit_param(int i);
	void fill_param_list();
	char *get_param_formated(int i);
	void insert_param(char *name,int type,void *data);
	void reset_param_list();
	void set_param_list(bsp_object *o);
	void update_param_list();

	virtual ~CFlyEditorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFlyEditorView)
	afx_msg void OnItemchanged(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKeydown(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	afx_msg void OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in flyEditorView.cpp
inline CFlyEditorDoc* CFlyEditorView::GetDocument()
   { return (CFlyEditorDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FLYEDITORVIEW_H__5A2CCB2B_B946_11D2_8077_D12CBD47771D__INCLUDED_)
