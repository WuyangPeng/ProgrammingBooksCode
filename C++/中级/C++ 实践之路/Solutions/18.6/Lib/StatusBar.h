#if !defined (STATUSBAR)
#define STATUSBAR
// Bartosz Milewski (c) 2000
#include "Controls.h"
#include "Exception.h"
#include <commctrl.h>

namespace Win
{
	class StatusBar : public Win::SimpleCtrl
	{
	public:
		StatusBar (HWND winParent, int id)
			: Win::SimpleCtrl (winParent, id)
		{
			SetHeight ();
		}
		StatusBar (HWND win = 0)
			: Win::SimpleCtrl (win),
			  _height (0)
		{
			if (win)
				SetHeight ();
		}
		void Init (HWND win)
		{
			SimpleCtrl::Init (win);
			SetHeight ();
		}
		bool GetPartRect (RECT & partRect, int idx = 0)
		{
			return SendMsg (SB_GETRECT, idx, reinterpret_cast<LPARAM>(&partRect)) != 0;
		}
		int Height () const { return _height; }
	private:
		void SetHeight ()
		{
			RECT partRect;
			if (GetPartRect (partRect) != 0)
			{
				_height = partRect.bottom - partRect.top;
			}
		}

	private:
		int	_height;
	};

	class StatusBarMaker : public Win::ControlMaker
	{
	public:
		StatusBarMaker (HWND winParent, int id)
			: ControlMaker ("", winParent, id)
		{
			INITCOMMONCONTROLSEX init;
			init.dwSize = sizeof (INITCOMMONCONTROLSEX);
			init.dwICC = ICC_BAR_CLASSES;
			if (InitCommonControlsEx (&init) == FALSE)
				throw Win::Exception ("Cannot initialize common controls");

			_style |= WS_CLIPSIBLINGS | CCS_BOTTOM | SBARS_SIZEGRIP;
		}
		HWND Create ()
		{
			HWND h = ::CreateStatusWindow (_style, "", _hWndParent, 
							reinterpret_cast<unsigned int>(_hMenu));
			if (h == 0)
				throw Win::Exception ("Internal error: Couldn't create status bar");
			return h;
		}
	};
}
#endif
