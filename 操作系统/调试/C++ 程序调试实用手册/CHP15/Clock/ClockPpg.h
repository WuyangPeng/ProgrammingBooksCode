#if !defined(AFX_CLOCKPPG_H__A4386F95_98DE_11D3_A7E0_0080AE000001__INCLUDED_)
#define AFX_CLOCKPPG_H__A4386F95_98DE_11D3_A7E0_0080AE000001__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// ClockPpg.h : Declaration of the CClockPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CClockPropPage : See ClockPpg.cpp.cpp for implementation.

class CClockPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CClockPropPage)
	DECLARE_OLECREATE_EX(CClockPropPage)

// Constructor
public:
	CClockPropPage();

// Dialog Data
	//{{AFX_DATA(CClockPropPage)
	enum { IDD = IDD_PROPPAGE_CLOCK };
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CClockPropPage)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLOCKPPG_H__A4386F95_98DE_11D3_A7E0_0080AE000001__INCLUDED)
