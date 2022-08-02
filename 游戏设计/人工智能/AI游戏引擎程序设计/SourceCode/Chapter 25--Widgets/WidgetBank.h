#pragma once

#include "Widgets/Common.h"

class Group;

/******************************************************************************
 *	WidgetBank:	This is the window that is host to all the widgets for your
 *				application. It floats separately from the main window, and can
 *				be resized. You don't add widgets directly to the widget bank;
 *				instead you add Groups using AddGroup(). AddGroup() returns a
 *				pointer to the group that was added, which you use to add
 *				actual widgets.
 *
 *****************************************************************************/
class WidgetBank : public CWnd
{
public:
	// constructors
	WidgetBank();
	virtual ~WidgetBank();

	// member methods
	void Init();
	void Draw();
	void UpdateWidgetBankSize();
	void Update();
	
	// widget creation methods
	int GetHeight();
	Group* AddGroup( char * label );
	afx_msg UINT OnNcHitTest(CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

	// member variables
	Group * m_groups[MAX_CHILD_GROUPS];
		
	int		m_numGroups;
	CRect	m_ClientSize ;

	DECLARE_DYNCREATE(WidgetBank)

	DECLARE_MESSAGE_MAP()

private:
	int m_id;
public:
	afx_msg void OnNcDestroy();
 	virtual BOOL CreateEx(DWORD dwExStyle, LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, LPVOID lpParam = NULL);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};


