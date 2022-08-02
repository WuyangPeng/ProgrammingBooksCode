#if !defined (PROCEDURE_CPP)
#define PROCEDURE_CPP
#include "Procedure.h"
// Bartosz Milewski (c) 2000
#include "Control.h"
#include "Window.h"

LRESULT CALLBACK Win::Procedure (HWND hwnd, 
								UINT message, 
								WPARAM wParam, 
								LPARAM lParam)
{
	Win::Dow win (hwnd);
	Win::Controller * pCtrl = win.GetLong<Win::Controller *> ();
	switch (message)
	{
		case WM_NCCREATE:
		{
			Win::CreateData const * create = 
				reinterpret_cast<Win::CreateData const *> (lParam);
			pCtrl = static_cast<Win::Controller *> (
				create->GetCreationData());
			pCtrl->SetWindowHandle (hwnd);
			win.SetLong<Win::Controller *> (pCtrl);
			break;
		}
		case WM_CREATE:
		{
			bool success = false;
			if (pCtrl->OnCreate (reinterpret_cast<CreateData const *> (lParam), success))
				return success? 0: -1;
			break;
		}
		case WM_DESTROY:
			// We're no longer on screen
			pCtrl->OnDestroy ();
			return 0;
		case WM_COMMAND:
			if (lParam == 0)
			{
				if (pCtrl->OnCommand (LOWORD (wParam), HIWORD (wParam) == 1))
					return 0;
			}
			else
			{
				HWND hCtrl = reinterpret_cast<HWND>(lParam);
				if (pCtrl->OnControl (hCtrl, LOWORD (wParam), HIWORD (wParam)))
					return 0;
			}
			break;
		case WM_SETFOCUS:
		{
			HWND wndPrev = reinterpret_cast<HWND> (wParam);
			if (pCtrl->OnFocus (wndPrev))
				return 0;
			break;
		}
		case WM_PAINT:
			if (pCtrl->OnPaint ())
				return 0;
			break;
		case WM_SIZE:
			if (pCtrl->OnSize (LOWORD (lParam), HIWORD (lParam), wParam))
				return 0;
			break;
		case WM_MOUSEMOVE:
		{
			POINTS p = MAKEPOINTS (lParam);
			Win::KeyState kState (wParam);
			if (pCtrl->OnMouseMove (p.x, p.y, kState))
				return 0;
			break;
		}
		case WM_LBUTTONDOWN:
		{
			POINTS p = MAKEPOINTS (lParam);
			KeyState kState (wParam);
			if (pCtrl->OnLButtonDown (p.x, p.y, kState))
				return 0;
			break;
		}
		case WM_LBUTTONUP:
		{
			POINTS p = MAKEPOINTS (lParam);
			KeyState kState (wParam);
			if (pCtrl->OnLButtonUp (p.x, p.y, kState))
				return 0;
			break;
		}
		case WM_CAPTURECHANGED:
			if (pCtrl->OnCaptureChanged (reinterpret_cast<HWND> (lParam)))
				return 0;
			break;
		case WM_KEYDOWN:
			if (pCtrl->OnKeyDown (wParam, lParam))
				return 0;
			break;
	}
	return ::DefWindowProc (hwnd, message, wParam, lParam);
}

// window subclassing procedure

LRESULT CALLBACK Win::SubProcedure (HWND hwnd, 
                                 UINT message, 
                                 WPARAM wParam, 
                                 LPARAM lParam)
{
	Win::Dow win (hwnd);
    SubController * pCtrl = win.GetLong<Win::SubController *> ();
    switch (message)
    {
	case WM_SETFOCUS:
		{
			HWND wndPrev = reinterpret_cast<HWND> (wParam);
			if (pCtrl->OnFocus (wndPrev))
				return 0;
		}
		break;
	case WM_KEYDOWN:
		if (pCtrl->OnKeyDown (wParam, lParam))
			return 0;
		break;
	}
	return pCtrl->CallPrevProc (message, wParam, lParam);
}

#endif
