#pragma once
#include "stdafx.h"
#include "Widgets/MessageMapTemplate.hpp"
#include "Widgets/Common.h"

/********************************************************************
 *	HoverButton:	A hoverbutton is used as a part of a ScrubberWidget.
 *					When the mouse hovers over a hoverbutton, it 
 *					highlights, indicating that the user may
 *					press the middle mouse button and begin
 *					interacting with the scrubber widget. You should
 *					never need to directly create or mess with a
 *					HoverButton.
 *
 ********************************************************************/
template <class T>
class HoverButton : public CStatic {
public:
	// constructors
	HoverButton(T & var, SCRUB_SPEED speed );
	~HoverButton();
	
	// member methods
	void OnMouseEnter ( UINT nFlags, CPoint point ) ;
    void OnMouseHover ( UINT nFlags, CPoint point ) ;
	T ComputeNewValue( int x_pos );
	void SetTextColor(COLORREF crColor);
	void SetBkColor(COLORREF crColor);
	void SetMin( T min ){ m_minValue = min;}
	void SetMax( T max ){ m_maxValue = max;}
	void SetMinMax( T min, T max ){ m_minValue = min; m_maxValue = max; }
	void MouseMoveProcessEHL ( UINT nFlags, CPoint point );
	void CalcModifier( CPoint point );
	
	// Overrides
	afx_msg void	OnMButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL	OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg BOOL	OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH	CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg void	OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void	OnMouseMove(UINT nFlags, CPoint point);
	afx_msg LRESULT OnMouseLeave_system ( WPARAM wParam, LPARAM lParam );    
	afx_msg void	OnRButtonDown(UINT nFlags, CPoint point);
	
private:
	// member variables
	bool m_flag_mouse_inside ;	// is the mouse directly over the hoverbutton?
	CBrush m_brBkgnd;			// Holds Brush Color for the Static Text
	COLORREF m_crBkColor;		// Holds the Background Color for the Text
	COLORREF m_crTextColor;		// Holds the Color for the Text
	bool m_mButtonPressed;		// is the middle mouse button currently being held down?
	T m_modifier;				// used to scale hoverbutton modifier
	SCRUB_SPEED m_scrubSpeed;	// a multiplier used to modify scrubbing speed
	T & m_HoverVar;				// the value being modified
	CPoint m_oldPos;			// previous position of mouse
	T m_oldValue;				// we store the value in case user changes mind

	T m_maxValue;				// the highest value you can achieve with scrubbing
	T m_minValue;				// the lowest value you can achieve with scrubbing

	DECLARE_MESSAGE_MAP()
	afx_msg void OnNcDestroy();
};

BEGIN_MESSAGE_MAP_FOR_TEMPLATE( T, HoverButton<T>, CStatic)
		ON_WM_MBUTTONDOWN()
		ON_MESSAGE( WM_MOUSELEAVE, OnMouseLeave_system )
		ON_WM_MOUSEMOVE()
		ON_WM_CTLCOLOR_REFLECT()
		//}}AFX_MSG_MAP
		ON_WM_CTLCOLOR()
		ON_WM_MBUTTONUP()
		ON_WM_MOUSEWHEEL()
		ON_WM_ERASEBKGND()
		ON_WM_RBUTTONDOWN()
	
		END_MESSAGE_MAP()


/******************************************************************************
 *	Name:		HoverButton
 *
 *	Info:		HoverButton constructor
 *
 *	Args:		var - the target variable
 *
 *				speed - SLOW_SPEED, REGULAR_SPEED, or FAST_SPEED
 *
 *****************************************************************************/
template <class T>
 HoverButton<T>::HoverButton( T & var, SCRUB_SPEED speed ):m_HoverVar( var ), m_scrubSpeed( speed )
{
	m_crBkColor = ::GetSysColor(COLOR_3DFACE);	// Holds the Background Color for the Text
	m_crTextColor = BLACK;
	m_brBkgnd.CreateSolidBrush(m_crBkColor); // Create the Brush Color for the Background.
	m_mButtonPressed = false;
	m_modifier = 1;
	m_flag_mouse_inside=false;
	m_oldPos = CPoint(0 , 0);
	m_minValue = 0;
	m_maxValue = 0;
	
}

template <class T>
HoverButton<T>::~HoverButton()
{

}

/******************************************************************************
 *	Name:		OnMButtonDown
 *
 *	Info:		Overloaded function is called when the middle mouse button
 *				is pressed. SetCapture is used to keep focus on this 
 *				HoverButton as long as the mouse button is down, even if the
 *				cursor is moved outside the widget.
 *
 *****************************************************************************/
template <class T>
void HoverButton<T>::OnMButtonDown(UINT nFlags, CPoint point)
{
	m_oldValue = m_HoverVar;

	// clamp focus to this widget, and don't let it go until the button come up
	SetCapture();

	// compute a modifier value
	CalcModifier( point );

	CWnd::OnMButtonDown(nFlags, point);
	m_oldPos = point;

	// set a flag to indicate that the button is being pressed
	m_mButtonPressed = true;
}

/******************************************************************************
 *	Name:		CalcModifier
 *
 *	Info:		Uses the position of the mouse to determine which part of the
 *				widget the cursor was over when the button was pressed, and stores
 *				the result in m_modifier.
 *
 *	Args:		point - the position of the cursor in the HoverButton widget.
 *
 *****************************************************************************/
template <class T>
void HoverButton<T>::CalcModifier( CPoint point )
{
	CRect r;
	GetClientRect(r);

	double tempVar = 0;

	tempVar = float(((float)(point.x ))/ (float)r.Width());
	if ( tempVar > 0.66f )
		m_modifier = (T)1;
	else if ( tempVar < 0.33 )
		m_modifier = (T)100;
	else
		m_modifier = (T)10;
}

/******************************************************************************
 *	Name:		OnMButtonUp
 *
 *	Info:		Overloaded function--called when the middle mouse button is
 *				released. ReleaseCapture is called here--SetCapture was called
 *				in OnMButtonDown--which restores focus functionality to normal.
 *
 *****************************************************************************/
template <class T>
void HoverButton<T>::OnMButtonUp(UINT nFlags, CPoint point)
{
	CRect r;
	GetClientRect(r);
	::ReleaseCapture();
	m_mButtonPressed=false;
	if (!r.PtInRect(point))
	{
		SetTextColor(BLACK);
		SetBkColor(::GetSysColor( COLOR_3DFACE ));
	}

	CStatic::OnMButtonUp(nFlags, point);
}

/******************************************************************************
 *	Name:	OnMouseMove
 *
 *	Info:	Modifies the target variable when the user moves the mouse, but
 *			only when the middle mouse button is being held down. Overridden
 *			function.
 *
 *****************************************************************************/
template <class T>
void HoverButton<T>::OnMouseMove(UINT nFlags, CPoint point)
{
	if( m_mButtonPressed == true )
	{
		m_HoverVar = ComputeNewValue( point.x - m_oldPos.x );
		((ScrubberWidget<T> *)GetParent())->Refresh();
	}
	MouseMoveProcessEHL ( nFlags, point ) ;
	CWnd::OnMouseMove(nFlags, point);
	m_oldPos=point;
}

/******************************************************************************
*	Name:	ComputeNew Value
*
*	Info:	Used the scrubbing speed setting and the m_modifier to come up
*			with an adjusted delta value.
*
*	Args:	delta - the distance the user has moved the mouse while scrubbing.
*
*****************************************************************************/
template <class T>
T HoverButton<T>::ComputeNewValue( int delta )
{
		// T newValue = 0;
		double temp = 0;
	
		switch(m_scrubSpeed){
			case( REGULAR_SPEED ):
			{
				temp =  m_HoverVar + ( delta ) * m_modifier;
				break;
			}
			case( SLOW_SPEED ):
			{
				temp = m_HoverVar + (( delta ) * m_modifier/10);
				break;
			}
			case( VERY_SLOW_SPEED ):
				 {
					 temp = m_HoverVar + (( delta ) * m_modifier/100);
					 break;
				 }
		}
		if ( m_minValue != m_maxValue )
		{
			if ( temp > m_maxValue )
			{
				temp = m_maxValue;
			}
			else if (  temp < m_minValue )
			{
				temp = m_minValue;
			}
		}
		return T(temp);
}

/******************************************************************************
 *	Name:	MouseMoveProcessEHL
 *
 *	Info:	Sets a flag to show that the cursor has entered the window, and 
 *			calls _TrackMouseEvent, which posts messages when the cursor
 *			hovers over or leaves the window.
 *
 ****************************************************************************/
template< class T >
void HoverButton<T>::MouseMoveProcessEHL ( UINT nFlags, CPoint point ) 
{
	//  CHECK FOR A NEW ENTRANCE OF THE CURSOR
    if ( ! m_flag_mouse_inside ) {
 		TRACKMOUSEEVENT tme ;

        tme.cbSize    = sizeof ( TRACKMOUSEEVENT ) ;
        tme.dwFlags   = TME_LEAVE ;
        tme.hwndTrack = m_hWnd ;
		
        _TrackMouseEvent ( & tme ) ;

        m_flag_mouse_inside = true ;
        //  "GENERATE" A MOUSE-ENTER EVENT
        OnMouseEnter( nFlags, point ) ;

    }
}

/******************************************************************************
 *	Name:	OnMouseLeave_system
 *
 *	Info:	This function is called automatically when a WM_MOUSELEAVE event is 
 *			detected. It just sets the colors back to normal and sets a flag.
 *
 *****************************************************************************/
template <class T>
LRESULT HoverButton<T>::OnMouseLeave_system ( WPARAM /* wParam */, LPARAM /* lParam */ )
{
    m_flag_mouse_inside = false ;
	if (!m_mButtonPressed){
		SetTextColor(BLACK);
		SetBkColor(::GetSysColor(COLOR_3DFACE));
	}
    return TRUE;
}

/******************************************************************************
 *	Name:		OnMouseEnter
 *
 *	Info:		Overridden function--gets called automatically when the cursor 
 *				moves into the HoverButton window. Changes the colors to make 
 *				it clear to the user that he may interact with the widget.
 *
 *****************************************************************************/
template <class T>
void HoverButton<T>::OnMouseEnter ( UINT /* nFlags */, CPoint /* point */ ) 
{
	SetFocus();
	SetTextColor(::GetSysColor(COLOR_3DFACE));
	SetBkColor(BLACK);
}

/******************************************************************************
 *	Name:		OnMouseHover
 *
 *	Info:		Currently does nothing, but eventually may want to put tooltips
 *				code here.
 *
 *****************************************************************************/
template <class T>
void HoverButton<T>::OnMouseHover ( UINT nFlags, CPoint point ) 
{

}

/*****************************************************************************
 *	Name:		CtlColor
 *
 *	Info:		Handles the actual color changing of the HoverButton. 
 *				Overridden function.
 *
 *****************************************************************************/
template <class T>
HBRUSH HoverButton<T>::CtlColor(CDC* pDC, UINT nCtlColor) 
{	
	HBRUSH hbr;
	hbr = (HBRUSH)m_brBkgnd;			// Passing a Handle to the Brush
	pDC->SetBkColor(m_crBkColor);		// Setting the Color of the Text Background
	pDC->SetTextColor(m_crTextColor);	// Setting the Text Color
	
	if (nCtlColor)						// To get rid of compiler warning
      nCtlColor += 0;

	return hbr;
}

/******************************************************************************
 *	Name:		SetBkColor
 *
 *	Info:		Sets the background color of the HoverButton widget.
 *
 *	Args:		crColor = the color to use.
 *
 *****************************************************************************/
template <class T>
void HoverButton<T>::SetBkColor(COLORREF crColor)
{
	// Passing the value passed by the dialog to the member variable for Backgound Color
	m_crBkColor = crColor;

	// Deleting any Previous Brush Colors if any existed.
	m_brBkgnd.DeleteObject();				

	// Creating the Brush Color For the Static Text Background
	m_brBkgnd.CreateSolidBrush(crColor);	
	RedrawWindow();
}

/******************************************************************************
 *	Name:		SetTextColor
 *
 *	Info:		Sets the text color for HoverButton.
 *
 *	Args:		crColor - the color to use
 *
 *****************************************************************************/
template <class T>
void HoverButton<T>::SetTextColor(COLORREF crColor)
{	
	// Passing the value passed by the dialog to the member variable for Text Color
	m_crTextColor = crColor; 
}

/******************************************************************************
 *	Name:		OnMouseWheel
 *
 *	Info:		When the user spins the mouse wheel, the target variable
 *				is modified, just as if he were "scrubbing" with the mouse.
 *				Overridden function.
 *
 *****************************************************************************/
template <class T>
BOOL HoverButton<T>::OnMouseWheel(UINT /* nFlags */, short zDelta, CPoint pt)
{
	CRect clientRect;
	GetWindowRect(clientRect);
	CPoint cliPoint;
	cliPoint.x = pt.x - clientRect.left;
	cliPoint.y = pt.y - clientRect.top;

	CalcModifier( cliPoint );
	
	if ( m_flag_mouse_inside )
	{
		m_HoverVar = ComputeNewValue( (zDelta < 0) ? -1 : 1 );
		// refresh the scrubber widget
		((ScrubberWidget<T> *)GetParent())->Refresh();
	}

	return true;
}

/******************************************************************************
 *	Name:		OnEraseBkgnd
 *
 *	Info:		Overridden function... returning true is supposed to help
 *				eliminate flicker, but I'm not sure it's really necessary.
 *
 *****************************************************************************/
template <class T>
BOOL HoverButton<T>::OnEraseBkgnd(CDC* /* pDC */ )
{
	return true;
}

/******************************************************************************
*	Name:		OnRButtonDown
*
*	Info:		Overloaded function called when the right mouse button is
*				pressed. If the middle mouse button is currently being pressed,
*				ie. the user is in mid-scrub, then restore the target value
*				to what it was before he began scrubbing.
*
*****************************************************************************/
template <class T>
void HoverButton<T>::OnRButtonDown(UINT nFlags, CPoint point)
{
	if ( m_mButtonPressed )
	{
		m_HoverVar = m_oldValue;
	}	
	// refresh the scrubber widget
	((ScrubberWidget<T> *)GetParent())->Refresh();

	CStatic::OnRButtonDown(nFlags, point);
}

/******************************************************************************
*	Name:		OnNcDestroy
*
*	Info:		By overriding OnNcDestroy, we ensure that the components of our 
*				CWnd-derived class will be destroyed when Windows automatically 
*				destroys the CWnd.
*
*****************************************************************************/
template<typename T>
void HoverButton<T>::OnNcDestroy()
{
	CStatic::OnNcDestroy();
	delete this;
}