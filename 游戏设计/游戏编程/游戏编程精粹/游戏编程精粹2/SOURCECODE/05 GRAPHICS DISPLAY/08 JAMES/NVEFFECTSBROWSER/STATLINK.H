/* Copyright (C) Greg James, 2001. 
 * All rights reserved worldwide.
 *
 * This software is provided "as is" without express or implied
 * warranties. You may freely copy and compile this source into
 * applications you distribute provided that the copyright text
 * below is included in the resulting source code, for example:
 * "Portions Copyright (C) Greg James, 2001"
 */
////////////////////////////////////////////////////////////////
// CStaticLink 1997 Microsoft Systems Journal. 
// If this program works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
//

////////////////
// CStaticLink implements a static control that's a hyperlink
// to any file on your desktop or web. You can use it in dialog boxes
// to create hyperlinks to web sites. When clicked, opens the file/URL
//
class CStaticLink : public CStatic {
public:
	CStaticLink();

	// you can change these any time:
	COLORREF	 m_colorUnvisited;		 // color for unvisited
	COLORREF	 m_colorVisited;			 // color for visited
	BOOL		 m_bVisited;				 // whether visited or not

	// URL/filename for non-text controls (eg icon, bitmap) or when link is
	// different from window text. If you don't set this, CStaticIcon will
	// use GetWindowText to get the link.
	CString	 m_link;

protected:
	DECLARE_DYNAMIC(CStaticLink)
	CFont		 m_font;						 // underline font for text control

	// message handlers
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg void	OnClicked();
	DECLARE_MESSAGE_MAP()
};
