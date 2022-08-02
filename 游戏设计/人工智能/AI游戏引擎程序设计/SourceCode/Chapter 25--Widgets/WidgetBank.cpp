// WidgetBank.cpp : implementation file
//

#include "stdafx.h"
#include "Widgets/WidgetBank.h"
#include "Common.h"
#include "Widgets/Group.h"
#include "resource.h"
#include ".\widgetbank.h"

//#ifdef _DEBUG
//#define new DEBUG_NEW
//#endif

#define IDR_MAINFRAME					128
IMPLEMENT_DYNCREATE( WidgetBank, CFrameWnd )

/******************************************************************************
 *	Name:	WidgetBank
 *
 *	Info:	WidgetBank constructor
 *
 *****************************************************************************/
WidgetBank::WidgetBank()
{
	m_numGroups = 0;
		
	for (int i = 0; i < MAX_CHILD_WIDGETS; i++ )	
		m_groups[i] = NULL;
	
	m_hWnd = (HWND)0;
	m_id = 0;
	Init();
}

/******************************************************************************
 *	Name:	~WidgetBank
 *
 *	Info:	WidgetBank destructor
 *
 *****************************************************************************/
WidgetBank::~WidgetBank()
{
}

BEGIN_MESSAGE_MAP(WidgetBank, CWnd)
	ON_WM_NCHITTEST()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_NCDESTROY()
	ON_WM_VSCROLL()
END_MESSAGE_MAP()

/******************************************************************************
*	Name:	Init
*
*	Info:	Create the widget bank window.
*
*****************************************************************************/
void WidgetBank::Init()
{
	CRect rect(CPoint(0,0), CPoint( WIDGET_BANK_WIDTH, 0 ));
	WidgetBank::CreateEx(	NULL, 
							NULL,
							"Widgets of Kindness",  
							WS_SIZEBOX | WS_CAPTION | WS_POPUP | WS_VISIBLE | WS_CHILD, 
							rect,
							AfxGetApp()->GetMainWnd(),
							NULL );
}

/******************************************************************************
 *	Name:	AddGroup
 *
 *	Info:	Adds a widget group to the widget bank. Other widgets and groups 
 *			can then be added to this widget group.
 *
 *	Args:	label - the header caption for this widget group.
 *
 *	Return:	A pointer to the widget group created.
 *
 *****************************************************************************/
Group* WidgetBank::AddGroup( char * label )
{

	Group * g = NULL;
	CRect wbRect;
	GetClientRect(wbRect);

	g = m_groups[m_numGroups++] = new Group(	label, 
										this,
										0 );
	g->SetWidgetBank( this );

	UpdateWidgetBankSize();
	return g;
}

/******************************************************************************
 *	Name:	Draw
 *
 *	Info:	Runs through all the widgets and redraws them. This generally needs
 *			to be called whenever the user expands/contracts a widget.
 *
 *****************************************************************************/
void WidgetBank::Draw(){
	CRect r;

	int y_offset = GetScrollPos(SB_VERT) ;

	int y_pos = 0;

	for ( int i = 0; i < m_numGroups; i++ )
	{
		y_pos += m_groups[i]->Draw( y_pos - y_offset );
	}

	Invalidate();
}
/******************************************************************************
 *	Name:	OnNcHitTest
 *
 *	Info:	Overloaded function, called every time the mouse is moved in this 
 *			window.
 *
 *****************************************************************************/
UINT WidgetBank::OnNcHitTest(CPoint point)
{
	int check;

	switch ( check=CWnd::OnNcHitTest(point) ) {
        // if the mouse is in any of the following locations, then
		// ignore it. Otherwise, return as usual.
//		 case HTRIGHT:
		 case HTTOPRIGHT:
         case HTTOP:
         case HTTOPLEFT:
		// case HTBOTTOM:
         case HTLEFT:
         case HTBOTTOMLEFT:
         case HTBOTTOMRIGHT:
              return 0;
	}
	return check;
}

/******************************************************************************
 *	Name:	OnSize
 *
 *	Info:	Overloaded function, called when the window is resized. This is 
 *			where the scrollbar gets sized and positioned.
 *
 *****************************************************************************/
void WidgetBank::OnSize(UINT nType, int cx, int cy)
{
	SCROLLINFO	si ;

	si.cbSize = sizeof(SCROLLINFO) ;
	si.fMask = SIF_PAGE | SIF_RANGE ;
	
	// show/hide/setup the vertical scrollbar
	ShowScrollBar( SB_VERT ) ;
	si.nPage = cy ;
	si.nMax = m_ClientSize.Height() ;
	si.nMin = 0 ;
	SetScrollInfo(SB_VERT, &si);
	EnableScrollBarCtrl(SB_VERT );
	Draw();
	CWnd::OnSize(nType, cx, cy);

}

/******************************************************************************
*	Name:	GetHeight
*
*	Info:	Calculates the height of the widget bank, based on the number of
*			child groups it has.
*
*	Return:	The height;
*
*****************************************************************************/
int WidgetBank::GetHeight()
{
	int height = 0;
	for (int i = 0; i < m_numGroups; i++ )
	{
		height+= m_groups[i]->GetHeight();
	}
	return height;
}

/******************************************************************************
 *	Name:	OnEraseBkgnd
 *
 *	Info:	Overloaded function, called when Background is erased. It doesn't
 *			do anything now but return false, but this is supposed to somehow
 *			help with the flickering effect you sometimes see when MFC controls
 *			are drawn.
 *
 *	Return:	success/failure.
 *
 *****************************************************************************/
BOOL WidgetBank::OnEraseBkgnd(CDC* /* pDC */ )
{
	return false;
}

/******************************************************************************
 *	Name:	UpdateWidgetBankSize
 *
 *	Info:	Most important thing that happens here is the resizing of the
 *			widget bank's client size. This function is called each time
 *			a widget is added to the widget bank, hence the need to update the
 *			client size.
 *
 *****************************************************************************/
void WidgetBank::UpdateWidgetBankSize()
{
	/* Get the coordinate and size of the frame */
	CRect r, rWindow;
	GetClientRect(r);
	GetWindowRect(rWindow);
	
	/* calculate the width taken up by window borders */
	int WinTotalBorderHeight=rWindow.Height()-r.Height();

	int newHeight=0;
	if ( m_numGroups > MAX_NUM_WIDGETS )
		newHeight= MAX_NUM_WIDGETS_DISPLAY * ( MINIMIZED_WIDGET_HEIGHT)+ WinTotalBorderHeight;
	else 
		newHeight = (m_numGroups*MINIMIZED_WIDGET_HEIGHT) + WinTotalBorderHeight; 

	/* Resize the Widget Bank window, now that we know how many widgets it holds */
	MoveWindow( 0,0, rWindow.Width(), newHeight, true );

	Draw();
}

/******************************************************************************
*	Name:	CreateEx
*
*	Info:	Overloaded function, called when the widget bank is created.
*
*****************************************************************************/
BOOL WidgetBank::CreateEx(DWORD dwExStyle, LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, LPVOID lpParam)
{
	CRect r, rRect;
	int result = 0;
	result = CWnd::CreateEx( dwExStyle,
		lpszClassName, 
		lpszWindowName, 
		dwStyle,
		rect,
		pParentWnd,
		nID,
		lpParam);

	// Get the coordinate and size of the frame we just made
	GetClientRect(r);
	GetWindowRect(rRect);
	m_ClientSize = CRect(0, 0, r.Width(), rRect.Height()) ;

	return true;
}

void WidgetBank::OnNcDestroy()
{
	CWnd::OnNcDestroy();
	delete this;
}

/******************************************************************************
*	Name:	Update
*
*	Info:	Update all of the widget bank's child groups.
*
*****************************************************************************/
void WidgetBank::Update()
{
	for (int i = 0; i < m_numGroups; i++ )
	{
		m_groups[i]->Update();
	}
}

/******************************************************************************
*	Name:	OnVScroll
*
*	Info:	Overloaded function, called when the window is scrolled. This is 
*			where scrolling events are handled.
*
*****************************************************************************/
void WidgetBank::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	int nCurPos = GetScrollPos(SB_VERT) ;
	int nPrevPos = nCurPos;
	// decide what to do for each different scroll event
	switch( nSBCode )
	{
	case SB_LEFT:			nCurPos = 0;
		break;
	case SB_RIGHT:			nCurPos = GetScrollLimit(SB_VERT)-1;
		break;
	case SB_LINEDOWN:		nCurPos = min( nCurPos + MINIMIZED_WIDGET_HEIGHT, GetScrollLimit(SB_VERT) );
		break;		
	case SB_LINEUP:			nCurPos = max( nCurPos - MINIMIZED_WIDGET_HEIGHT, 0 );
		break;		
	case SB_PAGELEFT:		nCurPos = max(nCurPos - m_ClientSize.Height(), 0);
		break;
	case SB_PAGERIGHT:		nCurPos = min(nCurPos + m_ClientSize.Height(), GetScrollLimit(SB_VERT)-1);
		break;
	case SB_THUMBTRACK:
	case SB_THUMBPOSITION:  nCurPos = nPos;
		break;
	}		

	SetScrollPos( SB_VERT, nCurPos);
	ScrollWindow( 0, nPrevPos - nCurPos) ;
	CWnd::OnVScroll(nSBCode, nPos, pScrollBar);
}
