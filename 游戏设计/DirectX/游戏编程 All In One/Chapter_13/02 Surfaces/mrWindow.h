 /* 'mrWindows.h' */

 /* Mirus base types header */
#include "mrDatatypes.h"
 /* Mirus error definitions header */
#include "mrError.h"
 /* Windows header file */
#include <windows.h> 

 /* Include this file only once */
#pragma once

 /* Mirus window framework */
class mrWindow
{
protected:
 WNDCLASS  m_kWndClass;
 HWND      m_hWindow;
 MSG       m_kMessage;

public:
	 /* Constructor / Destructor */
 mrWindow (void);
 ~mrWindow (void);

  /* Window manipulation functions */
 mrError32 Create (HINSTANCE hInstance, LPSTR szTitle, 
                   mrInt iWidth = CW_USEDEFAULT, 
                   mrInt iHeight = CW_USEDEFAULT, 
                   mrUInt32 iStyle = WS_OVERLAPPEDWINDOW | WS_VISIBLE);
 static LRESULT CALLBACK WndProc (HWND hWindow, UINT iMessage, 
                         WPARAM wParam, LPARAM lParam);
 void Run (void);

  /* Custom functions */
 virtual mrBool32 MessageHandler (UINT iMessage, WPARAM wParam, 
                                  LPARAM lParam);
 virtual mrBool32 Frame (void) = 0;

  /* More functions */
 void SetPosition (mrInt iWidth, mrInt iHeight);
 POINT GetPosition (void);
 void SetSize (mrInt iWidth, mrInt iHeight);
 POINT GetSize (void);
 void Show (mrInt iShow);
	HWND GetHandle (void);
};