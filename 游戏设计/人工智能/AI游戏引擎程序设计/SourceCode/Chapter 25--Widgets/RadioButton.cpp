#include "StdAfx.h"
#include "Widgets/RadioButton.h"
#include "Widgets/Common.h"
#include ".\radiobutton.h"

RadioButton::RadioButton( char * groupName, char * leftName, char * rightName, 
						 int & val, CWnd * pWin, int yPos, 
						 int id1, int id2,
						 EventHandler * h ):m_val(val), m_eventHandler(h)
{
	CRect r;
	pWin->GetClientRect( r );

	Create(			NULL,
					"",
					WS_CHILD | WS_VISIBLE,
					CRect (CPoint( 0, yPos ),
					CSize(r.Width(), MINIMIZED_WIDGET_HEIGHT * 2)),
					pWin,
					IDC_WIDGET_RADIO );

	GetClientRect(r);
	m_GroupButton.Create(	groupName,
					WS_CHILD | WS_VISIBLE | BS_GROUPBOX | WS_GROUP,
					CRect (CPoint( 2, 0 ),
					CSize(r.Width(), MINIMIZED_WIDGET_HEIGHT * 2)),
					this,
					IDC_WIDGET_RADIO_GROUP );

	m_LeftButton.Create(	leftName,
							WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
							CRect (CPoint( 6, 17 ),
							CSize((r.Width()-4)/2, MINIMIZED_WIDGET_HEIGHT )),
							this,
							id1 );
	m_LeftButton.SetCheck( BST_CHECKED );

	m_RightButton.Create(	rightName,
							WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
							CRect (CPoint( 2 + (r.Width()-4)/2, 17 ),
							CSize(((r.Width())/2)-10, MINIMIZED_WIDGET_HEIGHT )),
							this,
							id2 );
}

RadioButton::~RadioButton(void)
{
}

int RadioButton::Draw( int pos )
{
	CRect parRect;
	CRect cliRect;
	GetWindowRect(cliRect);
	GetParent()->GetWindowRect(parRect);
	GetParent()->ScreenToClient(cliRect);

	MoveWindow( 0, pos, parRect.Width(), cliRect.Height());
	m_GroupButton.MoveWindow( 2, 0, parRect.Width()-2, cliRect.Height());
	pos = cliRect.Height();		
	m_RightButton.GetWindowRect( cliRect );
	ScreenToClient( cliRect );
	GetWindowRect(parRect);
	m_RightButton.MoveWindow( parRect.Width()/2, cliRect.top, (parRect.Width() /2)-3, cliRect.Height() );
	return pos;
}

BOOL RadioButton::OnCommand(WPARAM wParam, LPARAM lParam)
{
	m_val = (int)wParam;
	if ( m_eventHandler )
		m_eventHandler->UIEvent( wParam );

	return Widget::OnCommand(wParam, lParam);
}
