#pragma once
#include "afxwin.h"
#include "Widgets/Widget.h"
#include "Widgets/EventHandler.h"

/********************************************************************
*	RadioButton:	This basic radio button class only supports radio
*					buttons with two choices. 
*
*	TODO:			Eventually it should be able to support any 
*					number of choices.
*
*******************************************************************/
class RadioButton :	public Widget
{
public:
	// constructors
	RadioButton( char * groupName, char * leftName, 
		char * rightName, int & val, 
		CWnd * pWin, int yPos,
		int id1=0, int id2=0,
		EventHandler * h=0 );
	~RadioButton(void);
	int Draw( int pos );

protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);

private:
	// member variables
	CButton m_GroupButton;
	CButton m_LeftButton;
	CButton m_RightButton;

	int & m_val;

	EventHandler * m_eventHandler;
};
