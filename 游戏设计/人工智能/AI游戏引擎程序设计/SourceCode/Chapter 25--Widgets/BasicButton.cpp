#include "StdAfx.h"
#include "Widgets/Common.h"
#include "Widgets/BasicButton.h"
#include "Widgets/EventHandler.h"

//#ifdef _DEBUG
//#define new DEBUG_NEW
//#endif

BEGIN_MESSAGE_MAP( BasicButton, CWnd )
END_MESSAGE_MAP( )

/******************************************************************************
*	Name:		BasicButton
*
*	Info:		BasicButton constructor.
*
*	Args:		eventHandler - the eventHandler that will provide functionality
*				to this button.
*
*****************************************************************************/
BasicButton::BasicButton( EventHandler * eventHandler )
{
	m_eventHandler = eventHandler;
}

BasicButton::~BasicButton(void)
{
}

/******************************************************************************
*	Name:		Create
*
*	Info:		Creates this widget window, and it's component windows.
*
*	Args:		label - the caption that will appear on this BasicButton.
*				
*				id - the enum "name" of this widget. Make it something descriptive,
*				like START_GAME_BUTTON, or DRAW_SHADOWS, etc.
*
*				pWin - the window that will be a parent to this widget.
*
*				pos - the vertical height--relative to the parent window--of 
*				this widget.
*
*****************************************************************************/
void BasicButton::Create( char * label, int id, CWnd* pWin, int pos )
{
	CRect r;
	pWin->GetClientRect(r);
	CWnd::Create(	NULL,
					NULL,
					WS_CHILD | WS_VISIBLE,
					CRect(CPoint(0, pos), CSize(r.Width(), MINIMIZED_WIDGET_HEIGHT )),
					pWin,
					IDC_BASIC_BUTTON );
	r.bottom = MINIMIZED_WIDGET_HEIGHT;
	m_button.Create( label, 
						WS_VISIBLE | WS_CHILD,  
						CRect(CPoint(10, 0),CSize(r.Width()-15, MINIMIZED_WIDGET_HEIGHT )),
						this,
						id );
}
/******************************************************************************
*	Name:		OnCommand
*
*	Info:		Overridden MFC event--you never call this directly.
*				Here we call UIEvent and pass it the id
*				(which is stored in wParam) of the button that was pressed. You 
*				can then switch on this value in your own UIEvent function to
*				call the correct code.
*
*****************************************************************************/
BOOL BasicButton::OnCommand(WPARAM wParam, LPARAM lParam)
{
	if (m_eventHandler)
		m_eventHandler->UIEvent( wParam );
	return Widget::OnCommand(wParam, lParam);
}

/******************************************************************************
*	Name:		Draw
*
*	Info:		For repositioning and sizing this widget whenever the user
*				clicks on a widget header.
*
*	Args:		pos - the vertical height--relative to the parent window--at
*				which to draw this widget.
*
*****************************************************************************/
int BasicButton::Draw( int pos )
{
	CRect parRect;
	CRect cliRect;
	GetWindowRect(cliRect);
	GetParent()->GetWindowRect(parRect);
	GetParent()->ScreenToClient(cliRect);

	MoveWindow( 0, pos, parRect.Width(), cliRect.Height());
	m_button.MoveWindow( 8, 0, parRect.Width()-16, cliRect.Height());

	pos = cliRect.Height();
	return pos;
}