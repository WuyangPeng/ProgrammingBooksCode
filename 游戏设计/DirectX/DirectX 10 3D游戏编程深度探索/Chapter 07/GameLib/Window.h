/*******************************************************************
 *         Advanced 3D Game Programming with DirectX 10.0
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *	
 *	See license.txt for modification and distribution information
 *		copyright (c) 2007 by Peter Walsh, Wordware
 ******************************************************************/

#ifndef _WINDOW_H
#define _WINDOW_H

#include <windows.h>

#include <list>
#include <string>

#include "GameErrors.h"


/**
 * cWindow 
 * Window encapsulator
 */
class cWindow  
{
protected:

	// Width and height of the client area
	int m_Width, m_Height;

	// Handle to the window
	HWND m_hWnd;

	// Name of the window 
	std::wstring m_name;

	// True if the window is active	
	bool m_bActive;

	static cWindow* m_pGlobalWindow;

public:
	cWindow( 
		int width, 
		int height, 
		const TCHAR* name = L"Default window name" );
	~cWindow();

	virtual LRESULT WndProc(
		HWND hWnd,
		UINT uMsg,
		WPARAM wParam,
		LPARAM lParam );

	virtual void RegisterClass( WNDCLASSEX* pWc = NULL );
	virtual void InitInstance();

	HWND GetHWnd()
	{
		return m_hWnd;
	}

	bool IsActive()
	{ 
		return m_bActive; 
	}

	// True -> there are messages in the queue for us to pump
	bool HasMessages();

	// res_AllGood -> continue running
	// res_False -> got a WM_QUIT.  Stop the application.
	eResult Pump();

	static cWindow* GetMainWindow()
	{ 
		return m_pGlobalWindow; 
	}

};

inline cWindow* MainWindow()
{ 
	return cWindow::GetMainWindow(); 
}


#endif //_WINDOW_H
