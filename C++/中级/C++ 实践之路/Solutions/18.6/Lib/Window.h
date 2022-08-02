#if !defined (WINDOW_H)
#define WINDOW_H
// Bartosz Milewski (c) 2000
#include <windows.h>
#include <cassert>

namespace Win
{
	class SubController;

	// class Win::Dow
	class Dow
	{
	public:
		Dow (HWND h = 0) : _h (h) {}
		void Init (HWND h) { _h = h; }
		operator HWND () const { return _h; }
		void Destroy ()
		{
			::DestroyWindow (_h);
		}
		Win::Dow GetParent () { return ::GetParent (_h); }
		HINSTANCE GetInstance () const
		{
			return reinterpret_cast<HINSTANCE> (
				::GetWindowLong (_h, GWL_HINSTANCE));
		}
		
		template <class T>
		inline T GetLong (int which = GWL_USERDATA)
		{
			return reinterpret_cast<T> (::GetWindowLong (_h, which));
		}
		
		template <class T>
		inline void SetLong (T value, int which = GWL_USERDATA)
		{
			::SetWindowLong (_h, which, reinterpret_cast<long> (value));
		}

		LRESULT SendMsg (UINT msg, WPARAM wparam = 0, LPARAM lparam = 0) const
		{
			return ::SendMessage (_h, msg, wparam, lparam);
		}
		bool PostMsg (UINT msg, WPARAM wparam = 0, LPARAM lparam = 0) const
		{
			return ::PostMessage (_h, msg, wparam, lparam) != FALSE;
		}
		void CaptureMouse ()
		{
			::SetCapture (_h);
		}
		void ReleaseMouse ()
		{
			if (HasCapture ())
				::ReleaseCapture ();
		}
		bool HasCapture () const
		{
			return ::GetCapture () == _h;
		}
		// Text/Caption
		void SetText (char const * text) 
		{ 
			::SetWindowText (_h, text); 
		}
		int GetText (char * buf, int len) const // len includes null
		{ 
			return ::GetWindowText (_h, buf, len); 
		}
		// Window visibility
		void Show (int cmdShow = SW_SHOW) 
		{ 
			::ShowWindow (_h, cmdShow); 
		}
		void Hide () 
		{ 
			::ShowWindow (_h, SW_HIDE); 
		}
		void Update () 
		{ 
			::UpdateWindow (_h); 
		}
		void Display (int cmdShow)
		{
			Show (cmdShow);
			Update ();
		}
		// Font
		void SetFont (HFONT hFont)
		{
			BOOL fRedraw = TRUE;
			SendMsg (WM_SETFONT, 
					reinterpret_cast<WPARAM> (hFont), 
					MAKELPARAM (fRedraw, 0));
		}
		// Focus
		void SetFocus ()
		{ 
			::SetFocus (_h); 
		}
		bool HasFocus () const
		{
			return ::GetFocus () == _h;
		}
		// Moving
		void Move (int x, int y, int width, int height)
		{
			::MoveWindow (_h, x, y, width, height, TRUE);
		}
		// Subclassing
		void SubClass (SubController * ctrl);
		void UnSubClass ();
	private:
		HWND _h;
	};
}

#endif
