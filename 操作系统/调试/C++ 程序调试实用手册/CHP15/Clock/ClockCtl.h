#if !defined(AFX_CLOCKCTL_H__A4386F93_98DE_11D3_A7E0_0080AE000001__INCLUDED_)
#define AFX_CLOCKCTL_H__A4386F93_98DE_11D3_A7E0_0080AE000001__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// ClockCtl.h : Declaration of the CClockCtrl ActiveX Control class.

/////////////////////////////////////////////////////////////////////////////
// CClockCtrl : See ClockCtl.cpp for implementation.

class CClockCtrl : public COleControl
{
	DECLARE_DYNCREATE(CClockCtrl)

// Constructor
public:
	CClockCtrl();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClockCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	protected:
	//}}AFX_VIRTUAL

// Implementation
protected:
	~CClockCtrl();

	void GetDrawRect(CRect* rc);		// Clock Size
	BOOL InFace(CPoint& point);			// Hit the Clock?
	void HitClock(CDC* pdc);			// Blink the clock color

	DECLARE_OLECREATE_EX(CClockCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CClockCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CClockCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CClockCtrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(CClockCtrl)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CClockCtrl)
	BOOL m_clockShape;
	afx_msg void OnClockShapeChanged();
	OLE_COLOR m_hitClock;
	afx_msg void OnHitClockChanged();
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// Event maps
	//{{AFX_EVENT(CClockCtrl)
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(CClockCtrl)
	dispidClockShape = 1L,
	dispidHitClock = 2L,
	//}}AFX_DISP_ID
	};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLOCKCTL_H__A4386F93_98DE_11D3_A7E0_0080AE000001__INCLUDED)
