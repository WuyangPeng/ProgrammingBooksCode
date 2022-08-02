// PolyCtl.cpp : Implementation of CPolyCtl

#include "stdafx.h"
#include "Polygon.h"
#include "PolyCtl.h"
#include <time.h>
#include <string.h>

/////////////////////////////////////////////////////////////////////////////
// CPolyCtl

HRESULT CPolyCtl::OnDraw(ATL_DRAWINFO& di)
{
    struct tm *date_time;
	time_t timer;
	static TEXTMETRIC tm;
	
	RECT& rc = *(RECT*)di.prcBounds;
	HDC hdc  = di.hdcDraw;

	COLORREF colFore;
	HBRUSH hOldBrush, hBrush;
	HPEN hOldPen, hPen;

	// Translate m_colFore into a COLORREF type
	OleTranslateColor(m_clrFillColor, NULL, &colFore);
	
	// Create and select the colors to draw the circle
	hPen = (HPEN)GetStockObject(BLACK_PEN);
	hOldPen = (HPEN)SelectObject(hdc, hPen);
	hBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);
	hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

	const double pi = 3.14159265358979;
	POINT	ptCenter;
	double  dblRadiusx = (rc.right - rc.left) / 2;
	double  dblRadiusy = (rc.bottom - rc.top) / 2;
	double	dblAngle = 3 * pi / 2;			// Start at the top
	double	dblDiff  = 2 * pi / m_nSides;	// Angle each side will make
	ptCenter.x = (rc.left + rc.right) / 2;
	ptCenter.y = (rc.top + rc.bottom) / 2;
	
	// Calculate the points for each side
	for (int i = 0; i < m_nSides; i++)
	{
		m_arrPoint[i].x = (long)(dblRadiusx * cos(dblAngle) + ptCenter.x + 0.5);
		m_arrPoint[i].y = (long)(dblRadiusy * sin(dblAngle) + ptCenter.y + 0.5);
		dblAngle += dblDiff;
	}
	Ellipse(hdc, rc.left, rc.top, rc.right, rc.bottom);

	// Create and select the brush that will be used to fill the polygon
	hBrush	  = CreateSolidBrush(colFore);
	SelectObject(hdc, hBrush);
	Polygon(hdc, &m_arrPoint[0], m_nSides);


	// Print date and time
	time(&timer);
	date_time=localtime(&timer);

	const char* strtime;
		
    strtime	= asctime(date_time);

	SetBkMode(hdc,TRANSPARENT);

	SetTextAlign(hdc, TA_CENTER | TA_TOP);
	ExtTextOut(hdc, (rc.left + rc.right)/2,(rc.top + rc.bottom - tm.tmHeight)/2,
		       ETO_CLIPPED, &rc, strtime, strlen(strtime)-1, NULL);
	
	// Select back the old pen and brush and delete the brush we created
	SelectObject(hdc, hOldPen);
	SelectObject(hdc, hOldBrush);
	DeleteObject(hBrush);

	return S_OK;
}

LRESULT CPolyCtl::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	HRGN hRgn;
	WORD xPos = LOWORD(lParam);  // horizontal position of cursor 
	WORD yPos = HIWORD(lParam);  // vertical position of cursor 

	// Create a region from our list of points
	hRgn = CreatePolygonRgn(&m_arrPoint[0], m_nSides, WINDING);
	
	// If the clicked point is in our polygon then fire the ClickIn
	//  event otherwise we fire the ClickOut event
	if (PtInRegion(hRgn, xPos, yPos))
		Fire_ClickIn(xPos, yPos);
	else
	    Fire_ClickOut(xPos, yPos);

	// Delete the region that we created
	DeleteObject(hRgn);
	return 0;
}

STDMETHODIMP CPolyCtl::get_Sides(short *pVal)
{
	*pVal = m_nSides;
	return S_OK;
}

STDMETHODIMP CPolyCtl::put_Sides(short newVal)
{
	if (newVal > 2 && newVal < 11)
	{
		m_nSides = newVal;
		FireViewChange();
		return S_OK;
	}
	else
		return Error(_T("Must have between 3 and 10 sides"));
}


