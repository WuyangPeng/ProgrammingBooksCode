// DLLDemoDoc.h : interface of the CDLLDemoDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DLLDEMODOC_H__D906B1D5_93B3_11D3_A7E0_0080AE000001__INCLUDED_)
#define AFX_DLLDEMODOC_H__D906B1D5_93B3_11D3_A7E0_0080AE000001__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CDLLDemoDoc : public CDocument
{
protected: // create from serialization only
	CDLLDemoDoc();
	DECLARE_DYNCREATE(CDLLDemoDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDLLDemoDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDLLDemoDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDLLDemoDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLLDEMODOC_H__D906B1D5_93B3_11D3_A7E0_0080AE000001__INCLUDED_)
