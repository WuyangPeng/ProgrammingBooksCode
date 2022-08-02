#if !defined (CONTROL_H)
#define CONTROL_H
// Bartosz Milewski (c) 2000
#include <windows.h>
#include "Window.h"
#include "Procedure.h"

namespace Win
{
	class KeyState
	{
	public:
		KeyState (WPARAM wParam): _data (wParam)
		{}
		bool IsCtrl () const 
			{ return (_data & MK_CONTROL) != 0;}
		bool IsShift () const 
			{ return (_data & MK_SHIFT) != 0; }
		bool IsLButton () const 
			{ return (_data & MK_LBUTTON) != 0;}
		bool IsMButton () const 
			{ return (_data & MK_MBUTTON) != 0;}
		bool IsRButton () const 
			{ return (_data & MK_RBUTTON) != 0;}
	private:
		WPARAM    _data;
	};

	class Controller
	{
		friend LRESULT CALLBACK Procedure (HWND hwnd, 
						UINT message, WPARAM wParam, LPARAM lParam);
	protected:
		void SetWindowHandle (HWND hwnd) { _h.Init (hwnd); }
	public:
		virtual ~Controller () {}
		virtual bool OnCreate (Win::CreateData const * create, bool & success) throw ()
			{ return false; }
		virtual bool OnDestroy () throw ()
			{ return false; }
		virtual bool OnFocus (Win::Dow winPrev) throw ()
			{ return false; }
		virtual bool OnSize (int width, int height, int flag) throw ()
			{ return false; }
		virtual bool OnPaint () throw ()
			{ return false; }
		virtual bool OnCommand (int cmdId, bool isAccel) throw ()
			{ return false; }
		virtual bool OnControl (Win::Dow control, int controlId, int notifyCode) throw ()
			{ return false; }
		// Mouse
		virtual bool OnMouseMove (int x, int y,	KeyState kState)  throw ()
			{ return false; }
		virtual bool OnLButtonDown (int x, int y, Win::KeyState kState) throw ()
			{ return false; }
		virtual bool OnLButtonUp (int x, int y, Win::KeyState kState) throw ()
			{ return false; }
		virtual bool OnCaptureChanged (HWND hwndNewCapture) throw ()
			{ return false; }
		// Keyboard
		virtual bool OnKeyDown (int vKey, int flags) throw ()
			{ return false; }

	protected:
		Win::Dow  _h;
	};
	
	class SubController: public Controller
	{
	public:
		SubController () : _prevProc (0), _prevController (0) {}
		void Init (HWND win, ProcPtr prevProc, Controller * prevCtrl)
		{
			SetWindowHandle (win);
			_prevProc = prevProc;
			_prevController = prevCtrl;
		}
		LRESULT CallPrevProc (UINT message, WPARAM wParam, LPARAM lParam)
		{
			return ::CallWindowProc (_prevProc, _h, message, wParam, lParam);
		}
		ProcPtr GetPrevProc ()
		{
			return _prevProc;
		}
		Controller * GetPrevController ()
		{
			return _prevController;
		}
	protected:
		ProcPtr _prevProc;
		Controller * _prevController;
	};
}
#endif
