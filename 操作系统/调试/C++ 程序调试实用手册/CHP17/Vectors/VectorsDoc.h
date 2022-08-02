// VectorsDoc.h : interface of the CVectorsDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_VECTORSDOC_H__EC3E4A9C_382F_11D3_9D69_00A0C994D2F0__INCLUDED_)
#define AFX_VECTORSDOC_H__EC3E4A9C_382F_11D3_9D69_00A0C994D2F0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CVectorsDoc : public CDocument
{
protected: // create from serialization only
	CVectorsDoc();
	DECLARE_DYNCREATE(CVectorsDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVectorsDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CVectorsDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CVectorsDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VECTORSDOC_H__EC3E4A9C_382F_11D3_9D69_00A0C994D2F0__INCLUDED_)
