#if !defined (MAKER_H)
#define MAKER_H
// Bartosz Milewski (c) 2000
#include <windows.h>
#include "Control.h"

namespace Win
{
	class Maker
	{
	public:
		Maker (char const * className, HINSTANCE hInst);
		HWND Create (Win::Controller & ctrl, char const * title);
	protected:
		HINSTANCE    _hInst;		// program instance
		char const  *_className;	// name of Window class
		DWORD        _style;		// window style
		DWORD        _exStyle;		// window extended style
		int          _x;			// horizontal position
		int          _y;			// vertical position
		int          _width;		// window width 
		int          _height;		// window height
		HWND         _hWndParent;	// parent or owner
		HMENU        _hMenu;		// menu, or child-window id
		void		*_data;			// window-creation data
	};

	class ChildMaker: public Maker
	{
	public:
		ChildMaker (char const * className, Win::Dow winParent, int childId);
		HWND Create (char const * text = "");
	};
}
	
#endif
