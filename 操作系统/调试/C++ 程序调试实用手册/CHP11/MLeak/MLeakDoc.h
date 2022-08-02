// MLeakDoc.h : interface of the CMLeakDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MLEAKDOC_H__7D597DAA_8B14_11D3_A7DE_0080AE000001__INCLUDED_)
#define AFX_MLEAKDOC_H__7D597DAA_8B14_11D3_A7DE_0080AE000001__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000




class CMLeakDoc : public CDocument
{
protected: // create from serialization only
	CMLeakDoc();
	DECLARE_DYNCREATE(CMLeakDoc)

	CString myCString;

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMLeakDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMLeakDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMLeakDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MLEAKDOC_H__7D597DAA_8B14_11D3_A7DE_0080AE000001__INCLUDED_)
