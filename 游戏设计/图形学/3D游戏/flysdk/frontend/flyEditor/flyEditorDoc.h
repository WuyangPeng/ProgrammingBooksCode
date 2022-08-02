// flyEditorDoc.h : interface of the CFlyEditorDoc class
//
/////////////////////////////////////////////////////////////////////////////

enum 
{ 
	TREE_TYPE_GLOBAL=1,
	TREE_TYPE_PLUGINS,
	TREE_TYPE_OBJECTS,
	TREE_TYPE_SOUNDS,
	TREE_TYPE_TEXTURES,
	TREE_TYPE_LIGHTMAPS,
	TREE_TYPE_DLLS,
	TREE_TYPE_STOCK,
	TREE_TYPE_DYNOBJECT
};

#if !defined(AFX_FLYEDITORDOC_H__5A2CCB29_B946_11D2_8077_D12CBD47771D__INCLUDED_)
#define AFX_FLYEDITORDOC_H__5A2CCB29_B946_11D2_8077_D12CBD47771D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CFlyEditorDoc : public CDocument, public flyEngine
{
protected: // create from serialization only
	CFlyEditorDoc();
	DECLARE_DYNCREATE(CFlyEditorDoc)

// Attributes
public:
	CImageList tree_il;
// Operations
public:
	void find_active();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFlyEditorDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	void FillTreeView();
	virtual ~CFlyEditorDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFlyEditorDoc)
	afx_msg void OnSimmulate();
	afx_msg void OnUpdateSimmulate(CCmdUI* pCmdUI);
	afx_msg void OnRenderOpengl();
	afx_msg void OnUpdateRenderOpengl(CCmdUI* pCmdUI);
	afx_msg void OnRenderNorender();
	afx_msg void OnUpdateRenderNorender(CCmdUI* pCmdUI);
	afx_msg void OnFileRestart();
	afx_msg void OnUpdateFileRestart(CCmdUI* pCmdUI);
	afx_msg void OnViewObjscene();
	afx_msg void OnUpdateViewObjscene(CCmdUI* pCmdUI);
	afx_msg void OnActivate();
	afx_msg void OnActive();
	afx_msg void OnDestroy();
	afx_msg void OnDeltaposSpin(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FLYEDITORDOC_H__5A2CCB29_B946_11D2_8077_D12CBD47771D__INCLUDED_)
