#pragma once
#include "afxwin.h"
#include "Widgets/Widget.h"
#include "Widgets/Common.h"
#include "Widgets/TemplateToString.h"

/********************************************************************
*	Watcher:	Watcher widgets are passive--they simply display the 
*				current value of a single variable. They are useful
*				for keeping an eye on general values as your program
*				runs, such as polys per frame, time to draw a frame,
*				etc. By default this widget only updates every 10 
*				frames (so it's a little easier to read), but you can
*				change this value with SetUpdateInterval().
*
*******************************************************************/
template <class T>
class Watcher: public Widget
{
public:
	Watcher( int & watch);
	Watcher( float & watch);
	~Watcher(void);
	void Create( CString label, CRect r, CWnd* pWin );
	int Draw( int pos );
	void Update();
	void SetUpdateInterval( int updInt ){ m_updateInterval = updInt; }

private:
	CStatic	m_label;
	CStatic m_watch;
	T & m_val;
	int m_frameCount;		// frame counter
	int	m_updateInterval;	// update every this many frames
};

template <class T>
Watcher<T>::Watcher( float & watch ):m_val( watch )
{
	m_updateInterval = 10;
	m_frameCount = 0;
}

template <class T>
Watcher<T>::Watcher( int & watch ):m_val( watch )
{
	m_updateInterval = 10;
	m_frameCount = 0;
}

template <class T>
Watcher<T>::~Watcher(void)
{
}

template <class T>
void Watcher<T>::Create( CString label, CRect rect, CWnd * pWin )
{
	CWnd::Create(	NULL,
		NULL,
		WS_VISIBLE | WS_CHILD,
		rect,
		pWin,
		IDC_WIDGET_WATCHER);

	m_label.Create( label, 
		WS_VISIBLE | WS_CHILD,
		CRect( CPoint(10,0), CSize(100, MINIMIZED_WIDGET_HEIGHT)),
		this
		);

	char buffer[16];

	_gcvt( m_val, 8, buffer );

	CRect r;
	GetClientRect(r);
	m_watch.Create( buffer,
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		CRect( CPoint(100, 0), CSize( r.Width()-105, 23 )),
		this
		);
}

template <class T>
void Watcher<T>::Update()
{
	m_frameCount++;
	if ((m_frameCount % m_updateInterval)==0)
	{
		m_frameCount = 0;
		TemplateToString<T> val;
		val.Inst = m_val;

		m_watch.SetWindowText(val.EchoType());	
	}
}

template<class T>
int Watcher<T>::Draw( int pos )
{
	CRect wbRect;
	CRect cliRect;
	GetWindowRect(cliRect);
	GetParent()->GetWindowRect(wbRect);
	GetParent()->ScreenToClient(cliRect);
	int width = int(wbRect.Width() * WIDGET_SCRUBBER_HOVER_WIDTH);

	MoveWindow( 0, pos, wbRect.Width(), cliRect.Height() );
	m_label.MoveWindow(0,0, width, MINIMIZED_WIDGET_HEIGHT );
	m_watch.MoveWindow(width, 0, wbRect.Width()-width - WIDGET_SCRUBBER_RIGHT_MARGIN, MINIMIZED_WIDGET_HEIGHT - 5);
	pos = cliRect.Height();
	return pos;
}