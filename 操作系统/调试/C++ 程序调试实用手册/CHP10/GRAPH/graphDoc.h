// graphDoc.h : interface of the CGraphDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRAPHDOC_H__3732B2AC_8DDB_11D3_A7DE_0080AE000001__INCLUDED_)
#define AFX_GRAPHDOC_H__3732B2AC_8DDB_11D3_A7DE_0080AE000001__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CGraphDoc : public CDocument
{
protected: // create from serialization only
	CGraphDoc();
	DECLARE_DYNCREATE(CGraphDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGraphDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGraphDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CGraphDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAPHDOC_H__3732B2AC_8DDB_11D3_A7DE_0080AE000001__INCLUDED_)
