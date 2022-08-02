#pragma once
#include "stdafx.h"

#include "Widgets/Group.h"
#include "Widgets/ScrubberWidget.h"
#include "Widgets/BasicButton.h"
#include "Widgets/OnOffButton.h"
#include "Widgets/WidgetBank.h"
#include "Widgets/Widget.h"
#include "Widgets/RadioButton.h"
#include "Widgets/Watcher.h"
#include "Widgets/Text.h"

BEGIN_MESSAGE_MAP(Group, CWnd)
	ON_BN_CLICKED (IDC_WIDGET_HEADER, OnClickHeader )
	ON_WM_ERASEBKGND()
	ON_WM_NCDESTROY()
END_MESSAGE_MAP()
/******************************************************************************
*	Name:		Group
*
*	Info:		Group Constructor.
*
*	Args:		label - this string will appear on the header Group.
*
*				pWin - pointer to the parent window
*
*				level - the level of tabbing to use when printing the caption.
*
*****************************************************************************/
Group::Group( char * label, CWnd * pWin, const int level  ){
	CRect r;
	m_level = level;
	m_color = ::GetSysColor(COLOR_3DFACE);
	pWin->GetWindowRect(r);
	char newLabel[64]={' '};
	char buffer[64];

	sprintf(newLabel, "%s", label);
	for ( int i = 0; i < level; i++ )
	{
		sprintf( buffer, "   %s", newLabel );
		strcpy( newLabel, buffer );
	}

	m_status = false;
	m_numChildGroups = 0;
	m_numChildWidgets = 0;
	m_widgetBank = 0;
	for (i = 0; i < MAX_CHILD_GROUPS; i++ )
	{
		m_childGroups[i] = 0;
	}

	Create(	NULL, NULL, WS_CHILD | WS_VISIBLE,
		CRect(CPoint(0, r.Height()), 
		CSize( r.Width(), MINIMIZED_WIDGET_HEIGHT )), 
		pWin, 
		IDC_WIDGET );

	m_header.Create(	newLabel, 
		WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_LEFT | BS_PUSHLIKE, 
		CRect(CPoint(0, 0),	CSize(r.Width(), MINIMIZED_WIDGET_HEIGHT )), 
		this, 
		IDC_WIDGET_HEADER);
}

Group::~Group()
{
	for (unsigned i = 0; i < m_numChildWidgets; i++ )
	{
		delete m_childWidgets[i];
		m_childWidgets[i] = 0;
	}
}


/******************************************************************************
*	Name:	GetHeight
*
*	Info:	Computes the height of this group. If the widget is currently 
*			minimized (ie. not expanded), then it just returns the height of a 
*			minimized widget.
*
*	Return:	The current height of this widget
*
*****************************************************************************/
int Group::GetHeight()
{
	int height = MINIMIZED_WIDGET_HEIGHT;
	if ( IsExpanded() == true )
	{
		height += GetClientHeight();
	}

	return height;
}

/******************************************************************************
*	Name:	GetClientHeight
*
*	Info:	Computes the client height of this widget by computing the sum of the 
*			height of any child groups or widgets.
*
*	Return:	The current height of this widget
*
*****************************************************************************/
int Group::GetClientHeight()
{
	CRect r;
	int height = 0;
	for ( unsigned int i = 0; i < m_numChildWidgets; i++ )
	{
		m_childWidgets[i]->GetWindowRect(r);
		height += r.Height();
	}
	for ( i = 0; i < m_numChildGroups; i++ )
	{
		height += ((Group *)m_childGroups[i])->GetHeight();
	}
	return height;
}

/******************************************************************************
*	Name:	AddGroup
*
*	Info:	Add a group widget (to this group widget).
*
*	Args:	label - the caption for this group widget
*
*	Return:	A pointer to the group widget that was just created.
*
*****************************************************************************/
Group* Group::AddGroup( char * label )
{
	Group * w;
	CRect r;
	GetParent()->GetWindowRect(r);

	w = m_childGroups[m_numChildGroups++] = new Group(	label, 
		(CWnd*)this,
		m_level + 1 );
	
	w->SetWidgetBank( m_widgetBank );

	return w;
}

ScrubberWidget<float> * Group::AddScrubber( char * name, float & val )
{
	ScrubberWidget<float> * sw;
	m_childWidgets[m_numChildWidgets++] = sw = new ScrubberWidget<float>( val );
	sw->Create(	name, 
				this, 
				GetClientHeight()+ MINIMIZED_WIDGET_HEIGHT, 
				VERY_SLOW_SPEED );
	return sw;
}

ScrubberWidget<int> * Group::AddScrubber( char * name, int & val )
{
	ScrubberWidget<int> * sw;
	m_childWidgets[m_numChildWidgets++] = sw = new ScrubberWidget<int>( val );
	sw->Create(	name, 
				this, 
				GetClientHeight() + MINIMIZED_WIDGET_HEIGHT );
	return sw;
}

ScrubberWidget<unsigned char> * Group::AddScrubber( char * name, unsigned char & val )
{
	ScrubberWidget<unsigned char> * sw;
	m_childWidgets[m_numChildWidgets] = sw = new ScrubberWidget<unsigned char>( val );
	sw->Create(	name, 
		this, 
		GetClientHeight() + MINIMIZED_WIDGET_HEIGHT);
	m_numChildWidgets++;
	return sw;
}

OnOffButton * Group::AddOnOff( char * leftName, bool & a,  
					 int ID1, EventHandler * h )
{
	CRect r;
	GetClientRect(r);
	r.bottom = MINIMIZED_WIDGET_HEIGHT;
	r.top = GetClientHeight() + MINIMIZED_WIDGET_HEIGHT;

	OnOffButton * oob;

	m_childWidgets[m_numChildWidgets++] = oob = new OnOffButton( a, h );
	
	oob->Create(	NULL,
					NULL,
					WS_CHILD | WS_VISIBLE,
					r,
					this,
					IDC_WIDGET_ON_OFF
                    );

	oob->m_button.Create( leftName, 
		WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, 
		CRect(
		CPoint( 10, 0),
		CSize( r.Width(), MINIMIZED_WIDGET_HEIGHT )
		),
		oob,
		ID1 );

	return oob;
}

RadioButton * Group::AddRadio( char * groupName, char * leftName, 
							  char * rightName, int & val, int id1, 
							  int id2, EventHandler * h )
{
	RadioButton * rb;
	m_childWidgets[m_numChildWidgets] = rb = new RadioButton(	groupName, leftName, rightName,
		val, this,
		GetClientHeight() + MINIMIZED_WIDGET_HEIGHT,
		id1,
		id2,
		h );
	m_numChildWidgets++;
	return rb;
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
int Group::Draw( int y_pos )
{
	CRect r, r2, hRect;
	m_widgetBank->GetClientRect(r2);
	GetWindowRect(r);
	int height = GetHeight();

	m_header.GetClientRect(hRect);
	m_header.MoveWindow( hRect.left, hRect.top, r2.Width(), MINIMIZED_WIDGET_HEIGHT );

	MoveWindow( 0, y_pos, r2.Width(), height, true );
	if (IsExpanded()){
		y_pos = MINIMIZED_WIDGET_HEIGHT;
		for ( unsigned int i = 0; i < m_numChildGroups; i++ )
		{
			y_pos += ((Group *)m_childGroups[i])->Draw( y_pos );
		}
		for ( i = 0; i < m_numChildWidgets; i++)
		{
			y_pos += m_childWidgets[i]->Draw( y_pos );
		}
	}
	return height;
}

/******************************************************************************
*	Name:		OnClickHeader
*
*	Info:		When the user clicks on a widget header, the widget will 
*				expand vertically to show its contents. This function handles
*				resizing the widget's window and updating the client height.
*
*****************************************************************************/
void Group::OnClickHeader(){

	CRect wbRect, wbCliRect;

	// get a pointer to the widget bank window
	WidgetBank * wb = (WidgetBank*)m_widgetBank;

	// get the size and position of the widget bank window
	wb->GetWindowRect(wbRect);		

	// get the size and position of the client area
	wb->GetClientRect(wbCliRect);	

	// calculate the vertical space taken up by borders
	int borderHeight = wbRect.Height() - wbCliRect.Height(); 

	// set the status (am I open?) flag
	IsExpanded() ? m_status = false : m_status = true;

	// get the new client height
	int clientHeight = wb->GetHeight();

	// compute a new height for the widget bank
	int wbHeight = clientHeight + borderHeight;

	// clamp the widget bank height if necessary
	if ( wbHeight > MAX_WIDGET_BANK_HEIGHT )
	{
		wbHeight = MAX_WIDGET_BANK_HEIGHT;
	}

	wb->m_ClientSize = CRect( CPoint(0,0), CPoint(wbCliRect.Width(), clientHeight));

	// resize the widgetbank
	m_widgetBank->MoveWindow( wbRect.left, wbRect.top, wbRect.Width(), wbHeight);
	m_widgetBank->OnSize( SIZE_RESTORED, wbRect.Width(), clientHeight + MINIMIZED_WIDGET_HEIGHT);
	// Redraw all the widgets
	wb->Draw();
}

/******************************************************************************
*	Name:		OnEraseBkgnd
*
*	Info:		Overridden function... returning true is supposed to help
*				eliminate flicker, but I'm not sure it's really necessary.
*
*****************************************************************************/
BOOL Group::OnEraseBkgnd(CDC* pDC)
{
	CRect rect;
	GetClientRect(&rect);
	CBrush brush( m_color );

	pDC->SelectObject(brush);
	pDC->PatBlt( rect.left, rect.top, rect.Width(), rect.Height(), PATCOPY );

	return true;
}

/******************************************************************************
*	Name:		AddBasicButton
*
*	Info:		Add a simple button to this group. BasicButtons don't monitor
*				or alter any values or do anything on their own--they must be 
*				associated with an EventHandler object.
*
*	Args:		caption - the label for this button
*
*				id - this should be a descriptive enum that denotes what this
*				button does. When UIEvent in EventHandler is called, this id
*				will be passed along, and then used in a switch statement to 
*				invoke the correct functionality. For example, you might pass 
*				in something like FILE_OPEN, START_ANIM, or DRAW_WIREFRAME to 
*				identify your button.
*
*				h - The Event Handler that will receive the id of this button
*				when it is pressed.
*****************************************************************************/
BasicButton * Group::AddBasicButton( char * caption, int id, EventHandler * h )
{
	BasicButton * bb;
	m_childWidgets[m_numChildWidgets] = bb = new BasicButton( h );

	bb->Create(	caption, 
				id,
				this, 
				GetClientHeight() + MINIMIZED_WIDGET_HEIGHT );
	m_numChildWidgets++;
	return bb;
}

/******************************************************************************
*	Name:		AddWatcher
*
*	Info:		Add a Watcher widget to this group. Watchers don't accept any
*				input, but do display the value of a changing variable. 
*
*	Args:		caption - the label for this button
*
*				val - the float to watch.
*****************************************************************************/
void Group::AddWatcher( char * caption, float & val )
{
	CRect r;
	GetClientRect(r);
	r.top = GetClientHeight() + MINIMIZED_WIDGET_HEIGHT;
	r.bottom = r.top + MINIMIZED_WIDGET_HEIGHT;

	Watcher<float> * w;
	m_childWidgets[m_numChildWidgets++] = w = new Watcher<float>( val );
	w->Create(	caption,
		r,
		this);
}

/******************************************************************************
*	Name:		AddWatcher
*
*	Info:		Add a Watcher widget to this group. Watchers don't accept any
*				input, but do display the value of a changing variable. 
*
*	Args:		caption - the label for this button
*
*				val - the int to watch.
*****************************************************************************/
void Group::AddWatcher( char * caption, int & val )
{
	CRect r;
	GetClientRect(r);
	r.top = GetClientHeight() + MINIMIZED_WIDGET_HEIGHT;
	r.bottom = r.top + MINIMIZED_WIDGET_HEIGHT;
	Watcher<int> * w;
	m_childWidgets[m_numChildWidgets++] = w = new Watcher<int>( val );
	w->Create(	caption,
		r,
		this);
}

/******************************************************************************
*	Name:		AddText
*
*	Info:		Add a text widget to this group. Text widgets aren't interactive
*				in any way, but can be used to label sections of your widget bank
*				for the sake of clarity.
*
*	Args:		caption - the label for this Text widget
*****************************************************************************/
void Group::AddText( char * caption )
{
	CRect r;
	GetClientRect(r);
	r.top = GetClientHeight() + MINIMIZED_WIDGET_HEIGHT;
	r.bottom = r.top + MINIMIZED_WIDGET_HEIGHT;
	Text * t;
	m_childWidgets[m_numChildWidgets++] = t = new Text();
	t->Create( NULL, 
			NULL,
			WS_VISIBLE | WS_CHILD,
			r,
			this,
			NULL );
	t->m_text.Create( caption, 
		WS_CHILD | WS_VISIBLE, 
		CRect(
		CPoint( 10, 0 ),
		CSize( r.Width(), MINIMIZED_WIDGET_HEIGHT )
		),
		t,
		NULL );
}

void Group::OnNcDestroy()
{
	CWnd::OnNcDestroy();
	delete this;
}

/******************************************************************************
*	Name:	Update
*
*	Info:	Update all of this Group's child groups and child widgets.
*
*****************************************************************************/
void Group::Update()
{
	for (unsigned int i = 0; i < m_numChildGroups; i++)
	{
		m_childGroups[i]->Update();
	}

	for ( i = 0; i < m_numChildWidgets; i++)
	{
		m_childWidgets[i]->Update();
	}
}

