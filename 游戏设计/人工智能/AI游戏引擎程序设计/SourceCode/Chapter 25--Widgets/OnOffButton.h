#pragma once
#include "stdafx.h"
#include "Widgets/EventHandler.h"
#include "Widgets/Widget.h"

/********************************************************************
 *	OnOffButton:	A widget used to toggle boolean states. By default
 *					it looks like a checkbox, but you can switch to
 *					a pushbutton-styled widget by passing BS_PUSHLIKE
 *					to SetStyle after the widget has been created.
 *
 *******************************************************************/
class OnOffButton : public Widget {
public:
	// constructors
	OnOffButton( bool & state, EventHandler * eventHandler = 0 );
	
	// member methods
	void SetStyle( int style );
	void SetCheck( bool checked );
	int GetCheck();
	int Draw( int pos );
	CButton m_button;

	DECLARE_MESSAGE_MAP()
protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);

private:
	// member variables
	bool & myState;

	EventHandler * m_eventHandler;
};