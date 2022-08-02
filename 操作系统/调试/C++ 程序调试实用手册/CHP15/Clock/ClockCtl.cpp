// ClockCtl.cpp : Implementation of the CClockCtrl ActiveX Control class.

#include "stdafx.h"
#include "Clock.h"
#include "ClockCtl.h"
#include "ClockPpg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CClockCtrl, COleControl)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CClockCtrl, COleControl)
	//{{AFX_MSG_MAP(CClockCtrl)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_EDIT, OnEdit)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CClockCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CClockCtrl)
	DISP_PROPERTY_NOTIFY(CClockCtrl, "ClockShape", m_clockShape, OnClockShapeChanged, VT_BOOL)
	DISP_PROPERTY_NOTIFY(CClockCtrl, "HitClock", m_hitClock, OnHitClockChanged, VT_COLOR)
	DISP_STOCKPROP_BACKCOLOR()
	//}}AFX_DISPATCH_MAP
	DISP_FUNCTION_ID(CClockCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CClockCtrl, COleControl)
	//{{AFX_EVENT_MAP(CClockCtrl)
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

BEGIN_PROPPAGEIDS(CClockCtrl, 1)
	PROPPAGEID(CClockPropPage::guid)
END_PROPPAGEIDS(CClockCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CClockCtrl, "CLOCK.ClockCtrl.1",
	0xa4386f86, 0x98de, 0x11d3, 0xa7, 0xe0, 0, 0x80, 0xae, 0, 0, 0x1)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CClockCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DClock =
		{ 0xa4386f84, 0x98de, 0x11d3, { 0xa7, 0xe0, 0, 0x80, 0xae, 0, 0, 0x1 } };
const IID BASED_CODE IID_DClockEvents =
		{ 0xa4386f85, 0x98de, 0x11d3, { 0xa7, 0xe0, 0, 0x80, 0xae, 0, 0, 0x1 } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwClockOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CClockCtrl, IDS_CLOCK, _dwClockOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CClockCtrl::CClockCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CClockCtrl

BOOL CClockCtrl::CClockCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: Verify that your control follows apartment-model threading rules.
	// Refer to MFC TechNote 64 for more information.
	// If your control does not conform to the apartment-model rules, then
	// you must modify the code below, changing the 6th parameter from
	// afxRegInsertable | afxRegApartmentThreading to afxRegInsertable.

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_CLOCK,
			IDB_CLOCK,
			afxRegInsertable | afxRegApartmentThreading,
			_dwClockOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// CClockCtrl::CClockCtrl - Constructor

CClockCtrl::CClockCtrl()
{
	InitializeIIDs(&IID_DClock, &IID_DClockEvents);
}


/////////////////////////////////////////////////////////////////////////////
// CClockCtrl::~CClockCtrl - Destructor

CClockCtrl::~CClockCtrl()
{
}


/////////////////////////////////////////////////////////////////////////////
// CClockCtrl::OnDraw - Drawing function

void CClockCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
  CBrush* pBackBrush;
  CBrush* pFaceBrush;
  CPen* pHandsPen;  
  CRect rc = rcBounds;
  int xcenter, ycenter;

  // clock background rectangle
  pBackBrush=new CBrush(RGB(0,0,255));
  pdc->FillRect(rcBounds, pBackBrush);
  GetDrawRect(&rc);
  
  // clock face 
  pFaceBrush=new CBrush(RGB(255,255,0));
  pdc->SelectObject(pFaceBrush);
  pdc->Ellipse(rc);

  // clock hands
  pHandsPen=new CPen(PS_SOLID,3,RGB(0,0,0));
  pdc->SelectObject(pHandsPen);
  xcenter=(rc.right-rc.left)/2 + rc.left;
  ycenter=(rc.bottom-rc.top)/2 + rc.top;
  pdc->MoveTo(xcenter,ycenter);
  pdc->LineTo(rc.right*75/100,rc.bottom*75/100);
  pdc->MoveTo(xcenter,ycenter);
  pdc->LineTo(xcenter,rc.bottom*90/100);

  delete pBackBrush;
  delete pFaceBrush;
  delete pHandsPen;
}


/////////////////////////////////////////////////////////////////////////////
// CClockCtrl::DoPropExchange - Persistence support

void CClockCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	PX_Long(pPX, _T("HitClock"), (long&)m_hitClock, RGB(196,196,196));

}


/////////////////////////////////////////////////////////////////////////////
// CClockCtrl::OnResetState - Reset control to default state

void CClockCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange
}


/////////////////////////////////////////////////////////////////////////////
// CClockCtrl::AboutBox - Display an "About" box to the user

void CClockCtrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_CLOCK);
	dlgAbout.DoModal();
}


/////////////////////////////////////////////////////////////////////////////
// CClockCtrl message handlers

void CClockCtrl::OnClockShapeChanged() 
{
	// TODO: Add notification handler code

	SetModifiedFlag();
}


void CClockCtrl::GetDrawRect(CRect* rc)
{
  // Round clock face
  int dx = rc->right - rc->left;
  int dy = rc->bottom - rc->top;
  if (dx > dy) {
    rc->left += (dx - dy) / 2;
    rc->right = rc->left + dy;
  }
  else {
    rc->top += (dy - dx) / 2;
    rc->bottom = rc->top + dx;
  }
}

void CClockCtrl::OnHitClockChanged() 
{
	// TODO: Add notification handler code

	SetModifiedFlag();
}

void CClockCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

    CDC* pdc;

    // Flash a color change for clock face
    if (InFace(point)) {
      pdc = GetDC();
      HitClock(pdc);
      ReleaseDC(pdc);
	}	

	COleControl::OnLButtonDown(nFlags, point);
}

void CClockCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

    if (InFace(point))
      InvalidateControl();	

	COleControl::OnLButtonUp(nFlags, point);
}

BOOL CClockCtrl::InFace(CPoint& point)
{
  CRect rc;
  GetClientRect(rc);
  GetDrawRect(&rc);
  
  // Find center point
  double h = (rc.right - rc.left) / 2;
  double k = (rc.bottom - rc.top) / 2;

  // Find x and y values
  double x = point.x - (rc.right + rc.left) / 2;
  double y = point.y - (rc.bottom + rc.top) / 2;

  // Ellipse equation determines location of point
  return ((x * x) / (h * h) + (y * y) / (k * k) <= 1);
}

void CClockCtrl::HitClock(CDC* pdc)
{
  CBrush* pOldBrush;
  CBrush hitBrush(TranslateColor(m_hitClock));
  CRect rc;
  TEXTMETRIC tm;
  struct tm *date_time;
  time_t timer;

  // Fill between text
  // Background mode to transparent
  pdc->SetBkMode(TRANSPARENT);

  GetClientRect(rc);
  GetDrawRect(&rc);

  pOldBrush=pdc->SelectObject(&hitBrush);
  pdc->Ellipse(rc);

  // Get time and date 
  time(&timer);
  date_time=localtime(&timer);
  const CString& strtime = asctime(date_time);
  
  // Get Font information then print
  pdc->GetTextMetrics(&tm);
  pdc->SetTextAlign(TA_CENTER | TA_TOP);
  pdc->ExtTextOut((rc.left + rc.right)/2,
                   (rc.top + rc.bottom - tm.tmHeight)/2,
                   ETO_CLIPPED, rc, strtime,
                   strtime.GetLength()-1, NULL);

  pdc->SelectObject(pOldBrush);
}

