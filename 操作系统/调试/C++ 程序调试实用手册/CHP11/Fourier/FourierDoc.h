// FourierDoc.h : interface of the CFourierDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FOURIERDOC_H__1CA31E1C_D9F6_11D2_9D69_0080AE000001__INCLUDED_)
#define AFX_FOURIERDOC_H__1CA31E1C_D9F6_11D2_9D69_0080AE000001__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CFourierDoc : public CDocument
{
protected: // create from serialization only
	CFourierDoc();
	DECLARE_DYNCREATE(CFourierDoc)

    // variables to hold data
    int myterms;

    COLORREF mycolor;

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFourierDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFourierDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFourierDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FOURIERDOC_H__1CA31E1C_D9F6_11D2_9D69_0080AE000001__INCLUDED_)
