#pragma once
#include "afxwin.h"
#include "afxdlgs.h"
#include "Widgets/Widget.h"
#include "Widgets/Eventhandler.h"

/********************************************************************
*	BasicButton:A BasicButton is a single button that is almost as
*				wide as the widget bank itself. It doesn't have
*				on and off states--it's just there, waiting to be
*				be pressed. You must provide an event handler if
*				you want anything to happen when the button is pressed.
*
********************************************************************/
class BasicButton : public Widget
{
public:
	// constructors
	BasicButton( EventHandler * eventHandler = 0 ); 
	~BasicButton(void);
	void Create( char * label, int id, CWnd* pWin, int pos );
	int Draw( int pos );
	EventHandler * m_eventHandler;

	DECLARE_MESSAGE_MAP()
protected:
	// member methods
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);

private:
	// member variables
	CButton m_button;
};
