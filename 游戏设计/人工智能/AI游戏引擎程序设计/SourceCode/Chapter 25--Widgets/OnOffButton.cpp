#pragma once
#include "stdafx.h"
#include "Widgets/OnOffButton.h"
#include "Widgets/EventHandler.h"
#include ".\onoffbutton.h"

// OnOffButton
BEGIN_MESSAGE_MAP(OnOffButton, Widget)
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

/******************************************************************************
 *	Name:		OnOffButton
 *
 *	Info:		OnOffButton constructor.
 *
 *	Args:		state - the target variable.
 *
 *****************************************************************************/
OnOffButton::OnOffButton( bool & state, EventHandler * eventHandler ):myState( state ){

	m_eventHandler = eventHandler;
}

BOOL OnOffButton::OnCommand(WPARAM wParam, LPARAM lParam)
{
	if (m_eventHandler)
	{
		m_eventHandler->UIEvent(wParam );
	}
	return Widget::OnCommand(wParam, lParam);
}

void OnOffButton::SetStyle( int style )
{
	m_button.SetButtonStyle( style );
}

void OnOffButton::SetCheck( bool checked )
{
	m_button.SetCheck( checked );
}

int OnOffButton::GetCheck()
{
	m_button.GetCheck();

	return (m_button.GetCheck() ? 1 : 0 );
}

/******************************************************************************
*	Name:	Draw
*
*	Info:	Repositions and resizes this widget appropriately.
*
*	Args:	y_pos - where to draw this widget in the parent widget.
*
*	Return:	the vertical position of the bottom of this widget, in the parent 
*			widget.
*
*****************************************************************************/
int OnOffButton::Draw( int pos )
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
