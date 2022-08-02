#include "StdAfx.h"
#include ".\text.h"

Text::Text(void)
{
}

Text::~Text(void)
{
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
int Text::Draw( int pos )
{
	CRect parRect;
	CRect cliRect;
	GetWindowRect(cliRect);
	GetParent()->GetWindowRect(parRect);
	GetParent()->ScreenToClient(cliRect);

	MoveWindow( 4, pos, parRect.Width()-4, cliRect.Height());
	m_text.MoveWindow( 0, 0, parRect.Width(), cliRect.Height());
	pos = cliRect.Height();
	return pos;
}