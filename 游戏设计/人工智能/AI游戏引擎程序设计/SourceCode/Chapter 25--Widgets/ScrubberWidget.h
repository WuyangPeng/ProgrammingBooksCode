#pragma once
#include "stdafx.h"
#include "Widgets/HoverButton.h"
#include "Widgets/MessageMapTemplate.hpp"
#include "Widgets/TemplateToString.h"
#include "Widgets/Common.h"
#include "Widgets/Widget.h"

/********************************************************************
 *	ScrubberWidget:		A ScrubberWidget is made up of two other widgets, a
 *						HoverButton, and a CEdit (MFC) control. 
 *						manipulating the HoverButton, the user may
 *						modify the value displayed in the CEdit control,
 *						and the value to which the ScrubberWidget is bound.
 *
 *******************************************************************/
template <class T>
class ScrubberWidget : public Widget {
public:
	// constructors
	ScrubberWidget(T & var );
	~ScrubberWidget();

	// member methods
	void Refresh();
	int  Draw( int pos );
	void OnEditKillFocus();
	void Create( char * label, CWnd* pWin, int pos, SCRUB_SPEED speed = REGULAR_SPEED );
	void SetMin( T min ){ myHoverButton->m_minValue = min; }
	void SetMax( T max ){ myHoverButton->m_maxValue = max; }
	void SetMinMax( T min, T max ){ m_hoverButton->SetMinMax( min, max ); }

	// Overrides
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

	// member variables
	CEdit m_edit;
	HoverButton<T> * m_hoverButton;

	T &m_scrubVar;				// the value being changed
	
	DECLARE_MESSAGE_MAP()
	afx_msg void OnNcDestroy();
};

// ScrubberWidget
BEGIN_MESSAGE_MAP_FOR_TEMPLATE(T, ScrubberWidget<T>, CWnd)
ON_WM_CTLCOLOR()
ON_WM_ERASEBKGND()
ON_EN_KILLFOCUS( IDC_WIDGET_SCRUBBER_EDIT, OnEditKillFocus)
END_MESSAGE_MAP()

/******************************************************************************
*	Name:		ScrubberWidget
*
*	Info:		ScrubberWidget constructor.
*
*	Args:		var - the target variable.
*
*****************************************************************************/
template <class T>
ScrubberWidget<T>::ScrubberWidget(T & var ):m_scrubVar(var){
}
/******************************************************************************
*	Name:		~ScrubberWidget
*
*	Info:		ScrubberWidget destructor.
*
*****************************************************************************/
template <class T>
ScrubberWidget<T>::~ScrubberWidget()
{
	if ( m_hoverButton )
        delete m_hoverButton;
}

/******************************************************************************
*	Name:		Create
*
*	Info:		Fills in the ScrubberWidget widget with its subwidgets.
*
*	Args:		label - will become the caption on the HoverButton
*
*				pWin - a pointer to the parent window
*
*				pos - the position in the parent window where this should be
*				drawn.
*
*				speed - a power of modifier that will change the scrubbing
*				magnitude.
*
*****************************************************************************/
template <class T>
void ScrubberWidget<T>::Create( char * label, CWnd* pWin, int pos, SCRUB_SPEED speed ){
	CRect r;
	CString str;
	TemplateToString<T> t;
	pWin->GetClientRect(r);
	CWnd::Create(	NULL,
					NULL,
					WS_CHILD | WS_VISIBLE,
					CRect(CPoint(0, pos),CSize(r.Width(), MINIMIZED_WIDGET_HEIGHT )),
					pWin,
					IDC_WIDGET_SCRUBBER);

    m_hoverButton = new HoverButton<T>( m_scrubVar, speed );
	str.Format("    %s", label );		
	m_hoverButton->Create(	str,
		WS_VISIBLE | WS_CHILD | SS_ENDELLIPSIS | SS_LEFT | SS_NOTIFY, 
		CRect(CPoint(0,0), CSize(0, WIDGET_SCRUBBER_HEIGHT)),
		this,
		IDC_WIDGET_SCRUBBER_BUTTON );

	m_edit.CreateEx( 
		WS_EX_CLIENTEDGE,
		"edit",
		NULL,
		WS_CHILD | WS_VISIBLE | WS_TABSTOP,
		CRect(	CPoint(0, 0), 
		CSize(r.Width() 
		-WIDGET_SCRUBBER_RIGHT_MARGIN, WIDGET_SCRUBBER_HEIGHT )),
		this, 
		IDC_WIDGET_SCRUBBER_EDIT);

	t.Inst = m_scrubVar;
	str.Format("%s", t.EchoType());
	m_edit.SetWindowText(str);
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
template <class T>
int ScrubberWidget<T>::Draw( int pos )
{
	CRect wbRect;
	CRect cliRect;
	GetWindowRect(cliRect);
	GetParent()->GetWindowRect(wbRect);
	GetParent()->ScreenToClient(cliRect);
	int width = int(wbRect.Width() * WIDGET_SCRUBBER_HOVER_WIDTH);
	
	MoveWindow( 0, pos, wbRect.Width(), cliRect.Height() );
	m_hoverButton->MoveWindow(0,0, width, MINIMIZED_WIDGET_HEIGHT );
	m_edit.MoveWindow(width, 0, wbRect.Width()-width - WIDGET_SCRUBBER_RIGHT_MARGIN, MINIMIZED_WIDGET_HEIGHT );

	pos = cliRect.Height();
	return pos;
}
/******************************************************************************
*	Name:		Refresh
*
*	Info:		Sets the string displayed in myEdit to the value contained in
*				the target variable.
*
*****************************************************************************/
template <class T>
void ScrubberWidget<T>::Refresh()
{
	if ( GetFocus() == &m_edit )
		return;

	TemplateToString<T> val;
	val.Inst = m_scrubVar;

	m_edit.SetWindowText(val.EchoType());
}

/******************************************************************************
*	Name:		OnEditKillFocus
*
*	Info:		If the user moves the mouse out of the edit box, then the
*				target variable becomes updated with whatever value is in the
*				edit box when it moves out.
*
*****************************************************************************/
template <class T>
void ScrubberWidget<T>::OnEditKillFocus() 
{	CString str;
	m_edit.GetWindowText(str);
	m_scrubVar = (T)atof(str);
}

/******************************************************************************
*	Name:		OnEraseBkgnd
*
*	Info:		Overridden function... returning true is supposed to help
*				eliminate flicker, but I'm not sure it's really necessary.
*
*****************************************************************************/
template <class T>
BOOL ScrubberWidget<T>::OnEraseBkgnd(CDC* /* pDC */ )
{
	return true;
}

/******************************************************************************
*	Name:		OnNcDestroy
*
*	Info:		By overriding this function and deleting this, we ensure that
*				our class gets destroyed when Windows destroys the window that
*				this class is derived from.
******************************************************************************/
template<typename T>
void ScrubberWidget<T>::OnNcDestroy()
{
	CWnd::OnNcDestroy();
	delete this;
}
